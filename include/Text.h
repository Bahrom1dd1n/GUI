
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

#include "Element.h"
#include "Font.h"
#include "Image.h"
#include "Window.h"

class Text : public Image {
   private:
    std::string text;
    Font font;

   public:
    Text() = default;
    Text(Window* win, int x, int y, const std::string& text, Font& font, const SDL_Color& color = {0, 0, 0, 255});
    void Init(Window* win, int x, int y, const std::string& text, Font& font, const SDL_Color& color = {0, 0, 0, 255});

    inline const std::string& GetText() const { return this->text; };
    // overiding virtual functions of Element class
    ~Text();
};

#endif  // !__TEXT__
