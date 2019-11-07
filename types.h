#ifndef TYPES_H
#define TYPES_H
typedef struct {
    int x,y,z;
} Point;
typedef struct {
    Point *body;
    Point direction; /*Vektor koji pokazuje trenutni smer/pravac kretanja zmijice*/
    int size;
} Snake;
#endif