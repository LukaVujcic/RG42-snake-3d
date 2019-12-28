#ifndef TYPES_H
#define TYPES_H
typedef struct {
    int x,y,z;
} Point;

typedef struct {
    Point *body;
    Point direction; /*Vektor koji pokazuje trenutni smer/pravac kretanja zmijice*/
    int size;
    int score;
    
} Snake;

typedef struct {
    Point position;
    double r,g,b; //zadajemo boju vockice
} Food;
typedef struct{
    int U_FROM, U_TO, V_FROM, V_TO; //dimenzije terena
    int row_num,col_num; //matrica koja mapira slobodna i zauzeta polja
    int *free_fields;
} Terrain;
#endif