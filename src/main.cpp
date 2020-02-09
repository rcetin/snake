#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include <string>

#include "snake/snake.h"
#include "snake/food.h"
#include "common.h"

static int snake_init(SDL_Window **w, SDL_Renderer **r)
{
    int flg = IMG_INIT_PNG;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL init failed\n");
        return -1;
    }

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
    n_texture = IMG_LoadTexture(renderer, path.c_str());
    if (n_texture == NULL) {
        printf("create texture is failed for=%s, %s\n", path.c_str(),
            IMG_GetError());
        return NULL;
    }

    return n_texture;
}

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;
    int quit = 0;
    SDL_Event e;
    int snake_x, snake_y, food_x, food_y;

    if (snake_init(&window, &renderer)) {
        printf("error snake init\n");
        return -1;
    }

    food f(renderer);
    csnake snake(renderer);

    if (f.load("/home/rcetin/workspace/programming/sdl/snake/src/banana.png")) {
        printf("load png is failed\n");
        goto bail;
    }
    
    if (snake.load("/home/rcetin/workspace/programming/sdl/snake/src/snake.png")) {
        printf("load png is failed\n");
        goto bail;
    }

    while (!quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            snake.handle_event(e);
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        
        f.appear();
        snake.move();
        snake.get_center_pos(&snake_x, &snake_y);
        f.get_center_pos(&food_x, &food_y);
        if (food_x == snake_x && food_y == snake_y) {
            printf("BOOOM!\n");
            f.random();
        }

        //Update screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

bail:
    return -1;
}