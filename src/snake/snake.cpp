#include "snake.h"
#include "../common.h"

csnake::csnake()
{
    snake = ntexture();
    xpos = 0;
    ypos = 0;
    snake_w = DEFAULT_S_W;
    snake_h = DEFAULT_S_H;
}

csnake::csnake(int w, int h)
{
    snake = ntexture(w, h);
    xpos = 0;
    ypos = 0;
    snake_w = w;
    snake_h = h;
}

csnake::~csnake()
{
    snake.free();
}

int csnake::move(SDL_Renderer *renderer)
{
    return snake.render(renderer, xpos, ypos);
}

int csnake::load(std::string path, SDL_Renderer *renderer)
{
    return snake.load_image(path, renderer);
}

void csnake::handle_event( SDL_Event& e )
{
	if(e.type == SDL_KEYDOWN) {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: keys[UP] = 1; break;
            case SDLK_DOWN: keys[DOWN] = 1; break;
            case SDLK_LEFT: keys[LEFT] = 1; break;
            case SDLK_RIGHT: keys[RIGHT] = 1; break;
        }
        xpos = (keys[RIGHT]) ? xpos + SNAKE_SPEED : xpos;
        xpos = (keys[LEFT]) ? xpos - SNAKE_SPEED : xpos;
        ypos = (keys[DOWN]) ? ypos + SNAKE_SPEED : ypos;
        ypos = (keys[UP]) ? ypos - SNAKE_SPEED : ypos;
    }

	if(e.type == SDL_KEYUP) {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: keys[UP] = 0; break;
            case SDLK_DOWN: keys[DOWN] = 0; break;
            case SDLK_LEFT: keys[LEFT] = 0; break;
            case SDLK_RIGHT: keys[RIGHT] = 0; break;
        }
    }

    printf("handle event-> x=%d, y=%d\n", xpos, ypos);
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
    // //If a key was released
    // else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    // {
    //     //Adjust the velocity
    //     switch( e.key.keysym.sym )
    //     {
    //         case SDLK_UP: ypos += SNAKE_SPEED; break;
    //         case SDLK_DOWN: ypos -= SNAKE_SPEED; break;
    //         case SDLK_LEFT: xpos += SNAKE_SPEED; break;
    //         case SDLK_RIGHT: xpos -= SNAKE_SPEED; break;
    //     }
    // }
}
