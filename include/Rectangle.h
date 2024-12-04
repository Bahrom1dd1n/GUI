#ifndef __RECTANGLE__
#define __RECTANGLE__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "Element.h"

class Rectangle : public Element {
   private:
    SDL_Rect rect;
    SDL_Color color;

   public:
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

#endif  // !__RECTANGLE__
