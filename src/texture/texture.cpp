#include "texture.h"

ntexture::ntexture()
{
    texture = NULL;
    img_w = 0;
    img_h = 0;
}

ntexture::ntexture(int w, int h)
{
    texture = NULL;
    img_w = w;
    img_h = h;
}

ntexture::~ntexture()
{
    free();
}

void ntexture::free(void)
{
    if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
    img_h = 0;
    img_w = 0;
}

void ntexture::set_size(int w, int h)
{
    img_w = w;
    img_h = h;
}

int ntexture::load_image(std::string path, SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == NULL) {
        printf("create texture is failed for=%s, %s\n", path.c_str(),
            IMG_GetError());
        return -1;
    }

    return 0;
}

int ntexture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip,
    double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect rect = {x, y, img_w, img_h};

	if( clip != NULL )
	{
		rect.w = clip->w;
		rect.h = clip->h;
	}

    if (SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip)) {
        printf("render texture is failed, %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}