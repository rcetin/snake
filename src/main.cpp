#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include <string>

#include "snake/snake.h"
#include "snake/food.h"
#include "menu/menu.h"
#include "common.h"

typedef void (*game_fx)(SDL_Renderer *);

game_fx game_fx_array[STATES_ALL];
game_state_e current_state = MAIN_MENU;

static struct {
    food *f;
    csnake *snake;
    menu *m;
    int score;
} game_ctx;

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
    game_ctx.f = NULL;
    game_ctx.snake = NULL;
    game_ctx.m = NULL;
}

static void game_state_change(game_state_e e)
{
    current_state = e;
}

static void game_main_menu_event_handle(SDL_Event& e)
{
    if (current_state != MAIN_MENU) {
        return;
    }

	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
        if(game_ctx.m->check_button_click("play_button")) {
            return;
        }

        game_state_change(INIT_GAME);
	}
}

static void render_snake_title(SDL_Renderer *renderer)
{
    SDL_Color menu_title = {75, 188, 222, 255};
    if (game_ctx.m->set_font("./src/fonts/Roboto-Thin.ttf", 40)) {
        printf("set_font failed, line=%d\n", __LINE__);
    }
    if (game_ctx.m->load_text("Snake", menu_title)) {
        printf("load_text failed, line=%d\n", __LINE__);
    }
    game_ctx.m->set_size(300, 70);
    if (game_ctx.m->put_element(SCREEN_WIDTH/2 - 150, 25, "title") < 0) {
        printf("put_element failed, line=%d\n", __LINE__);
    }
}

static void render_score_title(SDL_Renderer *renderer)
{
    SDL_Color menu_title = {75, 188, 222, 255};
    if (game_ctx.m->set_font("./src/fonts/Roboto-Thin.ttf", 20)) {
        printf("set_font failed, line=%d\n", __LINE__);
    }
    if (game_ctx.m->load_text("Score", menu_title)) {
        printf("load_text failed, line=%d\n", __LINE__);
    }
    game_ctx.m->set_size(80, 30);
    if (game_ctx.m->put_element(SCREEN_WIDTH - 100, 25, "score") < 0) {
        printf("put_element failed, line=%d\n", __LINE__);
    }
}

static void game_main_menu(SDL_Renderer *renderer)
{
    render_snake_title(renderer);
    if (game_ctx.m->set_font("./src/fonts/Pacifico.ttf", 20)) {
        printf("set_font failed, line=%d\n", __LINE__);
    }
    SDL_Color play_game = {169, 191, 21, 255};
    if (game_ctx.m->load_text("Start game", play_game)) {
        printf("load_text failed, line=%d\n", __LINE__);
    }
    game_ctx.m->set_size(150, 70);
    if (game_ctx.m->put_element(SCREEN_WIDTH/2 - 75, 250 - 35, "play_button") < 0) {
        printf("put_element failed, line=%d\n", __LINE__);
    }
    // game_state_change(INIT_GAME);
}

static void game_init(SDL_Renderer *renderer)
{
    // TODO: fx pointers should return integer not void!
    game_ctx.score = 0;

    if (game_ctx.f->load("./src/images/banana.png")) {
        printf("load png is failed\n");
        goto bail;
    }
    
    if (game_ctx.snake->load("./src/images/snake.png")) {
        printf("load png is failed\n");
        goto bail;
    }

    game_state_change(PLAY);
    return;

bail:
    game_free();
}

static void update_score(SDL_Renderer *renderer)
{
    SDL_Color menu_title = {75, 188, 222, 255};
    if (game_ctx.m->set_font("./src/fonts/Roboto-Thin.ttf", 15)) {
        printf("set_font failed, line=%d\n", __LINE__);
    }
    if (game_ctx.m->load_text(std::to_string(game_ctx.score), menu_title)) {
        printf("load_text failed, line=%d\n", __LINE__);
    }
    game_ctx.m->set_size(40, 30);
    if (game_ctx.m->put_element(SCREEN_WIDTH - 75, 60, "score_int") < 0) {
        printf("put_element failed, line=%d\n", __LINE__);
    }

}

static void game_play(SDL_Renderer *renderer)
{
    int snake_x, snake_y, food_x, food_y;

    game_ctx.f->appear();
    game_ctx.snake->move(0);
    game_ctx.snake->get_center_pos(&snake_x, &snake_y);
    game_ctx.f->get_center_pos(&food_x, &food_y);
    if (food_x == snake_x && food_y == snake_y) {
        game_ctx.snake->feed();
        game_ctx.f->random();
        game_ctx.score += 10;
    }

    if (snake_x >= GAME_BORDEX_XMAX ||
        snake_y >= GAME_BORDEX_YMAX ||
        snake_x <= GAME_BORDEX_MXMAX ||
        snake_y <= GAME_BORDEX_MYMAX) {
            printf("snake_x = %d, snake_y=%d\n", snake_x, snake_y);
            current_state = OVER;
    }
}

static void game_over(SDL_Renderer *renderer)
{
    SDL_Color game_over = {169, 191, 21, 255};
    if (game_ctx.m->load_text("GAME OVER", game_over)) {
        printf("load_text failed, line=%d\n", __LINE__);
    }
    game_ctx.m->set_size(400, 200);
    if (game_ctx.m->put_element(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 100, "game_over")) {
        printf("put_element failed, line=%d\n", __LINE__);
    }
}

static void init_game_states(game_fx *g)
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
    SDL_Rect outer_rect = {10,
            10,
            SCREEN_WIDTH - 20,
            SCREEN_HEIGHT - 20};
    SDL_Rect game_rect = {10,   // -xmax
            100,    // -ymax
            SCREEN_WIDTH - 20,  // 600 xmax
            SCREEN_HEIGHT - 110};   // 360 ymax


    if (snake_init(&window, &renderer)) {
        printf("error snake init\n");
        return -1;
    }

    csnake snake(renderer);
    food f(renderer);
    menu m(renderer);

    game_ctx.m = &m;
    game_ctx.f = &f;
    game_ctx.snake = &snake;

    init_game_states(game_fx_array);
    while (!quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            game_ctx.snake->handle_event(e);
            if (current_state == PLAY && e.type == SDL_KEYDOWN) {
                game_ctx.snake->move(1);
            }

            game_main_menu_event_handle(e);
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        
        render_snake_title(renderer);
        render_score_title(renderer);
        update_score(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); 
        SDL_RenderDrawRect(renderer, &outer_rect);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); 
        SDL_RenderDrawRect(renderer, &game_rect);

        game_fx_array[current_state](renderer);

        //Update screen
        SDL_RenderPresent(renderer);
    }

    game_free();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}