#include "Font.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <strings.h>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Image.h"

bool Font::ttf_init = false;
int length_of_all = 0;
Font::Font(const Font& t) {
    if (!t.font_info) return;
    this->font_info = t.font_info;
    t.font_info->link_count++;
}

Font::Font(Font&& _font) noexcept {
    if (!_font.font_info) return;
    this->font_info = _font.font_info;
    _font.font_info = nullptr;
}

Font& Font::operator=(const Font& _font) {
    // if this font is last holder of datta then delete data
    this->Destroy();
    if (_font.font_info) {
        this->font_info = _font.font_info;
        this->font_info->link_count++;
    }
    return *this;
}

Font::Font(const char* font_path, size_t font_size, int style) {
    if (!ttf_init) {
        TTF_Init();
        ttf_init = true;
    }
    TTF_Font* font = TTF_OpenFont(font_path, font_size);
    if (!font) {
        printf("Cannot load font!\n");
        exit(1);
    }
    TTF_SetFontStyle(font, style);
    this->font_info = new FontData;
    this->font_info->_font = font;
    this->font_info->link_count = 1;
}

void Font::Init(const char* font_path, size_t font_size, int style) {
    this->Destroy();
    if (!ttf_init) {
        TTF_Init();
        ttf_init = true;
    }

    TTF_Font* font = TTF_OpenFont(font_path, font_size);
    if (!font) {
        printf("Cannot load font!\n");
        exit(1);
    }
    TTF_SetFontStyle(font, style);
    this->font_info = new FontData;
    this->font_info->_font = font;
    this->font_info->link_count = 1;
}

// DrawText return width of Drawn text
int Font::DrawText(SDL_Renderer* ren, int x, int y, const char* text, size_t length, const SDL_Color& color) {
    if (this->font_info->texture == nullptr) this->LoadFontTextures(ren);

    SDL_Rect rect = {x, y, 0, this->font_info->letter_height};
    SDL_Rect src_rect = {0, 0, 0, font_info->letter_height};
    SDL_SetTextureColorMod(font_info->texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(font_info->texture, color.a);
    for (size_t i = 0; i < length; i++) {
        rect.x += rect.w;
        if (text[i] == '\0') break;
        short index = text[i] - 32;
        if (index < -1) continue;
        if (index < 0 || index > 96) index = '*' - 32;
        rect.w = font_info->letter_width[index];
        src_rect.w = rect.w;
        src_rect.x = font_info->letters[index];
        SDL_RenderCopy(ren, font_info->texture, &src_rect, &rect);
    }

    return rect.x - x + rect.w;
}

Image Font::ConvertToImage(SDL_Renderer* ren, int x, int y, const std::string& text, const SDL_Color& color) {
    if (this->font_info->texture == nullptr) this->LoadFontTextures(ren);
    SDL_Color color_mod = {255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderText_Blended(this->font_info->_font, text.c_str(), color_mod);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_FreeSurface(surf);
    return Image(x, y, ren, texture);
}
void Font::LoadFontTextures(SDL_Renderer* ren) {
    if (this->font_info->texture) return;
    SDL_Color color = {255, 255, 255, 255};
    TTF_Font* font = this->font_info->_font;
    char all_letters[97] = {0};
    int offset = 0;

    for (int i = 32; i < 127; i++) {
        all_letters[i - 32] = char(i);
        int h, w = 0;
        char letter[] = {char(i), '\0'};
        TTF_SizeText(font, all_letters, &w, &h);
        font_info->letter_width[i - 32] = w - offset;
        font_info->letters[i - 32] = offset;
        offset = w;
    }
    // font_info->letters[0] = 0;
    SDL_Surface* surf = TTF_RenderText_Blended(font, all_letters, color);
    font_info->texture = SDL_CreateTextureFromSurface(ren, surf);
    font_info->letter_height = surf->h;
    SDL_SetTextureBlendMode(font_info->texture, SDL_BLENDMODE_BLEND);
    length_of_all = surf->w;
    SDL_FreeSurface(surf);
}
inline void Font::Destroy() {
    if (!this->font_info) return;
    if (this->font_info->link_count > 1) {
        this->font_info->link_count--;
        return;
    }
    // if this is last holder of data then release data
    SDL_DestroyTexture(this->font_info->texture);
    TTF_CloseFont(this->font_info->_font);
    delete this->font_info;
}
Font::~Font() {
    this->Destroy();
}
/*
 size_t RenderTextUntil(int x, int y, const char* text, char delim, size_t max_length) {
     SDL_Rect rect = {x, y, 0, letter_height};
     for (size_t i = 0; i < max_length && text[i] != delim; i++) {
         rect.w = letter_width[text[i]];
         SDL_RenderCopy(main_ren, letters[text[i]], NULL, &rect);
         rect.x += rect.w;
     }
     return rect.x - x;
 }
 */
