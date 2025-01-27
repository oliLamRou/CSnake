#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <stdio.h>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    int screenX = 800;
    int screenY = 600;
    // Create a fixed-size window (800x600)
    SDL_Window *win = SDL_CreateWindow("Fixed-Size Game Window", 
                        SDL_WINDOWPOS_CENTERED, 
                        SDL_WINDOWPOS_CENTERED, 
                        screenX, screenY, 
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
    int n = 10;
    typedef struct {
        //direction
        int dx, dy;

        //tail
        int px [10];
        int py [10];
    } Snake;
    
    Snake snake;
    snake.dx = 1;
    snake.px[0] = 400;
    snake.py[0] = 300;
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

        for (int i = 0; i < n; i++)
        {
            int _i = 9 - i;
            if(_i == 0){
                snake.px[0] = snake.px[0] > screenX ? snake.px[0] = 0 : snake.px[0] < 0 ? snake.px[0] = screenX : snake.px[0] + snake.dx * size;
                snake.py[0] = snake.py[0] > screenY ? snake.py[0] = 0 : snake.py[0] < 0 ? snake.py[0] = screenY : snake.py[0] + snake.dy * size;
                // snake.px[0] = snake.px[0] + snake.dx * size;
                // snake.py[0] = snake.py[0] + snake.dy * size;
                continue;
            }
            snake.px[_i] = snake.px[_i-1];
            snake.py[_i] = snake.py[_i-1];
            
        }

        // printf("->");
        // for (int i = 0; i < n; i++)
        // {
        //     printf("x: %d y: %d", snake.px[i], snake.py[i]);
        // }        
        // printf("\n");

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < n; i++)
        {
            SDL_Rect square2 = {snake.px[i], snake.py[i], size, size};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &square2);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}