#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <stdio.h>

#include "window.h"
#include "asset.h"

void clearScreen(SDL_Renderer *renderer);
void screenLoop(Snake *snake, Screen *screen);
int controle(SDL_Event *event, Snake *snake);
void renderSquare(int px, int py, int size, int r, int g, int b, int a, SDL_Renderer *renderer);

int main() {
    //Init Game    
    Snake snake = initSnake();
    
    Grid grid;
    grid.x = 40;
    grid.y = 30;

    Screen screen;
    screen.x = grid.x * snake.size;
    screen.y = grid.y * snake.size;
    
    Food food;
    newFood(&food, &grid, &snake);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a fixed-size window (800x600)
    SDL_Window *win = SDL_CreateWindow("Fixed-Size Game Window", 
                        SDL_WINDOWPOS_CENTERED, 
                        SDL_WINDOWPOS_CENTERED, 
                        screen.x, screen.y,
                        0
                    );

    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
                                win, 
                                -1, 
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                            );
    if (!renderer) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Main loop
    SDL_Event event;
    int running = 1;    
    while (running) {
        //Controle
        running = controle(&event, &snake);

        //Food
        if(food.x == snake.px[0] && food.y == snake.py[0]){
            newFood(&food, &grid, &snake);
            snake.len ++;
            snake.px = realloc(snake.px, sizeof(int) * snake.len);
            snake.py = realloc(snake.py, sizeof(int) * snake.len);
        }

        //Snake
        for (int i = snake.len-1; i > -1; i--)
        {
            //head
            if(i == 0)
            {
                // printf("Head\n");
                screenLoop(&snake, &screen);
            } else {
                // printf("Tail\n");
                snake.px[i] = snake.px[i-1];
                snake.py[i] = snake.py[i-1];
            }
        }

        //Render
        clearScreen(renderer);

        for (int i = 0; i < snake.len; i++)
        {
            //check collision
            if(i != 0 && snake.px[0] == snake.px[i] && snake.py[0] == snake.py[i]){
                snake = initSnake();
                break;
            }

            renderSquare(snake.px[i], snake.py[i], snake.size, 255, 0, 0, 255, renderer);
        }

        renderSquare(food.x, food.y, snake.size, 0, 255, 0, 255, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(60);
    }

    // Cleanup & Close
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}


void clearScreen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
}


void screenLoop(Snake *snake, Screen *screen){
    int *p = snake->dx != 0 ? &snake->px[0] : &snake->py[0];
    int *s = snake->dx != 0 ? &screen->x : &screen->y;
    int *d = snake->dx != 0 ? &snake->dx : &snake->dy;

    // printf("%d %d %d\n", *p, *s, *d);
    if(*p > *s - snake->size){
        *p = 0;
    } else if(*p < 0) {
        *p = *s - snake->size;
    } else {
        *p = *p + *d * snake->size;
    }
}

int controle(SDL_Event *event, Snake *snake) 
{
    int running = 1;
    while (SDL_PollEvent(event)) 
    {
        if (event->type == SDL_QUIT) 
        {
            running = 0;
        } else if (event->type == SDL_KEYDOWN){
            switch (event->key.keysym.sym) {
            case SDLK_LEFT:
                if(snake->dx != 0){break;}
                snake->dx = -1;
                snake->dy = 0;
                break;
            
            case SDLK_RIGHT:
                if(snake->dx != 0){break;}
                snake->dx = 1;
                snake->dy = 0;
                break;

            case SDLK_UP:
                if(snake->dy != 0){break;}
                snake->dx = 0;
                snake->dy = -1;
                break;

            case SDLK_DOWN:
                if(snake->dy != 0){break;}
                snake->dx = 0;
                snake->dy = 1;
                break;
            case SDLK_RETURN:
                running = 0;
                break;
            }
        }
    }
    return running;
}

void renderSquare(int px, int py, int size, int r, int g, int b, int a, SDL_Renderer *renderer)
{
    SDL_Rect square = {px, py, size, size};
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &square);
    return;    
}