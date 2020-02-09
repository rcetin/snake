#ifndef _FOOD_H
#define _FOOD_H

#include "../texture/texture.h"

class food
{
private:
    ntexture tfood;
    SDL_Renderer *fr;

    int xpos;
    int ypos;
    int food_w;
    int food_h;
public:
    food(SDL_Renderer *r);
    ~food();
    int load(std::string path);
    int appear();
    void random();
    void get_center_pos(int *x, int *y);
};

#endif