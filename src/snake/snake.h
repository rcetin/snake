#ifndef _SNAKE_H
#define _SNAKE_H

#include "../texture/texture.h"

#define DEFAULT_S_W 10
#define DEFAULT_S_H 10
#define SNAKE_SPEED 20

enum {
    UP,
    DOWN,
    RIGHT,
    LEFT,

    KEYS_ALL
} keys;

class csnake
{
    private:
        ntexture snake;
        int xpos;
        int ypos;
        int xvel;
        int yvel;

        int snake_w;
        int snake_h;

        int keys[KEYS_ALL] = {0};
    public:
        csnake();
        csnake(int w, int h);
        ~csnake();
        int move(SDL_Renderer *renderer);
        int load(std::string path, SDL_Renderer *renderer);
        void handle_event(SDL_Event& e);
};

#endif