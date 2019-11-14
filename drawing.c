#include "drawing.h"
#include <GL/glut.h>

void draw_coordinate_system()
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
void draw_food(int x, int y, int z)
{
    double edge=1;
    glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(x,y,z);
        glutSolidCube(edge);
    glPopMatrix();
}
void draw_snake(Snake *snake)
{
        double edge=1;
        int i;
        glPushMatrix();
                glColor3f(1,0,0);
                glTranslatef(snake->body[0].x,snake->body[0].y,snake->body[0].z);
                glutSolidCube(edge);
        glPopMatrix();
        glColor3f(0,0,1);
        for (i=1;i<snake->size;i++)
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
                glTranslatef(snake->body[i].x,snake->body[i].y,snake->body[i].z);
                glutSolidCube(edge);
            glPopMatrix();
        }
}