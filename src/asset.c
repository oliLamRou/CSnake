#include <stdlib.h>
#include <stdio.h>

#include "asset.h"

//Food
void newFood(Food *food, Grid *grid, Snake *snake){
    food->x = (rand() % grid->x) * snake->size;
    food->y = (rand() % grid->y) * snake->size;
}

//Food
Snake initSnake(){
    Snake snake;
    snake.len = 2;
    snake.size = 10;
    snake.px = malloc(snake.len * sizeof(int));
    snake.py = malloc(snake.len * sizeof(int));
    snake.dx = 1;
    snake.px[0] = 50;
    snake.py[0] = 40;
    for (int i = 1; i < snake.len; i++)
    {
        snake.px[i] = snake.px[i-1] - snake.size;
        snake.py[i] = snake.py[0];
    }

    return snake;
}
