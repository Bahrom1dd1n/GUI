
#ifndef __FONT__
#define __FONT__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "Image.h"

class Font {
   private:
    struct FontData {
        static const short num_letters = 96;
        SDL_Texture* letters[num_letters] = {nullptr};
        TTF_Font* _font = nullptr;
        uint16_t letter_width[num_letters] = {0};
        uint16_t letter_height = 0;
        uint16_t link_count = 0;
    };
    FontData* font_info = nullptr;
    static bool ttf_init;
    uint32_t DrawText(SDL_Renderer* rend, int x, int y, const char* text, size_t length,
                      const SDL_Color& color = {0, 0, 0, 255});

    Image ConvertToImage(SDL_Renderer* ren, const std::string& text, const SDL_Color& color = {0, 0, 0, 255});
    void LoadFontTextures(SDL_Renderer* ren);

   public:
    Font() = default;
    Font(const Font& t);

    Font(Font&& _font) noexcept;

    Font& operator=(const Font& _font);
    Font(const char* font_path, size_t font_size, const SDL_Color& font_color);
    void Init(const char* font_path, size_t font_size, const SDL_Color& font_color);

    // retunr height of font
    inline uint32_t GetLetterHeight() const { return this->font_info->letter_height; };
    // retunr width of texture of given letter
    inline uint32_t GetLetterWidth(char letter) const {
        if (letter < 32 || letter > 126) return 0;
        return this->font_info->letter_width[letter - 32];
    };

    // DrawText return width of Drawn text , if win is specified it draw text to that window
    // unless it will draw it to it's parent window
    ~Font();
    friend class Button;
    friend class TextField;
    friend class Text;
};

#endif  //! __FONT__
