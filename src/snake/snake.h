#ifndef _SNAKE_H
#define _SNAKE_H

#include "../texture/texture.h"

#define S_UP    (1 << 1)
#define S_DOWN  (1 << 2)
#define S_RIGHT (1 << 3)
#define S_LEFT  (1 << 4)

enum key_e{
    UP,
    DOWN,
    RIGHT,
    LEFT,

    KEYS_ALL
};

class csnake
{
    private:
        ntexture snake;
        SDL_Renderer *sr;
        int xpos;
        int ypos;
        int xvel;
        int yvel;

        int snake_w;
        int snake_h;

        int keys;

        int move_cnt;
    public:
        csnake(SDL_Renderer *renderer);
        ~csnake();
        int move();
        int load(std::string path);
        void handle_event(SDL_Event& e);
        void get_center_pos(int *x, int *y);
        void debug_values(void);
};

#endif