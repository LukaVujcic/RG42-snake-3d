#include "../Headers/map.h"
#include <stdlib.h>
const int depth_move=3; //koristimo kao pomeraj jer ne mozemo da mapiramo negativne vrednosti pomocu code
static int offset(int x, int y, int z,int row_num,int col_num) 
{ 
    return (z * row_num * col_num) + (y * row_num) + x; 
}
static int code_val(int x,int y)
{
    int code=0;
    if (x > 0)
    {
        code+=2;
    }
    if (x < 0)
    {
        code-=2;
    }
    if (y > 0)
    {
        code+=1;
    }
    if (y < 0)
    {
        code-=1;
    }
    return code;
}
void set_field(int *free_fields,int x, int y,int flag,int row_num,int col_num)
{
    int code=code_val(x,y); //Koristimo code da kodiramo kojoj matrici od depth matrica postavljamo vrednost
 
    free_fields[offset(abs(x),abs(y),code+depth_move,row_num,col_num)]=flag; 
}
int is_field_free(int *free_fields,int x, int y,int row_num,int col_num)
{
    int code=code_val(x,y);
    return !free_fields[offset(abs(x),abs(y),code+depth_move,row_num,col_num)];
}