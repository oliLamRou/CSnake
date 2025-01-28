#ifndef snake_h
#define snake_h

typedef struct {
    int dx, dy;
    int px [10];
    int py [10];
} Snake;

Snake initSnake;

#endif