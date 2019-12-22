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

typedef struct { /*TO DO obavezno dodati razlicite tipove hrane*/
    Point position;
    double r,g,b;
} Food;
typedef struct{
    int U_FROM, U_TO, V_FROM, V_TO;
    int row_num,col_num;
    int *free_fields;
} Terrain;
#endif