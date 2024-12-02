#ifndef __TEXT_FIELD__
#define __TEXT_FIELD__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>

#include "Element.h"
#include "Font.h"
#include "Window.h"

class TextField : public Element {
   private:
    Font font;
    std::string text;
    SDL_Rect rect;
    SDL_Color bg_color;
    uint32_t cursor_index = 0;
    uint32_t cursor_x = 0;
    uint32_t max_length = 0;
    uint32_t start = 0;
    char cursor_blink = 0;

    bool focused = false;

    static const uint8_t padding = 4;

   public:
    TextField() = default;

    TextField(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color = {255, 255, 255, 255});

    void Init(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color = {255, 255, 255, 255});
    inline const std::string& GetText() const { return this->text; }
    void Draw() override;

    // return true if this element contains point of given coordinates
    bool ContainPoint(int x, int y) override;
    // behavior of gui elemnt when it's been pressed
    void Click() override;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    void Focuse() override;
    // unfocuses gui element
    void Unfocuse() override;
    // behavior of gui element when when specific key is pressed
    void KeyPress(uint32_t key) override;
    // behavior of gui element when when typed
    void Type(char) override;
    // behavior of gui element when mouse enters area of gui element
};

#endif  //!__TEXT_FIELD__
