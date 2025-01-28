#ifndef snake_h
#define snake_h

typedef struct {
    int dx, dy;
    int *px, *py;
} Snake;

Snake initSnake;

#endif