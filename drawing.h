#ifndef DRAWING_H
#define DRAWING_H
#include "types.h"
void draw_coordinate_system(void); /*Postavljamo kordinatni sistem radi lakseg pozicioniranja buducih objekata*/
void draw_snake(Snake *snake); /*Funkcija za iscrtavanje zmijice*/
void draw_food(const Food *food); //Funkcija za crtanje hrane
#endif