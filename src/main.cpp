#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

static int snake_init(SDL_Window **w, SDL_Renderer **r)
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL init failed\n");
        return -1;
    }
    printf("SDL init success\n");

    *w = SDL_CreateWindow("Snake",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (*w == NULL) {
        printf("create window failed, %s\n", SDL_GetError());
        goto bail;
    }

    *r = SDL_CreateRenderer(*w,
        -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    if (*r == NULL) {
        printf("create renderer failed, %s\n", SDL_GetError());
        goto bail;
    }

    return 0;
bail:
    SDL_DestroyWindow(*w);
    SDL_DestroyRenderer(*r);
    return -1;

}

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;

    if (snake_init(&window, &renderer)) {
        printf("error snake init\n");
        goto bail;
    }

    SDL_SetRenderDrawColor(renderer,
        255, 153, 51, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

bail:
    return -1;
}