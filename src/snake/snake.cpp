#include "snake.h"
#include "../common.h"
#include <string.h>

csnake::csnake(SDL_Renderer *renderer)
{
    xpos = 0;
    ypos = 0;
    snake_w = DEFAULT_S_W;
    snake_h = DEFAULT_S_H;
    keys = S_RIGHT;
    move_cnt = 0;

    sr = renderer;
    snake = ntexture(snake_w, snake_h);
}

csnake::~csnake()
{
    snake.free();
}

int csnake::move()
{
    debug_values();
    if (++move_cnt < FPS_THR) {
        goto render;
    }
    move_cnt = 0;

    xpos = (keys & S_RIGHT) ? xpos + SNAKE_SPEED : xpos;
    xpos = (keys & S_LEFT) ? xpos - SNAKE_SPEED : xpos;
    ypos = (keys & S_DOWN) ? ypos + SNAKE_SPEED : ypos;
    ypos = (keys & S_UP) ? ypos - SNAKE_SPEED : ypos;

    if (xpos + snake_w >= SCREEN_WIDTH) {
        xpos = SCREEN_WIDTH - snake_w;
    }

    if (xpos < 0) {
        xpos = 0;
    }

    if (ypos + snake_h >= SCREEN_HEIGHT) {
        ypos = SCREEN_HEIGHT - snake_h;
    }

    if (ypos < 0) {
        ypos = 0;
    }

render:
    return snake.render(sr, xpos, ypos);
}

int csnake::load(std::string path)
{
    return snake.load_image(path, sr);
}

void csnake::handle_event( SDL_Event& e )
{
	if(e.type == SDL_KEYDOWN) {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: keys = S_UP; break;
            case SDLK_DOWN: keys = S_DOWN; break;
            case SDLK_LEFT: keys = S_LEFT; break;
            case SDLK_RIGHT: keys = S_RIGHT; break;
        }
    }
}

void csnake::get_center_pos(int *x, int *y)
{
    *x = xpos + (snake_w / 2);
    *y = ypos + (snake_h / 2);
}

void csnake::debug_values(void)
{
        printf("PRINT keys: L=%d, R=%d, U=%d, D=%d\n", keys & S_LEFT, keys & S_RIGHT, keys & S_UP, keys & S_DOWN);
        printf("POS x=%d, y=%d\n", xpos, ypos);
}