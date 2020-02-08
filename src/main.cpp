#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

static int snake_init(SDL_Window **w, SDL_Renderer **r)
{
    int flg = IMG_INIT_PNG;

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

    if (!IMG_Init(flg)) {
        printf("init PNG image failed, %s\n", IMG_GetError());
        goto bail;
    }

    return 0;
bail:
    SDL_DestroyWindow(*w);
    SDL_DestroyRenderer(*r);
    return -1;

}

static SDL_Texture *load_png(std::string path, SDL_Renderer *renderer)
{
	SDL_Texture *n_texture = NULL;

	SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL) {
        printf("image load is failed for=%s, %s\n", path.c_str(),
            IMG_GetError());
        return NULL;
    }

    n_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (n_texture == NULL) {
        printf("create texture is failed for=%s, %s\n", path.c_str(),
            IMG_GetError());
        return NULL;
    }

    SDL_FreeSurface(loaded_surface);
    return n_texture;
}

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture *tx = NULL;
    SDL_Rect *rect;
    if (snake_init(&window, &renderer)) {
        printf("error snake init\n");
        goto bail;
    }

    tx = load_png("/home/rcetin/workspace/programming/sdl/snake/src/foo.png", renderer);
    if (tx == NULL) {
        printf("load png is failed\n");
        goto bail;
    }

    *rect = {10, 10, 100, 100};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tx, NULL, rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

bail:
    return -1;
}