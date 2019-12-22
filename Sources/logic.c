#include "../Headers/types.h"
#include "../Headers/logic.h"
#include "../Headers/map.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
int is_game_over;
void init_game(Snake *snake, Food *food,int *animation_ongoing,Terrain *terrain)
{
    food->r=0;
    food->g=1;
    food->b=0;
    srand(time(NULL)); //Incijalizacija seed-a
    const int size=5; /*duzina zmijice*/
    const int max_size=500; //velicina zmijice nece biti preko 500
    snake->body=malloc(sizeof(Point)*(max_size));
    snake->size=size;
    snake->direction.x=-1;
    snake->direction.z=0;
   // snake->direction.x=-1;
    generate_food_position(&food->position.x,&food->position.z);
    food->position.y=0;
    *animation_ongoing = 1;
    terrain->U_FROM=-17;
    terrain->U_TO=17;
    terrain->V_FROM=-15;
    terrain->V_TO=15;
    snake->score=19;
    int *free_fields=NULL;
    terrain->row_num=terrain->V_TO-terrain->V_FROM+1; //broj vrsta
    terrain->col_num=terrain->U_TO-terrain->U_FROM+1; //broj kolona
    int depth_num=7; //treba ce nam 7 matrice za mapiranje
    free_fields=malloc(sizeof(int)*terrain->row_num*terrain->col_num*depth_num+1);
    if (free_fields==NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i=0;i<size;i++)
    {
        snake->body[i].x=i;
        snake->body[i].y=0;
        snake->body[i].z=0;
        set_field(free_fields,snake->body[i].x,snake->body[i].y,1,terrain->row_num,terrain->col_num);
    }
    terrain->free_fields=free_fields;
}

static int generate_random_number(int a, int b)
{
    /* b > a */
    int r = abs((b-a)*sin(rand()))+a;
    //printf("%d",r);
    return r;
}
void generate_food_position(int *x, int *z)
{
    const int low=-13;
    const int high=13;
    *x=generate_random_number(low,high);
    *z=generate_random_number(low,high);
}
int is_food_eaten(const Snake *snake,const Food *food)
{
    if (food->position.x==snake->body[0].x && food->position.y==snake->body[0].y && food->position.z==snake->body[0].z)
    {
        return 1;
    }
    return 0;
}
void increase_score(Snake* snake, int val) 
{
    snake->score+=val;
}
void size_up(Snake *snake, int n)
{
    // n za koliko da poraste
    Point last;
    Point before_last;
    Point current;
    memcpy((void *)&last,&(snake->body[snake->size-1]),sizeof(Point));
    memcpy((void *)&before_last,&(snake->body[snake->size-2]),sizeof(Point));
    memcpy((void *)&current,&(snake->body[snake->size-1]),sizeof(Point)); //Postavljamo trenutni na poslednji
    Point dir; //direction 
    dir.x=last.x-before_last.x;
    dir.y=last.y-before_last.y;
    dir.z=last.z-before_last.z;
    for (int i=0;i<n;i++)
    {
        current.x+=dir.x;
        current.y+=dir.y;
        current.z+=dir.z;
        snake->body[snake->size].x = current.x;
        snake->body[snake->size].y = current.y;
        snake->body[snake->size].z= current.z;
        snake->size++;
    }
    
}
int is_snake_touch_border(Snake *snake, const Terrain *terrain)
{
    //gledamo da li postoji presek sa bilo kojom ivicom
    if (terrain->U_FROM==snake->body[0].x+snake->direction.x || terrain->U_TO==snake->body[0].x+snake->direction.x || terrain->V_FROM==snake->body[0].z+snake->direction.z || terrain->V_TO==snake->body[0].z+snake->direction.z)
    {
        return 1;
    }
    return 0;
}
void move_snake(Snake *snake,const Terrain *terrain)
{
    //printf("%d\n",generate_random_number(2,10));
    int i;
    set_field(terrain->free_fields,snake->body[snake->size-1].x,snake->body[snake->size-1].z,0,terrain->row_num,terrain->col_num);
    /*Deo koda koji pomera zmijicu i detektuje ako je bilo kolizije*/
    for (i=snake->size-1;i>0;i--)
    {
        //Detektovanje "SAMOUJEDA"
        if (snake->body[i].x==snake->body[0].x+snake->direction.x && snake->body[i].y==snake->body[0].y+snake->direction.y && snake->body[i].z==snake->body[0].z+snake->direction.z || (is_snake_touch_border(snake,terrain)))
        {
            is_game_over=1;
            //exit(0);      
        }
        snake->body[i].x=snake->body[i-1].x;
        snake->body[i].y=snake->body[i-1].y;
        snake->body[i].z=snake->body[i-1].z;
    }
    snake->body[0].x+=snake->direction.x;
    snake->body[0].y+=snake->direction.y;
    snake->body[0].z+=snake->direction.z;
    set_field(terrain->free_fields,snake->body[0].x,snake->body[0].z,1,terrain->row_num,terrain->col_num);
    
       
}