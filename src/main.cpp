#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include <string>

#include "snake/snake.h"
#include "snake/food.h"
#include "menu/menu.h"
#include "common.h"

game_fx game_fx_array[STATES_ALL];
game_state_e current_state = MAIN_MENU;

static struct {
    food *f;
    csnake *snake;
}game_ctx;

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

    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialized, SDL_ttf Error: %s\n", TTF_GetError() );
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

static void game_free(void)
{
    delete game_ctx.f;
    delete game_ctx.snake;
    game_ctx.f = NULL;
    game_ctx.snake = NULL;
}

void game_state_change(game_state_e e)
{
    current_state = e;
}

void game_main_menu(SDL_Renderer *renderer)
{
    game_state_change(INIT_GAME);
}

void game_init(SDL_Renderer *renderer)
{
    // TODO: fx pointers should return integer not void!
    game_ctx.f = new food(renderer);
    game_ctx.snake = new csnake(renderer);

    if (game_ctx.f->load("/home/rcetin/workspace/programming/sdl/snake/src/banana.png")) {
        printf("load png is failed\n");
        goto bail;
    }
    
    if (game_ctx.snake->load("/home/rcetin/workspace/programming/sdl/snake/src/snake.png")) {
        printf("load png is failed\n");
        goto bail;
    }

    game_state_change(PLAY);
    return;

bail:
    game_free();
}

void game_play(SDL_Renderer *renderer)
{
    int snake_x, snake_y, food_x, food_y;

    game_ctx.f->appear();
    game_ctx.snake->move();
    game_ctx.snake->get_center_pos(&snake_x, &snake_y);
    game_ctx.f->get_center_pos(&food_x, &food_y);
    if (food_x == snake_x && food_y == snake_y) {
        printf("BOOOM!\n");
        game_ctx.snake->feed();
        game_ctx.f->random();
    }
}

void game_over(SDL_Renderer *renderer)
{
    delete game_ctx.f;
    delete game_ctx.snake;
}

void init_game_states(game_fx *g)
{
    g[MAIN_MENU] = game_main_menu;
    g[INIT_GAME] = game_init;
    g[PLAY] = game_play;
    g[OVER] = game_over;
}

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;
    int quit = 0;
    SDL_Event e;

    if (snake_init(&window, &renderer)) {
        printf("error snake init\n");
        return -1;
    }

    // menu m(renderer);
    // // food f(renderer);
    // // csnake snake(renderer);

    // SDL_Color menu_title = {75, 188, 222, 255};
    // m.set_font("/home/rcetin/workspace/programming/sdl/snake/src/fonts/Pacifico.ttf", 40);
    // m.load_text("Snake", menu_title);
    //     SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    //     SDL_RenderClear(renderer);

    // m.put_element(100, 100);

    //     SDL_RenderPresent(renderer);
    // SDL_Delay(3000);

    init_game_states(game_fx_array);
    while (!quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            game_ctx.snake->handle_event(e);
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        
        game_fx_array[current_state](renderer);

        //Update screen
        SDL_RenderPresent(renderer);
    }

    game_free();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

bail:
    return -1;
}