#include <GL/glut.h>
#include <stdio.h>
#define TIMER_ID 0
#define TIMER_INTERVAL 200

typedef struct {
    int x,y,z;
} Point;
typedef struct {
    Point *body;
    Point direction;
    int size;
} Snake;
Snake snake;
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void); 
static void draw_snake(void); /*Funkcija za iscrtavanje zmijice*/
static void move_snake(void); /*Pomeram se u smeru vektora direction*/
static void draw_coordinate_system(void); /*Postavljamo kordinatni sistem radi lakseg pozicioniranja buducih objekata*/
static int animation_ongoing; 
void on_display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(20, 20, 20, 
                0, 0, 0
                , 0, 1, 0);
     draw_coordinate_system();
   
     draw_snake();
     glutSwapBuffers();
}
void move_snake()
{
    int i;
    snake.body[0].x+=snake.direction.x;
    snake.body[0].y+=snake.direction.y;
    snake.body[0].z+=snake.direction.z;
    for (i=snake.size-1;i>0;i--)
    {
        snake.body[i].x=snake.body[i-1].x;
        snake.body[i].y=snake.body[i-1].y;
        snake.body[i].z=snake.body[i-1].z;
    }
}
void draw_snake()
{
    
        double edge=1;
        int i;
        glPushMatrix();
                glColor3f(1,0,0);
                glTranslatef(snake.body[0].x,snake.body[0].y,snake.body[0].z);
                glutSolidCube(edge);
        glPopMatrix();
        glColor3f(0,0,1);
        for (i=1;i<snake.size;i++)
        {
            /*if (i&1)
            {
                 glColor3f(0,0,1);
            }
            else
            {
                 glColor3f(0,1,0);
                
            }*/
            
            glPushMatrix();
                glTranslatef(snake.body[i].x,snake.body[i].y,snake.body[i].z);
                glutSolidCube(edge);
            glPopMatrix();
        }
}
static void on_timer(int value)
{
    if (value != TIMER_ID)
        return;
    move_snake();
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
    case 'f':
        animation_ongoing=0;
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

static void draw_coordinate_system()
{
    glPushMatrix();
        glColor3f(1,0,0); /* x-osa */
        glBegin(GL_LINES);
            glVertex3f(100,0,0);
            glVertex3f(-100,0,0);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0,1,0); /* y-osa */
        glBegin(GL_LINES); 
            glVertex3f(0,-100,0);
            glVertex3f(0,100,0);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glColor3f(0,0,1); /* z-osa */
        glBegin(GL_LINES);
            glVertex3f(0,0,100);
            glVertex3f(0,0,-100);
        glEnd();
    glPopMatrix();
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
 
    animation_ongoing = 1;
    /*Incijalizacija zmijice dok ne namestimo da zmijica raste kad pojede hranu*/
    const int size=30; /*duzina zmijice*/
    snake.body=malloc(sizeof(Point)*(size+1));
    snake.size=size;
    int i;
    for (i=0;i<size;i++)
    {
        snake.body[i].x=i;
        snake.body[i].y=0;
        snake.body[i].z=0;
    }
    snake.direction.x=-1;
    snake.direction.z=0;
    snake.direction.x=-1;
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}