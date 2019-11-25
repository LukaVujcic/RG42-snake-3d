#include "types.h"
#include "logic.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void init_game(Snake *snake, Food *food,int *animation_ongoing)
{
    srand(time(NULL)); //Incijalizacija seed-a
    const int size=2; /*duzina zmijice*/
    const int max_size=500; //velicina zmijice nece biti preko 500
    snake->body=malloc(sizeof(Point)*(500));
    snake->size=size;
    int i;
    for (i=0;i<size;i++)
    {
        snake->body[i].x=i;
        snake->body[i].y=0;
        snake->body[i].z=0;
    }
    snake->direction.x=-1;
    snake->direction.z=0;
    snake->direction.x=-1;
    generate_food_position(&food->position.x,&food->position.z);
    food->position.y=0;
    *animation_ongoing = 1;
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
    const int low=-12;
    const int high=12;
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
void move_snake(Snake *snake)
{
    //printf("%d\n",generate_random_number(2,10));
    int i;
    /*Deo koda koji pomera zmijicu i detektuje ako je bilo kolizije*/
    for (i=snake->size-1;i>0;i--)
    {
        //Detektovanje "SAMOUJEDA"
        if (snake->body[i].x==snake->body[0].x+snake->direction.x && snake->body[i].y==snake->body[0].y+snake->direction.y && snake->body[i].z==snake->body[0].z+snake->direction.z)
        {
            exit(0);      
        }
        snake->body[i].x=snake->body[i-1].x;
        snake->body[i].y=snake->body[i-1].y;
        snake->body[i].z=snake->body[i-1].z;
    }
    snake->body[0].x+=snake->direction.x;
    snake->body[0].y+=snake->direction.y;
    snake->body[0].z+=snake->direction.z;
    
       
}