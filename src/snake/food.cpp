#include "food.h"
#include "../common.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

food::food(SDL_Renderer *r)
{
    food_w = DEFAULT_F_W;
    food_h = DEFAULT_F_H;
    random();

    fr = r;
    tfood = ntexture(food_w, food_h);
    srand(time(NULL));
}

food::~food()
{
    tfood.free();
}

int food::load(std::string path)
{
    return tfood.load_image(path, fr);
}

int food::appear()
{
    return tfood.render(fr, xpos, ypos);
}

void food::random()
{
    xpos = (rand() % ((SCREEN_WIDTH - food_w) / 10)) * 10;
    ypos = (rand() % ((SCREEN_HEIGHT - food_h) / 10)) * 10;
}

void food::get_center_pos(int *x, int *y)
{
    *x = xpos + (food_w / 2);
    *y = ypos + (food_h / 2);
}
