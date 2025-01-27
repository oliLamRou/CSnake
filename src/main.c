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

    // Main loop
    SDL_Event event;
    int running = 1;
    typedef struct {
        int dx, dy, px, py;
    } Snake;
    
    Snake snake;
    snake.dx = 1;
    snake.px = 400;
    snake.py = 300;

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

        snake.px = snake.px + snake.dx * 2;
        snake.py = snake.py + snake.dy * 2;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        SDL_Rect square1 = {snake.px, snake.py, 10, 10};
        SDL_RenderFillRect(renderer, &square1);

        SDL_RenderPresent(renderer);
        // SDL_Delay(5);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}