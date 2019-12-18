#include <GL/glut.h>
#include <stdio.h>
#include "../Headers/drawing.h"
#include "../Headers/types.h"
#include "../Headers/logic.h"
#include "../Headers/map.h"
#define TIMER_ID 0

static Snake snake;
static Food food;
static Terrain terrain;
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void); 
static int animation_ongoing;
static int TIMER_INTERVAL_SNAKE_INIT=100; //pocinjemo sa 100ms
static int TIMER_INTERVAL_SNAKE_CURR; //zadajemo trenutni interval tajmera
//TO DO Implementirati mehanizam za oslobadjanje memorije
int is_game_over=0;
static void on_display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glClearColor(135.0/255, 206.0/255, 250/255.0,1);
     if (!is_game_over)
     {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 22, 21, 
                    0, 0, 0
                    , 0, 1, 0);
        //draw_coordinate_system();
        draw_snake(&snake);
        draw_food(&food);
        draw_terrain(&terrain);
        draw_score(&snake);
     }
     else
     {
         draw_game_over(&snake);
     }
     
    
     glutSwapBuffers();
}

static void on_timer(int value)
{
    if (value != TIMER_ID)
        return;
    move_snake(&snake,&terrain);
    if (is_food_eaten(&snake,&food)) //Da li smo pojeli hranu
    {
        increase_score(&snake,1); //uvecavamo skor za 1
        if (TIMER_INTERVAL_SNAKE_CURR>50) // ne dozvoljavamo da bude prebrzo
        {
            const int coef_of_speed=5; //zadajemo koef za koji se menja brzina na svakih 5 bodova 
            TIMER_INTERVAL_SNAKE_CURR=TIMER_INTERVAL_SNAKE_INIT-coef_of_speed*snake.score/5;
        }
        //Generisemo hranu dok ne dodjemo do slobodnog mesta
        do
        {
            generate_food_position(&food.position.x,&food.position.z);  //Posto je hrana pojedena generisemo novu hranu
        } while (is_field_free(terrain.free_fields, food.position.x, food.position.z,terrain.row_num,terrain.col_num));
        size_up(&snake,1); //povecavamo zmijicu za 1 polje
       
    }
    glutPostRedisplay();
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL_SNAKE_CURR, on_timer, TIMER_ID);
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
    case 'p': //pauziramo
        animation_ongoing=0;
        break;
    case 'b': //pokrecemo
    
        if (animation_ongoing==0){
            animation_ongoing=1;
            glutTimerFunc(TIMER_INTERVAL_SNAKE_CURR, on_timer, TIMER_ID);
        }
            
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
    glutFullScreen();
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
    
    /*Incijalizacija zmijice, osvetljenja i teksture*/
    init_game(&snake,&food,&animation_ongoing,&terrain);
    init_light();
    init_texture();
    glutTimerFunc(TIMER_INTERVAL_SNAKE_CURR, on_timer, TIMER_ID);
    TIMER_INTERVAL_SNAKE_CURR=TIMER_INTERVAL_SNAKE_INIT; //inicijalizujemo trenutni tajmer zmijice
    glEnable(GL_DEPTH_TEST); //Ukljucujemo mogucnosti prikazivanja u 3D
    glutMainLoop();
    return 0;
}