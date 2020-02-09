#ifndef _MENU_H
#define _MENU_H

#include "../texture/texture.h"

#include <list>

struct menu_elem {
    int x;
    int y;
    int w;
    int h;
    std::string name;
};

class menu
{
    private:
        ntexture mtexture;
        SDL_Renderer *mr;
        std::list<struct menu_elem> elem_list;

        int current_elem_w;
        int current_elem_h;

    public:
        menu(SDL_Renderer *renderer);
        ~menu();
        int load_image(std::string path);
        int load_text(std::string text, SDL_Color text_color);
        void set_size(int w, int h);
        int set_font(const char *font_file, int pt_size);
        int put_element(int x, int y, std::string elem_name);
        int check_button_click(std::string name);
};

#endif