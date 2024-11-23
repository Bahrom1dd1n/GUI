#ifndef __BUTTON__
#define __BUTTON__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <cstdint>
#include <iostream>

#include "Element.h"
#include "Font.h"
#include "Text.h"
#include "Window.h"

class Button : public Element {
   private:
    const static uint32_t nm_padding = 2;
    Text name_text;
    SDL_Rect rect;
    SDL_Color col;
    SDL_Renderer* ren;

   public:
    Button(Window* win, int x, int y, int width, int height, const std::string& name, const Font& font,
           const SDL_Color& color)
        : name_text(win, x, y, name, font) {
        if (name_text.GetHeight() + nm_padding >= height) this->rect.h = name_text.GetHeight() + this->nm_padding * 2;
        if (name_text.GetWidth() + nm_padding >= width) this->rect.w = name_text.GetWidth() + nm_padding * 2;
        this->rect.x = x;
        this->rect.y = y;
        this->name_text.SetX(x + (this->rect.x - this->name_text.GetWidth()) >> 1);
        this->name_text.SetY(y + (this->rect.y - this->name_text.GetHeight()) >> 1);
        this->col = color;
        this->ren = win->main_ren;
    };
    void SetPosition(int x, int y) {
        this->rect.x = x;
        this->rect.y = y;
        this->name_text.SetX(x + (this->rect.x - this->name_text.GetWidth()) >> 1);
        this->name_text.SetY(y + (this->rect.y - this->name_text.GetHeight()) >> 1);
    }
    void Draw() override {
        SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);
        SDL_RenderFillRect(ren, &rect);
    };
    void Click() override;
    void Focuse() override;
    void Unfocuse() override;
    void Hover() override;
    void UnHover() override;
    void KeyPress(uint32_t key) override;
    void Type(char) override;
    inline bool ContainPoint(int x, int y) override;
    inline const std::string& GetName() { return this->name_text.GetText(); }
};

#endif  // __BUTTON__
