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
void draw_food(const Food *food)
{
    double edge=1;
    glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(food->position.x,food->position.y,food->position.z); //Svaku kocku pozicioniramo da zadate koordinate
        glutSolidCube(edge);
    glPopMatrix();
}
void draw_snake(Snake *snake)
{
        double edge=1;
        int i;
        // Renderovanje glave zmijice
        glPushMatrix();
                glColor3f(1,0,0);
                glTranslatef(snake->body[0].x,snake->body[0].y,snake->body[0].z);
                glutSolidCube(edge);
        glPopMatrix();
        //Renderovanje tela zmijice
        glColor3f(0,0,1);
        for (i=1;i<snake->size;i++)
        {
            /*Deo koda koji naizmenicno boji zmijicu*/
           /* if (i&1)  
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
void set_vertex_and_normal(double u, double v,double (*function)(double,double))
{
     //Povrs je paramtrizovana sa u i v
    double diff_u, diff_v;
    //Racunamo parcijalne izvode po u i v
    diff_u = (function(u + 1, v)
             - function(u - 1, v)) / 2.0;
    diff_v = (function(u, v + 1)
             - function(u, v - 1)) / 2.0;
    //Postavljamo normalu kao gradijent
    glNormal3f(-diff_u, 1, -diff_v);
    //Tacka koju iscrtavamo
    glVertex3f(u, function(u, v), v);

}
static double function_plane(double u,double v)//funkcija je f(u,v)=c, zadaje ravan y=c
{
    double c=-0.5; // uzeto je 0.5 kao edge/2, jer je edge duzina ivice kocke
    return c;
}
static void draw_border_of_terrain(int U_FROM, int U_TO, int V_FROM, int V_TO)
{
    double edge=1;
    glColor3f(1,0,0);

    glPushMatrix(); //gore
        glTranslatef((U_FROM+U_TO)/2,0,V_FROM+edge/2);
        glScalef(U_TO-U_FROM,1,1);
        glutSolidCube(edge);
    glPopMatrix();
    glPushMatrix(); //dole
        glTranslatef(-(U_FROM+U_TO)/2,0,-V_FROM-edge/2);
        glScalef(U_TO-U_FROM,1,1);
        glutSolidCube(edge);
    glPopMatrix();
    glPushMatrix(); //levo
        glTranslatef(U_FROM+edge/2,0,-(V_FROM+V_TO)/2);
        glScalef(1,1,V_TO-V_FROM);
        glutSolidCube(edge);
    glPopMatrix();
    glPushMatrix(); //desno
        glTranslatef(-U_FROM-edge/2,0,(V_FROM+V_TO)/2);
        glScalef(1,1,V_TO-V_FROM);
        glutSolidCube(edge);
    glPopMatrix();

}
static void draw_plane(int U_FROM, int U_TO, int V_FROM, int V_TO)
{
    int u, v;
    glPushMatrix();
        glColor3f(0,1,1);
        for (u = U_FROM; u < U_TO; u++) { 
            glBegin(GL_TRIANGLE_STRIP);
            for (v = V_FROM; v <= V_TO; v++) {
                set_vertex_and_normal(u, v, function_plane);
                set_vertex_and_normal(u + 1, v, function_plane);
            }
            glEnd();
        }
    glPopMatrix();
}
void draw_terrain()
{
    int U_FROM=-17;
    int U_TO=17;
    int V_FROM=-15;
    int V_TO=15;
    draw_plane(U_FROM,U_TO,V_FROM,V_TO); //crtamo ravan po kojoj se krecemo
    draw_border_of_terrain(U_FROM,U_TO,V_FROM,V_TO); //crtamo okvir za teren 
}