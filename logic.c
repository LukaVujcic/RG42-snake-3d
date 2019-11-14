#include "types.h"
#include "logic.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
static int generate_random_number(int a, int b)
{
    /* b > a */
    srand(time(NULL));
    int r = rand()%(b-a+1)+a;
    return r;
}
void generate_food(int *a, int *b)
{
    const int low=-30;
    const int high=30;
    *a=generate_random_number(low,high);
    *b=generate_random_number(low,high);
}
void move_snake(Snake *snake)
{
    //printf("%d\n",generate_random_number(2,10));
    int i;
    
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