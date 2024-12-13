#ifndef __TEXT_FIELD__
#define __TEXT_FIELD__

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <functional>
#include <string>

#include "Element.h"
#include "Font.h"
#include "Rectangle.h"
#include "Text.h"
#include "Window.h"
class TextField : public Rectangle {
   protected:
    Font font;
    std::string text;
    std::string placeholder;
    SDL_Color color;
    SDL_Color text_color;
    uint32_t cursor_index = 0;
    uint32_t max_length = 0;
    uint32_t start = 0;
    int cursor_x = 0;
    char cursor_blink = 0;

    bool focused = false;

    static const uint8_t padding = 4;

   public:
    std::function<void(int x, int y)> mouse_down_callback;
    std::function<void(uint32_t key)> key_down_callback;
    TextField() = default;

    TextField(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color = {255, 255, 255, 255},
              const SDL_Color& text_color = {0, 0, 0, 255});

    void Init(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color = {255, 255, 255, 255},
              const SDL_Color& text_color = {0, 0, 0, 255});
    inline const std::string& GetText() const { return this->text; }
    void SetPlaceholder(const std::string& text) { this->placeholder.assign(text); }
    void Type(char);

    void Draw() override;
    // return true if this element contains point of given coordinates
    Element* ContainPoint(int x, int y) override;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    void Focuse() override;
    // unfocuses gui element
    void Unfocuse() override;
    // behavior of gui element when when specific key is pressed
    void KeyDown(const Event& event) override;
    // behavior of gui element it's clicked
    void MouseDown(const Event& event) override;
    inline ~TextField() override {};
};

#endif  //!__TEXT_FIELD__
