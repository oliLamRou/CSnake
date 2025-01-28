#ifndef snake_h
#define snake_h

typedef struct {
    //direction
    int dx, dy;

    //tail
    int px [10];
    int py [10];
} Snake;

Snake initSnake;

#endif