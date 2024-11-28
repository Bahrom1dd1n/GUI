#include "Button.h"
void Button::Click() {};
void Button::Focuse() {};
void Button::Unfocuse() {};
void Button::Hover() {};
void Button::UnHover() {};
void Button::KeyPress(uint32_t key) {};

void Button::Type(char) {};
bool Button::ContainPoint(int x, int y) {
    if (x < this->rect.x || x > this->rect.x + this->rect.w) return false;
    if (y < this->rect.y || y > this->rect.y + this->rect.h) return false;
    return true;
}
Button::Button(Window* win, int x, int y, int width, int height, const std::string& name, Font& font,
               const SDL_Color& color)
    : name_text(win, x, y, name, font) {
    if (name_text.GetHeight() + 2 * nm_padding >= height) name_text.SetHeight(height - 2 * nm_padding);
    if (name_text.GetWidth() + 2 * nm_padding >= width) name_text.SetWidth(width - 2 * nm_padding);
    this->rect.x = x;
    this->rect.y = y;
    this->name_text.SetX(x + (((this->rect.x - this->name_text.GetWidth()) >> 1)));
    this->name_text.SetY(y + (((this->rect.y - this->name_text.GetHeight()) >> 1)));
    this->col = color;
    this->renderer = win->main_ren;
};
void Button::SetPosition(int x, int y) {
    this->name_text.SetX(name_text.GetX() + x - this->rect.x);
    this->name_text.SetY(name_text.GetY() + y - this->rect.y);
    this->rect.x = x;
    this->rect.y = y;
}
void Button::Draw() {
    SDL_SetRenderDrawColor(this->renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(this->renderer, &rect);
    name_text.Draw();
};
