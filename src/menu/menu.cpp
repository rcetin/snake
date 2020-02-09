#include "menu.h"

menu::menu(SDL_Renderer *renderer)
{
    mr = renderer;
    mtexture = ntexture();
}

menu::~menu()
{
    mtexture.free();
}

int menu::load_image(std::string path)
{
    return mtexture.load_image(path, mr);
}

int menu::set_font(const char *font_file, int pt_size)
{
    return mtexture.set_font(font_file, pt_size);
}

void menu::set_size(int w, int h)
{
    mtexture.set_size(w, h);
}

int menu::load_text(std::string text, SDL_Color text_color)
{
    return mtexture.load_text(text, text_color, mr);
}

int menu::put_element(int x, int y)
{
    return mtexture.render(mr, x, y);
}