#ifndef LOGIC_H
#define LOGIC_H
void move_snake(Snake *snake); /*Pomeram se u smeru vektora direction*/
void generate_food_position(int *x, int *z); // Daje koordinate na kojoj se pojavila nova hrana
static int generate_random_number(int a, int b); //Generise dva nasumicna broja, koja koristimo za pseudo-slucajno pojavljivanje hrane
void init_game(Snake *snake, Food *food,int *animation_ongoing); //Funkcija u kojoj inicijalizujemo sve potrebne parametre
int is_food_eaten(const Snake *snake,const Food *food); //Detekcija da li je hrana pojedena
#endif