#include "texture.h"

ntexture::ntexture()
{
    texture = NULL;
    img_w = 0;
    img_h = 0;
    font = NULL;
}

ntexture::ntexture(int w, int h)
{
    texture = NULL;
    img_w = w;
    img_h = h;
    font = NULL;
}

ntexture::~ntexture()
{
    free();
}

void ntexture::free(void)
{
    if(texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
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

int ntexture::set_font(const char *font_file, int pt_size)
{
    free();
    font = TTF_OpenFont(font_file, pt_size);
    if (font == NULL) {
        printf("open font failed for=%s, %s\n", font_file, TTF_GetError());
        return -1;
    }
    return 0;
}

int ntexture::load_text(std::string text, SDL_Color text_color,
    SDL_Renderer *renderer)
{
    SDL_Surface *s = NULL;

    s = TTF_RenderText_Solid(font, text.c_str(), text_color);
    if (s == NULL) {
        printf("render text failed, %s\n", TTF_GetError());
        goto bail;
    }

    texture = SDL_CreateTextureFromSurface(renderer, s);
    if (texture == NULL) {
        printf("SDL_CreateTextureFromSurface failed, %s\n", SDL_GetError());
        goto bail;
    }

    img_w = s->w;
    img_h = s->h;
    SDL_FreeSurface(s);
    return 0;

bail:
    free();
    return -1;
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