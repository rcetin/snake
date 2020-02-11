#include "snake.h"
#include "../common.h"
#include <string.h>

csnake::csnake(SDL_Renderer *renderer)
{
    xpos = 50;
    ypos = 50;
    snake_w = DEFAULT_S_W;
    snake_h = DEFAULT_S_H;
    keys = S_RIGHT;
    current_key = S_RIGHT;
    move_cnt = 0;
    snake_block_cnt = 1;
    fps_thr = FPS_THR;

    sr = renderer;
    snake = ntexture(snake_w, snake_h);
}

csnake::~csnake()
{
    snake.free();
}

int csnake::move(int force)
{
    struct spos p;

    if (++move_cnt < fps_thr && !force) {
        goto render;
    }
    move_cnt = 0;

    xpos = (keys & S_RIGHT) ? xpos + SNAKE_SPEED : xpos;
    xpos = (keys & S_LEFT) ? xpos - SNAKE_SPEED : xpos;
    ypos = (keys & S_DOWN) ? ypos + SNAKE_SPEED : ypos;
    ypos = (keys & S_UP) ? ypos - SNAKE_SPEED : ypos;

    p.xpos = xpos;
    p.ypos = ypos;
    pos.push_front(p);

    if (pos.size() > snake_block_cnt) {
        pos.pop_back();
    }

render:
    for (std::list<spos>::iterator it=pos.begin(); it != pos.end(); ++it) {
        if (snake.render(sr, it->xpos, it->ypos)) {
            return -1;
        }
    }

    return 0;
}

int csnake::load(std::string path)
{
    return snake.load_image(path, sr);
}

void csnake::handle_event(SDL_Event& e)
{
	if(e.type == SDL_KEYDOWN) {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: if(current_key != S_DOWN) keys = S_UP; break;
            case SDLK_DOWN: if(current_key != S_UP) keys = S_DOWN; break;
            case SDLK_LEFT: if(current_key != S_RIGHT) keys = S_LEFT; break;
            case SDLK_RIGHT: if(current_key != S_LEFT) keys = S_RIGHT; break;
        }
        current_key = keys;
    }
}

void csnake::get_center_pos(int *x, int *y)
{
    *x = xpos + (snake_w / 2);
    *y = ypos + (snake_h / 2);
}

void csnake::feed(void)
{
    snake_block_cnt++;
    if (!(snake_block_cnt % 5) && fps_thr > 1) {
        printf("speed increased\n");
        fps_thr--;
    }
}

void csnake::debug_values(void)
{
        // printf("PRINT keys: L=%d, R=%d, U=%d, D=%d\n", keys & S_LEFT, keys & S_RIGHT, keys & S_UP, keys & S_DOWN);
        // printf("POS x=%d, y=%d\n", xpos, ypos);

        printf("iterating pos list:\n");
        for (std::list<spos>::iterator it=pos.begin(); it != pos.end(); ++it)
            printf("LIST->xpos=%d, ypos=%d\n", it->xpos, it->ypos);

}