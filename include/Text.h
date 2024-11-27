
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
#include "Texture.h"
#include "Window.h"

class Text : public Element {
   private:
    SDL_FRect rect;
    std::string text;
    Texture text_texture;
    Font font;

   public:
    Text() = default;
    Text(Window* win, int x, int y, const std::string& text, const Font& font, const SDL_Color& color = {0, 0, 0, 255});
    void Init(Window* win, int x, int y, const std::string& text, const Font& font,
              const SDL_Color& color = {0, 0, 0, 255});

    void SetX(int x);
    void SetY(int y);
    void SetPosition(int x, int y);
    inline uint32_t GetWidth() const { return this->rect.w; };
    inline uint32_t GetHeight() const { return this->rect.h; };
    inline const std::string& GetText() const { return this->text; };
    // overiding virtual functions of Element class
    void Draw() override;
    void Click() override;
    void Focuse() override;
    void Unfocuse() override;
    void Hover() override;
    void UnHover() override;
    void KeyPress(uint32_t key) override;
    void Type(char) override;
    bool ContainPoint(int x, int y) override;
    ~Text();
};

#endif  // !__TEXT__
