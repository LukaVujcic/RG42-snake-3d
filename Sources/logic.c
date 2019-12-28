#include "../Headers/types.h"
#include "../Headers/logic.h"
#include "../Headers/map.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
int is_game_over;
int lock;
void init_game(Snake *snake, Food *food,int *animation_ongoing,Terrain *terrain)
{
    //Inicijalizujemo obicne vockice na zelenu boju
    food->r=0;
    food->g=1;
    food->b=0;
    srand(time(NULL)); //Incijalizacija seed-a
    const int size=5; /*pocetna duzina zmijice*/
    const int max_size=500; //velicina zmijice nece biti preko 500
    snake->body=malloc(sizeof(Point)*(max_size));
    if (snake->body==NULL)
    {
        fprintf(stderr,"Nedovoljno memorije!\n");
        exit(EXIT_FAILURE);
    }
    //Inicijalizujemo velicinu zmijice, vektor kretanja i skor
    snake->size=size;
    snake->direction.x=-1;
    snake->direction.z=0;
    snake->score=0;
    //generisemo hranu
    generate_food_position(&food->position.x,&food->position.z);
    food->position.y=0;
    //postavljamo flag da je igra u toku
    *animation_ongoing = 1;
    //zadajemo dimenzije terena
    terrain->U_FROM=-17;
    terrain->U_TO=17;
    terrain->V_FROM=-15;
    terrain->V_TO=15;
    int *free_fields=NULL;
    //zadajemo potreban broj polja za mapiranje terena
    terrain->row_num=terrain->V_TO-terrain->V_FROM+1; //broj vrsta
    terrain->col_num=terrain->U_TO-terrain->U_FROM+1; //broj kolona
    int depth_num=7; //treba ce nam 7 matrice za mapiranje
    free_fields=malloc(sizeof(int)*terrain->row_num*terrain->col_num*depth_num+1);
    if (free_fields==NULL)
    {
        fprintf(stderr,"Nedovoljno memorije!\n");
        exit(EXIT_FAILURE);
    }
    //postavljamo koord zmijice, ovde ce zmijica zauzeti polja u svojoj duzini
    for (int i=0;i<size;i++)
    {
        snake->body[i].x=i;
        snake->body[i].y=0;
        snake->body[i].z=0;
        //polja koja je zauzela zmijica markiramo kao zauzeta
        set_field(free_fields,snake->body[i].x,snake->body[i].y,1,terrain->row_num,terrain->col_num);
    }
    //pokazivac na podatke o zauzetim poljima prebacujemo u strukturu
    terrain->free_fields=free_fields;
}

static int generate_random_number(int a, int b)
{
    /* b > a */
    //funkcija koju koristimo za random broj
    int r = abs((b-a)*sin(rand()))+a;
    //printf("%d",r);
    return r;
}
void generate_food_position(int *x, int *z)
{
    //koordinate hrane su celobrojne koordinate iz oblasti [-13, 13]x[-13, 13]
    const int low=-13;
    const int high=13;
    *x=generate_random_number(low,high);
    *z=generate_random_number(low,high);
}
int is_food_eaten(const Snake *snake,const Food *food)
{   
    //uslov koji odredjuje da li smo pojeli hranu
    if (food->position.x==snake->body[0].x && food->position.y==snake->body[0].y && food->position.z==snake->body[0].z) 
    {
        return 1;
    }
    return 0;
}
void increase_score(Snake* snake, int val) 
{
    snake->score+=val;
}
void size_up(Snake *snake, int n)
{
    // n za koliko da poraste
    Point last;
    Point before_last;
    Point current;
    /*Deo koda koji kopira strukture,jer ne mozemo pisati 
        last=snake->body[snake->size-1];
        before_last=snake->body[snake->size-2];
        current=snake->body[snake->size-1];
    */
    memcpy((void *)&last,&(snake->body[snake->size-1]),sizeof(Point));
    memcpy((void *)&before_last,&(snake->body[snake->size-2]),sizeof(Point));
    memcpy((void *)&current,&(snake->body[snake->size-1]),sizeof(Point)); //Postavljamo trenutni na poslednji
    Point dir; //direction pokazuje na pravac koji zadaje rep zmije
    dir.x=last.x-before_last.x;
    dir.y=last.y-before_last.y;
    dir.z=last.z-before_last.z;
    for (int i=0;i<n;i++)
    {
        //odredjuje poziciju na koju treba da stavimo blok
        current.x+=dir.x;
        current.y+=dir.y;
        current.z+=dir.z;
        snake->body[snake->size].x = current.x;
        snake->body[snake->size].y = current.y;
        snake->body[snake->size].z= current.z;
        snake->size++; //azuriramo velicinu zmijice
    }
}
int is_snake_touch_border(Snake *snake, const Terrain *terrain)
{
    //gledamo da li postoji presek sa bilo kojom ivicom
    if (terrain->U_FROM==snake->body[0].x+snake->direction.x || terrain->U_TO==snake->body[0].x+snake->direction.x || terrain->V_FROM==snake->body[0].z+snake->direction.z || terrain->V_TO==snake->body[0].z+snake->direction.z)
    {
        return 1;
    }
    return 0;
}
void move_snake(Snake *snake,const Terrain *terrain)
{
    int i;
    //oslobadjamo polje na kojem je bio rep zmijice
    set_field(terrain->free_fields,snake->body[snake->size-1].x,snake->body[snake->size-1].z,0,terrain->row_num,terrain->col_num);
    /*Deo koda koji pomera zmijicu i detektuje ako je bilo kolizije*/
    for (i=snake->size-1;i>0;i--)
    {
        //Detektovanje "SAMOUJEDA"
        if (snake->body[i].x==snake->body[0].x+snake->direction.x && snake->body[i].y==snake->body[0].y+snake->direction.y && snake->body[i].z==snake->body[0].z+snake->direction.z || (is_snake_touch_border(snake,terrain)))
        {
            is_game_over=1;      
        }
        //pomeramo telo zmijice
        snake->body[i].x=snake->body[i-1].x;
        snake->body[i].y=snake->body[i-1].y;
        snake->body[i].z=snake->body[i-1].z;
    }
    //pomeramo glavu
    snake->body[0].x+=snake->direction.x;
    snake->body[0].y+=snake->direction.y;
    snake->body[0].z+=snake->direction.z;
    //markiramo polje kao zauzeto trenutnu poziciju glave zmijice
    set_field(terrain->free_fields,snake->body[0].x,snake->body[0].z,1,terrain->row_num,terrain->col_num);
    lock=0; //oslobadjamo katanac sa kontrola
       
}