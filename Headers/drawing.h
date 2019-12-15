#ifndef DRAWING_H
#define DRAWING_H
#include "types.h"
void draw_coordinate_system(void); /*Postavljamo kordinatni sistem radi lakseg pozicioniranja buducih objekata*/
void draw_snake(Snake *snake); /*Funkcija za iscrtavanje zmijice*/
void draw_food(const Food *food); //Funkcija za crtanje hrane
static void set_vertex_and_normal(double u, double v,double (*function)(double,double)); //postavljanje normale i crtanje tacke po funkciji function
static void draw_border_of_terrain(int U_FROM, int U_TO, int V_FROM, int V_TO); //crtanje granice terena
static void draw_plane(int U_FROM, int U_TO, int V_FROM, int V_TO); //crtanje ravni
void draw_terrain(const Terrain* terrain); //crtanje terena
void init_light(void); //Inicijalizacija osvetljenja
void init_texture(void); //Inicijalizacija tekstura
static void apply_texture_cube(double edge,int texture_name); //Postavlja teksturu na proizvoljnu kocku
static void renderBitmapString(int x, int y,int z,void* font, char *string);
void draw_score(const Snake* snake);
#endif
