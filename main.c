#include <GL/glut.h>
#include <stdio.h>
#include "drawing.h"
#include "types.h"
#include "logic.h"
#define TIMER_ID 0
#define TIMER_INTERVAL 200
static Snake snake;
static Food food;
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void); 
static int animation_ongoing;
static void on_display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(22, 20, 22, 
                0, 0, 0
                , 0, 1, 0);
     draw_coordinate_system();
     draw_snake(&snake);
     draw_food(&food);
     draw_terrain();
     glutSwapBuffers();
}

static void on_timer(int value)
{
    if (value != TIMER_ID)
        return;
    move_snake(&snake);
    if (is_food_eaten(&snake,&food)) //Da li smo pojeli hranu
    {
        generate_food_position(&food.position.x,&food.position.z);  //Posto je hrana pojedena generisemo novu hranu
        size_up(&snake,1); //povecavamo zmijicu za 1 polje
    }
    glutPostRedisplay();
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(EXIT_SUCCESS);
        break;
    case 'a':
        if (snake.direction.x==1) break;
        snake.direction.x=-1;
        snake.direction.z=0;  
        break;
    case 'd':
        if (snake.direction.x==-1) break;
        snake.direction.x=+1;
        snake.direction.z=0;
        break;
    case 'w':
        if (snake.direction.z==1) break;
        snake.direction.x=0;
        snake.direction.z=-1;
        break;
    case 's':
        if (snake.direction.z==-1) break;
        snake.direction.x=0;
        snake.direction.z=1;
        break;
    case 'p':
        animation_ongoing=0;
        break;
    case 'b':
        animation_ongoing=1;
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        break;
    }
    glutPostRedisplay();
}
static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 100);
}

int main(int argc,char** argv)
{
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);

    glutCreateWindow("Snake 3D");

    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    
    /*Incijalizacija zmijice dok ne namestimo da zmijica raste kad pojede hranu*/
    init_game(&snake,&food,&animation_ongoing);

    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}