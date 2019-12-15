#ifndef MAP_H
#define MAP_H
static int offset(int x, int y, int z,int row_num,int col_num); //mapiramo 3d matricu u 1d niz
static int code_val(int x,int y); //kodiramo da bi znali kako da mapiramo
void set_field(int *free_fields,int x, int y,int flag,int row_num,int col_num); //Postavlja zauzeto/slobodno polje
int is_field_free(int *free_fields,int x, int y,int row_num,int col_num); //Proverava da li je polje slobodno
#endif