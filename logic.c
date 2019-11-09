#include "types.h"
#include "logic.h"

void move_snake(Snake *snake)
{
    int i;
  
    for (i=snake->size-1;i>0;i--)
    {
        snake->body[i].x=snake->body[i-1].x;
        snake->body[i].y=snake->body[i-1].y;
        snake->body[i].z=snake->body[i-1].z;
    }
    snake->body[0].x+=snake->direction.x;
    snake->body[0].y+=snake->direction.y;
    snake->body[0].z+=snake->direction.z;
       
}