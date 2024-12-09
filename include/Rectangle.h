#ifndef __RECTANGLE__
#define __RECTANGLE__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "Element.h"
#include "Window.h"

class Rectangle : public Element {
   private:
    SDL_Rect rect;
    SDL_Color color;

   public:
    void Init(Window* win, int x, int y, int width, int height, const SDL_Color color);
    inline void SetX(const int x) { this->rect.x = x; }
    inline void SetY(const int y) { this->rect.y = y; }
    inline void SetPosition(const int x, const int y) {
        this->rect.x = x;
        this->rect.y = y;
    }
    inline uint32_t GetWidth() const { return rect.w; }
    inline uint32_t GetHeight() const { return rect.h; }
    inline int GetX() const { return rect.x; }
    inline int GetY() const { return rect.y; }
    void Draw() override;
    void Focuse() override;
    void Unfocuse() override;
    void MouseDown(const Event& event) override;
    void KeyDown(const Event& event) override;
    Element* ContainPoint(int x, int y) override;
};

#endif  // !__RECTANGLE__
