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
    current_elem_w = w;
    current_elem_h = h;

    mtexture.set_size(w, h);
}

int menu::load_text(std::string text, SDL_Color text_color)
{
    return mtexture.load_text(text, text_color, mr);
}

int menu::put_element(int x, int y, std::string elem_name)
{
    struct menu_elem e;

    for (std::list<menu_elem>::iterator it=elem_list.begin(); it != elem_list.end(); ++it) {
        if (it->name == elem_name) {
            goto render;
        }
    }
    e.x = x;
    e.y = y;
    e.w = current_elem_w;
    e.h = current_elem_h;
    e.name = elem_name;

    elem_list.push_back(e);

render:
    return mtexture.render(mr, x, y);
}

int menu::check_button_click(std::string name)
{
    int xm, ym;
    for (std::list<menu_elem>::iterator it=elem_list.begin(); it != elem_list.end(); ++it) {
        // printf("elem-> x=%d, y=%d, w=%d, h=%d, name=%s\n", it->x, it->y, it->w, it->h, it->name.c_str());
        if (it->name != name) {
            continue;
        }

	    SDL_GetMouseState(&xm, &ym);
        if(xm < it->x) {
            return -1;
        } else if(xm > it->x + it->w) {
            return -1;
        } else if(ym < it->y) {
            return -1;
        } else if(ym > it->y + it->h) {
            return -1;
        }
        return 0;
    }
    return 0;
}