#include "../Headers/drawing.h"
#include "../Headers/image.h"
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
static int texture_names[3];
#define FILENAME0 "../Textures/wood.bmp"
#define FILENAME1 "../Textures/brick.bmp"
#define FILENAME2 "../Textures/skin.bmp"
#define MAX_LENGTH_STRING 50
int animation_parametar;
static char word[MAX_LENGTH_STRING]; //Koristimo staticku alokaciju za reci koje ispisujemo, dali smo pretpostavku o njihovoj duzini
static void renderStrokeString(int x, int y,int z,void* font, char *string) 
{
    int len; //duzina stringa
    glDisable(GL_LIGHTING); //Privremeno iskljucujemo osvetljenje da bi postavili boju teksta
    glColor3f(1,0,0); //Postavljanje boje teksta
    //glRasterPos3f(x,y,z);
    //Postavljamo dimenzije slova
    glScalef(0.01,0.01,5);
    glTranslatef(x,y,z);
    len = strlen(string);
    for (int i = 0; i < len; i++)
    {
        glutStrokeCharacter(font, string[i]);
    }
    glEnable(GL_LIGHTING); //Ponovo ukljucujemo osvetljenje
}
void draw_score(const Snake* snake)
{
    sprintf(word,"Score: %d",snake->score);
    /* Postavljamo koordinate ispisivanja teksta*/
    const int x = -350;
    const int y = 1200;
    const int z = 0;
    glPushMatrix();
        glPushAttrib(GL_LINE_BIT);
            glLineWidth(4); //Postavljamo debljinu linije
            renderStrokeString(x,y,z,GLUT_STROKE_MONO_ROMAN,word);
        glPopAttrib();
    glPopMatrix();
}
void draw_game_over(const Snake* snake)
{   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1, 
                    0, 0, 0
                    , 0, 1, 0);
    //Koordinate za ispis teksta
    const int x = -500;
    const int y = 0;
    const int z = 0;
    /*Deo za ispisivanje "game over"*/
    sprintf(word,"Game over!");
    glPushMatrix();
        glScalef(0.05,0.05,5);
        glPushAttrib(GL_LINE_BIT);
            glLineWidth(4); //Postavljamo debljinu linije
            renderStrokeString(x,y,z,GLUT_STROKE_MONO_ROMAN,word);
        glPopAttrib();
    glPopMatrix();
    /*Deo za ispisivanje skora*/
    sprintf(word,"Score: %d",snake->score);
    glPushMatrix();
        glScalef(0.05,0.05,5);
        glPushAttrib(GL_LINE_BIT);
            glLineWidth(4); //Postavljamo debljinu linije
            renderStrokeString(x+100,y-200,z,GLUT_STROKE_MONO_ROMAN,word);
        glPopAttrib();
    glPopMatrix();
}
void init_texture(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;
    /* Ukljucujemo opciju koriscenja tekstura. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_MODULATE);

    /*
        Ucitavamo sliku koja predstavlja teksturu
    */
    image = image_init(0, 0);

    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(3, texture_names);

    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    /* Iskljucujemo teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /*Ucitavamo drugu strukturu*/
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, texture_names[1]);
     glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    /* Oslobadjamo objekat iz memorije */

    image_read(image, FILENAME2);

    glBindTexture(GL_TEXTURE_2D, texture_names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    image_done(image);

}
void init_light(void)
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
    double edge=0.8;
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
        glRotatef((90*cos(animation_parametar/5.0)),0,1,0); //okrecemo ga za [-90,90] stepeni
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
                float material_ambient[] = { 0.3, 0, 0, 1 };
                float material_diffuse[] = { 1, 0, 0, 1 };
                float material_specular[] = { 0.7, 0, 0, 1 };
                //float high_shininess[] = { 4 };
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
               // glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

               // glColor3f(1,0,0);
                glTranslatef(snake->body[0].x,snake->body[0].y,snake->body[0].z);
                apply_texture_cube(edge,texture_names[2]);

                //glutSolidCube(edge);
        }
        glPopMatrix();
        //Renderovanje tela zmijice
       // glColor3f(0,0,1);
        for (i=1;i<snake->size;i++)
        {
            /*Deo koda koji naizmenicno boji zmijicu*/
            /*if (i&1)
            {
                 glColor3f(0,0,1);

            }
            else
            {
                 glColor3f(0,1,0);

            }*/

            glPushMatrix();
            {
                float material_ambient[] = { 0, 0, 1, 1 };
                float material_diffuse[] = { 0, 0, 1, 1 };
                float material_specular[] = { 1, 1, 1, 1 };
               // float high_shininess[] = { 4};
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
                //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
                glTranslatef(snake->body[i].x,snake->body[i].y,snake->body[i].z);
                apply_texture_cube(edge,texture_names[2]);
                //glutSolidCube(edge);
            }

            glPopMatrix();
        }
}
static void set_vertex_and_normal(double u, double v,double (*function)(double,double))
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
    //Postavljamo texel, ovim zadajemo odgovarajuce mapiranje
    glTexCoord2f(u / 20,v / 20);
    //Tacka koju iscrtavamo
    glVertex3f(u, function(u, v), v);

}
static void apply_texture_cube(double edge,int texture)
{
    int coef_of_mapping=1;
    double offset=0.01;
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix(); //prednja strana

            glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex3f(-edge/2, -edge/2, edge/2);
                glTexCoord2f(0, edge);
                glVertex3f(-edge/2, edge/2, edge/2);
                glTexCoord2f(edge*coef_of_mapping , edge);
                glVertex3f(edge/2, edge/2, edge/2);
                glTexCoord2f(edge*coef_of_mapping, 0);
                glVertex3f(edge/2, -edge/2, edge/2);
            glEnd();
    glPopMatrix();

     //zadnja strana
    glPushMatrix();

            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(-edge/2, -edge/2, -edge/2);
                glTexCoord2f(0, edge);
                glVertex3f(-edge/2, edge/2, -edge/2);
                glTexCoord2f(edge*coef_of_mapping, edge);
                glVertex3f(edge/2, edge/2, -edge/2);
                glTexCoord2f(edge*coef_of_mapping, 0);
                glVertex3f(edge/2, -edge/2, -edge/2);
            glEnd();

    glPopMatrix();



    glPushMatrix(); //gornja strana

            glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex3f(-edge/2, edge/2,edge/2);
                glTexCoord2f(0, edge);
                glVertex3f(-edge/2, edge/2,-edge/2);
                glTexCoord2f(edge*coef_of_mapping, edge);
                glVertex3f(edge/2, edge/2,-edge/2);
                glTexCoord2f(edge*coef_of_mapping, 0);
                glVertex3f(edge/2, edge/2,edge/2);
            glEnd();


    glPopMatrix();

    glPushMatrix(); //leva strana

            glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex3f(-edge/2-offset, -edge/2,edge/2);
                glTexCoord2f(0, edge);
                glVertex3f(-edge/2-offset, edge/2,edge/2);
                glTexCoord2f(edge*coef_of_mapping, edge);
                glVertex3f(-edge/2-offset, edge/2,-edge/2);
                glTexCoord2f(edge*coef_of_mapping, 0);
                glVertex3f(-edge/2-offset, -edge/2,-edge/2);
            glEnd();


    glPopMatrix();
    glPushMatrix(); //desna strana

            glBegin(GL_QUADS);
                glTexCoord2f(0 , 0);
                glVertex3f(edge/2+offset, -edge/2,edge/2);
                glTexCoord2f(0, edge);
                glVertex3f(edge/2+offset, edge/2,edge/2);
                glTexCoord2f(edge*coef_of_mapping , edge);
                glVertex3f(edge/2+offset, edge/2,-edge/2);
                glTexCoord2f(edge*coef_of_mapping, 0);
                glVertex3f(edge/2+offset, -edge/2,-edge/2);
            glEnd();


    glPopMatrix();
   
    glBindTexture(GL_TEXTURE_2D, 0);
}
static double function_plane(double u,double v)//funkcija je f(u,v)=c, zadaje ravan y=c
{
    double c=-0.5; // uzeto je 0.5 kao edge/2, jer je edge duzina ivice kocke
    return c;
}
static void draw_border_of_terrain(int U_FROM, int U_TO, int V_FROM, int V_TO)
{
    double edge=1;
    glColor3f(0,0,0);
    glPushMatrix();
    {
        float material_ambient[] = { 0.5, 0.5, 0.5, 1 };
        float material_diffuse[] = { 1, 0, 0, 1 };
        float material_specular[] = { 0.5, 0.5, 0.5, 1 };
        //float high_shininess[] = { 4 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
        //glColor3f(0,1,1);

        const int coef_of_mapping=10; //koeficijent mapiranja teksture
        glBindTexture(GL_TEXTURE_2D, texture_names[1]);
        glPushMatrix(); //gornji zid
            glTranslatef((U_FROM+U_TO)/2,0,V_FROM);
            glScalef(U_TO-U_FROM,4,1);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glTexCoord2f(0,0);
                    glVertex3f(-edge/2, -edge/2, edge/2);
                    glTexCoord2f(0, edge);
                    glVertex3f(-edge/2, edge/2, edge/2);
                    glTexCoord2f(edge*coef_of_mapping , edge);
                    glVertex3f(edge/2, edge/2, edge/2);
                    glTexCoord2f(edge*coef_of_mapping, 0);
                    glVertex3f(edge/2, -edge/2, edge/2);
                    glEnd();
                glutSolidCube(edge);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix(); //donji zid
            glTranslatef(-(U_FROM+U_TO)/2,0,-V_FROM);
            glScalef(U_TO-U_FROM,4,1);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 0);
                    glVertex3f(-edge/2, -edge/2, edge/2);
                    glTexCoord2f(0, edge);
                    glVertex3f(-edge/2, edge/2, edge/2);
                    glTexCoord2f(edge*coef_of_mapping, edge);
                    glVertex3f(edge/2, edge/2, edge/2);
                    glTexCoord2f(edge*coef_of_mapping, 0);
                    glVertex3f(edge/2, -edge/2, edge/2);
                    glEnd();
                glutSolidCube(edge);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix(); //levi zid
            glTranslatef(U_FROM,0,-(V_FROM+V_TO)/2);
        // glRotatef(90,0,1,0);
            glScalef(1,4,V_TO-V_FROM);
            glPushMatrix();
                glBegin(GL_QUADS);
                    double offset=0.01;
                    glTexCoord2f(0,0);
                    glVertex3f(edge/2+offset, -edge/2,edge/2);
                    glTexCoord2f(0, edge);
                    glVertex3f(edge/2+offset, edge/2,edge/2);
                    glTexCoord2f(edge*coef_of_mapping, edge);
                    glVertex3f(edge/2+offset, edge/2,-edge/2);
                    glTexCoord2f(edge*coef_of_mapping, 0);
                    glVertex3f(edge/2+offset, -edge/2,-edge/2);
                    glEnd();
                glutSolidCube(edge);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix(); //desni zid
            glTranslatef(-U_FROM,0,(V_FROM+V_TO)/2);
        // glRotatef(90,0,1,0);
            glScalef(1,4,V_TO-V_FROM);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glTexCoord2f(0 , 0);
                    glVertex3f(-edge/2, -edge/2,edge/2);
                    glTexCoord2f(0, edge);
                    glVertex3f(-edge/2, edge/2,edge/2);
                    glTexCoord2f(edge*coef_of_mapping , edge);
                    glVertex3f(-edge/2, edge/2,-edge/2);
                    glTexCoord2f(edge*coef_of_mapping, 0);
                    glVertex3f(-edge/2, -edge/2,-edge/2);
                glEnd();
                glutSolidCube(edge);
            glPopMatrix();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();
}
static void draw_plane(int U_FROM, int U_TO, int V_FROM, int V_TO)
{
    int u, v;
    glPushMatrix();
    {
            float material_ambient[] = { 0, 0, 0, 1 };
            float material_diffuse[] = { 0.7, 0.7, 0.7, 1 };
            float material_specular[] = { 0, 0, 0, 1 };
            //float high_shininess[] = { 4 };
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
            glBindTexture(GL_TEXTURE_2D, texture_names[0]);
           // glColor3f(0,1,1);
            for (u = U_FROM; u < U_TO; u++) {
                glBegin(GL_TRIANGLE_STRIP);
                for (v = V_FROM; v <= V_TO; v++) {
                    set_vertex_and_normal(u, v, function_plane);
                    set_vertex_and_normal(u + 1, v, function_plane);
                }
                glEnd();
            }
            glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

}
void draw_terrain(const Terrain* terrain)
{
    draw_plane(terrain->U_FROM,terrain->U_TO,terrain->V_FROM,terrain->V_TO); //crtamo ravan po kojoj se krecemo
    draw_border_of_terrain(terrain->U_FROM,terrain->U_TO,terrain->V_FROM,terrain->V_TO); //crtamo okvir za teren
}
