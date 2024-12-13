
/*
 header file of Text graphical object
*/

#ifndef __TEXT__
#define __TEXT__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>

#include "Element.h"
#include "Font.h"
#include "Image.h"
#include "Window.h"

class Text : public Image {
   private:
    Font font;
    std::string text;

   public:
    Text() = default;
    Text(Window* win, int x, int y, const std::string& text, Font& font);
    void Init(Window* win, int x, int y, const std::string& text, Font& font);
    void SetText(const ::std::string& text);
    void inline SetBackGroundColor(const SDL_Color& color) { this->color = color; }
    void inline SetTextColor(const SDL_Color& text_color) {
        SDL_SetTextureColorMod(img_info->texture, color.r, color.g, color.b);
    }
    inline const std::string& GetText() const { return this->text; };
    // overiding virtual functions of Element class
    //~Text() {};
};

#endif  // !__TEXT__
