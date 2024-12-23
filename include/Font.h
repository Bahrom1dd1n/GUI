
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
#include "Window.h"
enum FontStyle {
    NORMAL = TTF_STYLE_NORMAL,
    BOLD = TTF_STYLE_BOLD,
    UNDERLINE = TTF_STYLE_UNDERLINE,
    ITALIC = TTF_STYLE_ITALIC,
};
class Font {
   private:
    struct FontData {
        static const short num_letters = 96;
        SDL_Texture* texture = nullptr;
        TTF_Font* _font = nullptr;
        int letters[num_letters] = {0};
        int16_t letter_width[num_letters] = {0};
        int16_t letter_height = 0;
        int16_t link_count = 0;
    };
    FontData* font_info = nullptr;
    static bool ttf_init;
    int32_t DrawText(SDL_Renderer* rend, int x, int y, const char* text, size_t length,
                     const SDL_Color& color = {0, 0, 0, 255});

    Image ConvertToImage(SDL_Renderer* ren, int x, int y, const std::string& text,
                         const SDL_Color& color = {0, 0, 0, 255});
    void LoadFontTextures(SDL_Renderer* ren);
    void Destroy();

   public:
    Font() = default;
    Font(const Font& t);

    Font(Font&& _font) noexcept;

    Font& operator=(const Font& _font);
    Font(const char* font_path, size_t font_size, int style = FontStyle::NORMAL);
    void Init(const char* font_path, size_t font_size, int style = FontStyle::NORMAL);

    // retunr height of font
    inline int32_t GetLetterHeight() const { return this->font_info->letter_height; };
    // retunr width of texture of given letter
    inline int32_t GetLetterWidth(char letter) const {
        if (letter < 32 || letter > 126) return 0;
        return this->font_info->letter_width[letter - 32];
    };
    inline SDL_Point GetTextDimensions(char* text) {
        int w = 0, h = 0;
        TTF_SizeText(font_info->_font, text, &w, &h);
        return {w, h};
    }
    // DrawText return width of Drawn text , if win is specified it draw text to that window
    // unless it will draw it to it's parent window
    ~Font();
    friend class Button;
    friend class TextField;
    friend class Text;
    friend class HiddenField;
    friend class Canvas;
};

#endif  //! __FONT__
