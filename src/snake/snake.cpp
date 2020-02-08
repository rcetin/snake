#include "snake.h"
#include "../common.h"
#include <string.h>

csnake::csnake()
{
    snake = ntexture();
    xpos = 0;
    ypos = 0;
    snake_w = DEFAULT_S_W;
    snake_h = DEFAULT_S_H;
    keys[LEFT] = 0;
    keys[RIGHT] = 1;
    keys[UP] = 0;
    keys[DOWN] = 0;
    move_cnt = 0;
}

csnake::csnake(int w, int h)
{
    snake = ntexture(w, h);
    xpos = 0;
    ypos = 0;
    snake_w = w;
    snake_h = h;
    keys[LEFT] = 0;
    keys[RIGHT] = 1;
    keys[UP] = 0;
    keys[DOWN] = 0;
    move_cnt = 0;
}

csnake::~csnake()
{
    snake.free();
}

int csnake::move(SDL_Renderer *renderer)
{
    if (++move_cnt < FPS_THR) {
        goto render;
    }
    move_cnt = 0;

    xpos = (keys[RIGHT]) ? xpos + SNAKE_SPEED : xpos;
    xpos = (keys[LEFT]) ? xpos - SNAKE_SPEED : xpos;
    ypos = (keys[DOWN]) ? ypos + SNAKE_SPEED : ypos;
    ypos = (keys[UP]) ? ypos - SNAKE_SPEED : ypos;

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
    return snake.render(renderer, xpos, ypos);
}

int csnake::load(std::string path, SDL_Renderer *renderer)
{
    return snake.load_image(path, renderer);
}

void csnake::handle_event( SDL_Event& e )
{
    // TODO: keys should be set using flags not one by one.
	if(e.type == SDL_KEYDOWN) {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                keys[UP] = 1;
                keys[DOWN] = 0;
                keys[RIGHT] = 0;
                keys[LEFT] = 0;
                break;
            case SDLK_DOWN:
                keys[DOWN] = 1;
                keys[UP] = 0;
                keys[RIGHT] = 0;
                keys[LEFT] = 0;
                break;
            case SDLK_LEFT:
                keys[LEFT] = 1;
                keys[RIGHT] = 0;
                keys[UP] = 0;
                keys[DOWN] = 0;
                break;
            case SDLK_RIGHT:
                keys[RIGHT] = 1;
                keys[LEFT] = 0;
                keys[UP] = 0;
                keys[DOWN] = 0;
                break;
        }
    }
}

void csnake::debug_values(void)
{
        printf("PRINT keys: L=%d, R=%d, U=%d, D=%d\n", keys[LEFT], keys[RIGHT], keys[UP], keys[DOWN]);
        printf("POS x=%d, y=%d\n", xpos, ypos);
}