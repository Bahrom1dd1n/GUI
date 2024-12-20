#ifndef __CANVAS__
#define __CANVAS__
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>

#include "Element.h"
#include "Image.h"
#include "Rectangle.h"
class Window;
class Canvas : public Rectangle {
   protected:
    std::vector<Element*> children;
    SDL_Texture* texture = nullptr;
    int border_width = 0;

   public:
    Canvas(Window* win, int x, int y, int width, int height);
    inline void SetBorderColor(const SDL_Color& color) { this->color = color; }
    inline void SetBorderWidth(int width) { this->border_width = width; }
    void Clear(const SDL_Color& color = {255, 255, 255, 255});
    void Draw() override;
    void DrawLine(int x, int y, int x2, int y2, const SDL_Color& color);
    void DrawImage(int x, int y, const Image& img);
    void FillRectangle(int x, int y, int w, int h, const SDL_Color& color);

    void DrawRectangle(int x, int y, int w, int h, int border_width, const SDL_Color& border_color);
};
#endif  //!__CANVAS__
