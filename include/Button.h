#ifndef __BUTTON__
#define __BUTTON__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <cstdint>
#include <functional>

#include "Element.h"
#include "Font.h"
#include "Image.h"
#include "Text.h"
#include "Window.h"

class Button : public Element {
   private:
    const static uint32_t nm_padding = 2;
    const static int dw = 2;
    Text name_text;
    Image img;
    SDL_Rect rect;
    SDL_Color col;
    uint8_t clicked = 0;

   public:
    std::function<void(int, int)> click_callback;
    Button() {};
    Button(Window* win, int x, int y, int width, int height, const std::string& name, Font& font,
           const SDL_Color& color);
    void Init(Window* win, int x, int y, int width, int height, const std::string& name, Font& font,
              const SDL_Color& color);
    inline const std::string& GetName() const { return this->name_text.GetText(); };
    void Click();
    inline void SetPosition(int x, int y) {
        rect.x = x;
        rect.y = y;
    };
    inline void SetX(int x) { rect.x = x; }
    inline void SetY(int y) { rect.y = y; }
    inline uint32_t GetWidth() const { return rect.w; }
    inline uint32_t GetHeight() const { return rect.h; }
    void Draw() override;
    void Focuse() override;
    void Unfocuse() override;
    void MouseDown(const Event& event) override;
    void KeyDown(const Event& event) override;
    Element* ContainPoint(int x, int y) override;
};

#endif  // __BUTTON__
