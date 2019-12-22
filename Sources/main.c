#include <GL/glut.h>
#include <stdio.h>
#include "../Headers/drawing.h"
#include "../Headers/types.h"
#include "../Headers/logic.h"
#include "../Headers/map.h"
#define TIMER_ID 0
#define TIMER_ID1 1
static Snake snake;
static Food food;
static Food bonus;
static Terrain terrain;
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void); 
static int animation_ongoing;
extern int animation_parametar;
static int TIMER_INTERVAL_SNAKE_INIT=100; //pocinjemo sa 100ms
static int TIMER_INTERVAL_SNAKE_CURR; //zadajemo trenutni interval tajmera
//TO DO Implementirati mehanizam za oslobadjanje memorije
static int TIMER_BONUS=1800;
int is_bonus_active=0;
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
        if (snake.score%10==0 && is_bonus_active)
        {
             draw_food(&bonus);
        }
        draw_terrain(&terrain);
        draw_score(&snake);
     }
     else
     {
         draw_game_over(&snake);
     }
    
     glutSwapBuffers();
}
static void timeout_bonus(int value)
{
     if (value != TIMER_ID1)
        return;
     is_bonus_active=0;
     
}
static void on_timer(int value)
{
    if (value != TIMER_ID)
        return;
    animation_parametar++;
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
        } while (!is_field_free(terrain.free_fields, food.position.x, food.position.z,terrain.row_num,terrain.col_num));
        size_up(&snake,1); //povecavamo zmijicu za 1 polje
        if (snake.score%10==0) //ako smo dosli do skora za generisanje bonus vockice
        {
            //generisemo sve dok ne pogodimo slobodno polje
            do
            {
                generate_food_position(&bonus.position.x,&bonus.position.z);
            } while (!is_field_free(terrain.free_fields, bonus.position.x, bonus.position.z,terrain.row_num,terrain.col_num) ||( bonus.position.x==food.position.x && bonus.position.z==food.position.z));
           is_bonus_active=1;
           glutTimerFunc(TIMER_BONUS,timeout_bonus,TIMER_ID1);  //postavljamo da nestane bonus nakon TIMER_BONUS ms
        }
    }     
    if (is_food_eaten(&snake,&bonus) && is_bonus_active) //ako smo pojeli bonusnu vockicu
    {
        snake.score+=5;
        is_bonus_active=0;
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
    case 'A':
        if (snake.direction.x==1) break;
        snake.direction.x=-1;
        snake.direction.z=0;  
        break;
    case 'd':
    case 'D':
        if (snake.direction.x==-1) break;
        snake.direction.x=+1;
        snake.direction.z=0;
        break;
    case 'w':
    case 'W':
        if (snake.direction.z==1) break;
        snake.direction.x=0;
        snake.direction.z=-1;
        break;
    case 's':
    case 'S':
        if (snake.direction.z==-1) break;
        snake.direction.x=0;
        snake.direction.z=1;
        break;
    case 'p': //pauziramo
    case 'P':
        animation_ongoing=0;
        break;
    case 'b': //pokrecemo
    case 'B':
    
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
    animation_parametar=0; //inicijalizujemo animacioni parametar
    //Inicijalizujemo boju bonusa na plavu
    bonus.r=0;
    bonus.g=0;
    bonus.b=1;
    glEnable(GL_DEPTH_TEST); //Ukljucujemo mogucnosti prikazivanja u 3D
    glutMainLoop();
    return 0;
}