
#ifndef __FONT__
#define __FONT__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <cstdint>

#include "Texture.h"

class Font {
   private:
    struct FontData {
        SDL_Texture* letters[96] = {nullptr};
        uint16_t letter_width[96] = {0};
        uint16_t letter_height = 0;
        uint16_t link_count = 0;
    };
    FontData* font_info = nullptr;
    static bool ttf_init;

   public:
    Font(const Font& t);

    Font(Font&& _font) noexcept;

    Font(const char* font_path, size_t font_size, const SDL_Color& font_color);

    Font& operator=(const Font& _font);
    // retunr height of font
    inline uint32_t GetLetterHeight() const { return this->font_info->letter_height; };
    // retunr width of texture of given letter
    inline uint32_t GetLetterWidth(char letter) const {
        if (letter < 32 || letter > 126) return 0;
        return this->font_info->letter_width[letter - 32];
    };

    // DrawText return width of Drawn text
    size_t DrawText(int x, int y, const char* text, size_t length) const;
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

    Texture ConvertToTextuer(const char* text, size_t length) const;
    ~Font();
};

#endif  //! __FONT__
