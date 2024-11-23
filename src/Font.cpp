#include "Font.h"
bool Font::ttf_init = false;
inline Font::Font(const Font& t) {
    if (!t.font_info) return;
    this->font_info = t.font_info;
    t.font_info->link_count++;
}

inline Font::Font(Font&& _font) noexcept {
    if (!_font.font_info) return;
    this->font_info = _font.font_info;
    _font.font_info = nullptr;
}
inline Font::Font(const char* font_path, size_t font_size, const SDL_Color& font_color) {
    this->font_info = new FontData;
    if (!ttf_init) {
        TTF_Init();
        ttf_init = true;
    }

    TTF_Font* font = TTF_OpenFont(font_path, font_size);
    SDL_Color color = {0, 0, 0, 255};
    for (int i = 32; i < 127; i++) {
        char l[] = {char(i), '\0'};

        SDL_Surface* surf = TTF_RenderText_Blended(font, l, color);

        if (l[0] == 'A') this->font_info->letter_height = surf->h;

        SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 255, 255));
        font_info->letters[i - 32] = SDL_CreateTextureFromSurface(main_ren, surf);

        font_info->letter_width[i - 32] = surf->w;
        SDL_FreeSurface(surf);
    }

    // SDL_QueryTexture(letters['A'], NULL,NULL, &letter_width['A'],
    // &letter_height);
    TTF_CloseFont(font);
}

inline Font& Font::operator=(const Font& _font) {
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
inline uint32_t Font::GetLetterHeight() const {
    return this->font_info->letter_height;
}

inline uint32_t Font::GetLetterWidth(char letter) const {
    if (letter < 32) return 0;
    return this->font_info->letter_width[letter - 32];
}

// DrawText return width of Drawn text
size_t Font::DrawText(int x, int y, const char* text, size_t length) const {
    SDL_Rect rect = {x, y, 0, this->font_info->letter_height};
    for (size_t i = 0; i < length; i++) {
        rect.x += rect.w;
        if (text[i] == '\0') break;
        short index = text[i] - 32;
        if (index < -1) continue;
        if (index < 0 || index > 96) index = '*' - 32;

        rect.w = font_info->letter_width[index];
        SDL_RenderCopy(main_ren, font_info->letters[index], NULL, &rect);
    }

    return rect.x - x + rect.w;
}

Texture Font::ConvertToTextuer(const char* text, size_t length) const {
    SDL_Texture* texture = nullptr;
    SDL_SetRenderTarget(main_ren, texture);
    SDL_SetRenderDrawColor(main_ren, 0, 0, 0, 0);
    SDL_RenderClear(main_ren);

    this->DrawText(0, 0, text, length);

    SDL_SetRenderTarget(main_ren, NULL);
    return Texture(texture);
}

Font::~Font() {
    if (!this->font_info) return;
    if (this->font_info->link_count > 1) {
        this->font_info->link_count--;
    }
    // if this is last holder of data then release data
    for (size_t i = sizeof(this->font_info->letters) - 1; i > -1; i--) SDL_DestroyTexture(this->font_info->letters[i]);
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
