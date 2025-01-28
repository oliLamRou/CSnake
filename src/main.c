#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <stdio.h>

#include "snake.h"
#include "food.h"

void clearScreen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    int screenX = 40;
    int screenY = 30;
    // Create a fixed-size window (800x600)
    SDL_Window *win = SDL_CreateWindow("Fixed-Size Game Window", 
                        SDL_WINDOWPOS_CENTERED, 
                        SDL_WINDOWPOS_CENTERED, 
                        screenX * 10, screenY * 10, 
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


    int size = 10;
    int n = 2;

    Food food;
    food.alive = 0;
    food.x = -1;
    food.y = -1;


    Snake snake;
    snake.px = malloc(n * sizeof(int));
    snake.py = malloc(n * sizeof(int));
    snake.dx = 1;
    snake.px[0] = 10;
    snake.py[0] = 10;
    for (int i = 1; i < n; i++)
    {
        snake.px[i] = snake.px[i-1] - size;
        snake.py[i] = snake.py[0];
    }

    // Main loop
    SDL_Event event;
    int running = 1;    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    snake.dx = -1;
                    snake.dy = 0;
                    break;
                
                case SDLK_RIGHT:
                    snake.dx = 1;
                    snake.dy = 0;
                    break;

                case SDLK_UP:
                    snake.dx = 0;
                    snake.dy = -1;
                    break;

                case SDLK_DOWN:
                    snake.dx = 0;
                    snake.dy = 1;
                    break;
                }
            }
        }

        for (int i = n-1; i > -1; i--)
        {
            if(i == 0)
            {
                snake.px[0] = snake.px[0] > screenX * 10 ? snake.px[0] = 0 : snake.px[0] < 0 ? snake.px[0] = screenX * 10 : snake.px[0] + snake.dx * size;
                snake.py[0] = snake.py[0] > screenY * 10 ? snake.py[0] = 0 : snake.py[0] < 0 ? snake.py[0] = screenY * 10 : snake.py[0] + snake.dy * size;
            } else {
                snake.px[i] = snake.px[i-1];
                snake.py[i] = snake.py[i-1];
            }
        }

        clearScreen(renderer);

        for (int i = 0; i < n; i++)
        {
            SDL_Rect square2 = {snake.px[i], snake.py[i], size, size};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &square2);
        }
        
        //Food
        if(food.alive == 0 || (food.x == snake.px[0] && food.y == snake.py[0])){
            food.x = (rand() % screenX) * 10;
            food.y = (rand() % screenY) * 10;
            food.alive = 1;
        }

        // printf("fx:%d sx:%d fy:%d sy:%d\n", food.x, snake.px[0], food.y, snake.py[0]);
        SDL_Rect sq= {food.x, food.y, size, size};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &sq);

        SDL_RenderPresent(renderer);
        SDL_Delay(60);

    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}