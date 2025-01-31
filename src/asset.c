#include <stdlib.h>
#include <stdio.h>

#include "asset.h"

//Food
void newFood(Food *food, Grid *grid, Snake *snake){
    int foodOnSnake = 1;
    while (foodOnSnake)
    {
        food->x = (rand() % grid->x) * snake->size;
        food->y = (rand() % grid->y) * snake->size;

        foodOnSnake = 0;
        for (int i = 0; i < snake->len; i++)
        {
            if(food->x == snake->px[i] && food->y == snake->px[i]){
                printf("Food on snake, respawn");
                foodOnSnake = 1;
            }
        }
    }
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

void moveHead(Snake *snake, Screen *screen){
    if(snake->dx != 0){
        snake->px[0] += snake->dx * snake->size;
    } else {
        snake->py[0] += snake->dy * snake->size;
    }

    //X
    if(snake->px[0] > screen->x - snake->size){
        snake->px[0] = 0;
    } else if(snake->px[0] < 0){
        snake->px[0] = screen->x - snake->size;
    }

    //Y
    if(snake->py[0] > screen->y - snake->size){
        snake->py[0] = 0;
    } else if(snake->py[0] < 0){
        snake->py[0] = screen->y - snake->size;
    }
}