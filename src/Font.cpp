#include "Font.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Image.h"

bool Font::ttf_init = false;

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
    if (this->font_info) {
        FontData& data = *this->font_info;
        // if this font is last holder of datta then delete data
        if (this->font_info->link_count == 1) {
            for (int i = sizeof(this->font_info->letters) - 1; i > -1; i--) {
                SDL_DestroyTexture(data.letters[i]);
            }
            data.link_count = 0;
            delete this->font_info;
            this->font_info = nullptr;
        }
        // else decriment counter of data holders
        else {
            this->font_info->link_count--;
        }
    }
    if (_font.font_info) {
        this->font_info = _font.font_info;
        this->font_info->link_count++;
    }
    return *this;
}

Font::Font(const char* font_path, size_t font_size, const SDL_Color& font_color) {
    if (!ttf_init) {
        TTF_Init();
        ttf_init = true;
    }
    TTF_Font* font = TTF_OpenFont(font_path, font_size);
    if (!font) {
        printf("Cannot load font!\n");
        exit(1);
    }
    this->font_info = new FontData;
    this->font_info->_font = font;
    this->font_info->link_count = 1;
}

void Font::Init(const char* font_path, size_t font_size, const SDL_Color& font_color) {
    this->~Font();
    if (!ttf_init) {
        TTF_Init();
        ttf_init = true;
    }
    TTF_Font* font = TTF_OpenFont(font_path, font_size);
    if (!font) {
        printf("Cannot load font!\n");
        exit(1);
    }
    this->font_info = new FontData;
    this->font_info->_font = font;
    this->font_info->link_count = 1;
}

// DrawText return width of Drawn text
uint32_t Font::DrawText(SDL_Renderer* ren, int x, int y, const char* text, size_t length, const SDL_Color& color) {
    if (this->font_info->letters[0] == nullptr) this->LoadFontTextures(ren);

    SDL_Rect rect = {x, y, 0, this->font_info->letter_height};
    for (size_t i = 0; i < length; i++) {
        rect.x += rect.w;
        if (text[i] == '\0') break;
        short index = text[i] - 32;
        if (index < -1) continue;
        if (index < 0 || index > 96) index = '*' - 32;
        rect.w = font_info->letter_width[index];
        SDL_Texture* letter_texture = font_info->letters[index];
        SDL_SetTextureColorMod(letter_texture, color.r, color.g, color.b);
        SDL_RenderCopy(ren, letter_texture, NULL, &rect);
    }

    return rect.x - x + rect.w;
}

Image Font::ConvertToImage(SDL_Renderer* ren, const std::string& text, const SDL_Color& color) {
    if (this->font_info->letters[0] == nullptr) this->LoadFontTextures(ren);
    SDL_Surface* surf = TTF_RenderText_Blended(this->font_info->_font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(surf);
    return Image(0, 0, ren, texture);
}
void Font::LoadFontTextures(SDL_Renderer* ren) {
    if (!this->font_info) return;
    SDL_Color color = {255, 255, 255, 255};
    TTF_Font* font = this->font_info->_font;
    for (int i = 32; i < 127; i++) {
        char l[] = {char(i), '\0'};
        SDL_Surface* surf = TTF_RenderText_Blended(font, l, color);
        if (l[0] == 'A') this->font_info->letter_height = surf->h;
        SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        font_info->letters[i - 32] = texture;
        font_info->letter_width[i - 32] = surf->w;
        SDL_FreeSurface(surf);
    }

    // SDL_QueryTexture(letters['A'], NULL,NULL, &letter_width['A'],
    // &letter_height);
};
Font::~Font() {
    if (!this->font_info) return;
    if (this->font_info->link_count > 1) {
        this->font_info->link_count--;
        return;
    }
    // if this is last holder of data then release data
    for (size_t i = this->font_info->num_letters - 1; i > -1; i--) SDL_DestroyTexture(this->font_info->letters[i]);
    TTF_CloseFont(this->font_info->_font);
    delete this->font_info;
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
