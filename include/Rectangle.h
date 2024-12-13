#ifndef __RECTANGLE__
#define __RECTANGLE__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "Element.h"
class Window;
class Rectangle : public Element {
   protected:
    SDL_Rect rect;
    SDL_Color color;

   public:
    Rectangle() = default;
    Rectangle(Window* win, int x, int y, int width, int height, const SDL_Color color);
    void Init(Window* win, int x, int y, int width, int height, const SDL_Color color);
    inline void SetX(const int x) { this->rect.x = x; }
    inline void SetY(const int y) { this->rect.y = y; }
    inline void SetCenterX(int x) { rect.x = x - (rect.w >> 1); }
    inline void SetCenterY(int y) { rect.y = y - (rect.h >> 1); }
    inline void SetWidth(int width, bool save_ratio = false) {
        if (save_ratio) {
            double ratio = double(width) / rect.w;
            this->rect.w *= ratio;
            this->rect.h *= ratio;
            return;
        }
        this->rect.w = width;
    }
    inline void SetHeight(int height, bool save_ratio = false) {
        if (save_ratio) {
            double ratio = double(height) / rect.h;
            this->rect.w *= ratio;
            this->rect.h *= ratio;
            return;
        }
        this->rect.h = height;
    }
    inline int GetX() const { return rect.x; }
    inline int GetY() const { return rect.y; }
    inline int GetCenterX() { return rect.x + (rect.w >> 1); }
    inline int GetCenterY() { return rect.y + (rect.h >> 1); }
    inline int GetWidth() const { return rect.w; }
    inline int GetHeight() const { return rect.h; }
    inline const SDL_Rect& GetBorders() const { return this->rect; }
    void Draw() override;
    void Focuse() override;
    void Unfocuse() override;
    void MouseDown(const Event& event) override;
    void KeyDown(const Event& event) override;
    Element* ContainPoint(int x, int y) override;
    inline ~Rectangle() override {};
};

#endif  // !__RECTANGLE__
