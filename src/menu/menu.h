#ifndef _MENU_H
#define _MENU_H

#include "../texture/texture.h"

class menu
{
    private:
        ntexture mtexture;
        SDL_Renderer *mr;

    public:
        menu(SDL_Renderer *renderer);
        ~menu();
        int load_image(std::string path);
        int load_text(std::string text, SDL_Color text_color);
        void set_size(int w, int h);
        int set_font(const char *font_file, int pt_size);
        int put_element(int x, int y);
};

#endif