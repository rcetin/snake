#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class ntexture
{
    private:
        SDL_Texture *texture;

        int img_w;
        int img_h;
    public:
        ntexture();
        ntexture(int w, int h);
        ~ntexture();

        void free(void);
        void set_size(int w, int h);
        int load_image(std::string path, SDL_Renderer *renderer);
        int render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip = NULL,
            double angle = 0, SDL_Point* center = NULL,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif