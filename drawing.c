#include "drawing.h"
#include <GL/glut.h>
void init_light()
{
    float light_ambient[] = { 1, 1, 1, 1 };
    float light_diffuse[] = { 1, 1, 1, 1 };
    float light_specular[] = { 1, 1, 1, 1 };
    float light_position[] = { 1, 1, 1, 0 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
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
    float material_ambient[] = { 0, 1, 0, 1 };
        float material_diffuse[] = { 0, 1, 0, 1 };
        float material_specular[] = { 0.1, 0.1, 0.1, 1 };
        //float high_shininess[] = { 4 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
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
        {
                float material_ambient[] = { 1, 0, 0, 1 };
                float material_diffuse[] = { 1, 0, 0, 1 };
                float material_specular[] = { 0.1, 0.1, 0.1, 1 };
                //float high_shininess[] = { 4 };
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
               // glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
                
               // glColor3f(1,0,0);
                glTranslatef(snake->body[0].x,snake->body[0].y,snake->body[0].z);
                glutSolidCube(edge);
        }
        glPopMatrix();
        //Renderovanje tela zmijice
       // glColor3f(0,0,1);
        for (i=1;i<snake->size;i++)
        {
            /*Deo koda koji naizmenicno boji zmijicu*/
            if (i&1)  
            {
                 glColor3f(0,0,1);
                 
            }
            else
            {
                 glColor3f(0,1,0);
                
            }
            
            glPushMatrix();
            {
                float material_ambient[] = { 0, 0, 1, 1 };
                float material_diffuse[] = { 0, 0, 1, 1 };
                float material_specular[] = { 0.3, 0.3, 0.3, 1 };
               // float high_shininess[] = { 4};
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
                //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
                glTranslatef(snake->body[i].x,snake->body[i].y,snake->body[i].z);
                glutSolidCube(edge);
            }
                
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
  //  glColor3f(1,0,0);
    {
        float material_ambient[] = { 1, 0, 0, 1 };
        float material_diffuse[] = { 1, 0, 0, 1 };
        float material_specular[] = { 0.1, 0.1, 0.1, 1 };
        //float high_shininess[] = { 4 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
        glColor3f(0,1,1);
    }
    glPushMatrix(); //gore
        glTranslatef((U_FROM+U_TO)/2,0,V_FROM);
        glScalef(U_TO-U_FROM,1,1);
        glutSolidCube(edge);
    glPopMatrix();
    glPushMatrix(); //dole
        glTranslatef(-(U_FROM+U_TO)/2,0,-V_FROM);
        glScalef(U_TO-U_FROM,1,1);
        glutSolidCube(edge);
    glPopMatrix();
    glPushMatrix(); //levo
        glTranslatef(U_FROM,0,-(V_FROM+V_TO)/2);
        glScalef(1,1,V_TO-V_FROM);
        glutSolidCube(edge);
    glPopMatrix();
    glPushMatrix(); //desno
        glTranslatef(-U_FROM,0,(V_FROM+V_TO)/2);
        glScalef(1,1,V_TO-V_FROM);
        glutSolidCube(edge);
    glPopMatrix();

}
static void draw_plane(int U_FROM, int U_TO, int V_FROM, int V_TO)
{
    int u, v;
    glPushMatrix();
        {
            float material_ambient[] = { 0, 0, 0, 1 };
            float material_diffuse[] = { 0, 1, 1, 1 };
            float material_specular[] = { 0.1, 0.1, 0.1, 1 };
            //float high_shininess[] = { 4 };
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
           // glColor3f(0,1,1);
            for (u = U_FROM; u < U_TO; u++) { 
                glBegin(GL_TRIANGLE_STRIP);
                for (v = V_FROM; v <= V_TO; v++) {
                    set_vertex_and_normal(u, v, function_plane);
                    set_vertex_and_normal(u + 1, v, function_plane);
                }
                glEnd();
            }
        }
        
    glPopMatrix();
}
void draw_terrain(const Terrain* terrain)
{
  
    draw_plane(terrain->U_FROM,terrain->U_TO,terrain->V_FROM,terrain->V_TO); //crtamo ravan po kojoj se krecemo
    draw_border_of_terrain(terrain->U_FROM,terrain->U_TO,terrain->V_FROM,terrain->V_TO); //crtamo okvir za teren 
}