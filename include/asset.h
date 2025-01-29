#ifndef food_h
#define food_h

#include "window.h"

//Snake
typedef struct {
    int dx, dy, len, size;
    int r, g, b, a;
    int *px, *py;
} Snake;

Snake initSnake();

//Food
typedef struct {
    int alive, x, y;
} Food;

void newFood(Food *food, Grid *grid, Snake *snake);

#endif
