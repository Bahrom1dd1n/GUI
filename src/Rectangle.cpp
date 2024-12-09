#include "Rectangle.h"

#include <SDL2/SDL_render.h>
void Rectangle::Init(Window* win, int x, int y, int width, int height, const SDL_Color color) {
    this->renderer = win->main_ren;
    this->rect = {x, y, width, height};
    this->color = color;
}
void Rectangle::Draw() {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->renderer, &rect);
};
void Rectangle::Focuse() {};
void Rectangle::Unfocuse() {};
void Rectangle::MouseDown(const Event& event) {};
void Rectangle::KeyDown(const Event& event) {};
Element* Rectangle::ContainPoint(int x, int y) {
    if (x < this->rect.x || x > this->rect.x + this->rect.w) return nullptr;
    if (y < this->rect.y || y > this->rect.y + this->rect.h) return nullptr;
    return this;
};
