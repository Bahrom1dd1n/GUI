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
Button::Button(Window* win, int x, int y, int width, int height, const std::string& name, const Font& font,
               const SDL_Color& color)
    : name_text(win, x, y, name, font) {
    if (name_text.GetHeight() + nm_padding >= height) this->rect.h = name_text.GetHeight() + this->nm_padding * 2;
    if (name_text.GetWidth() + nm_padding >= width) this->rect.w = name_text.GetWidth() + nm_padding * 2;
    this->rect.x = x;
    this->rect.y = y;
    this->name_text.SetX(x + (((this->rect.x - this->name_text.GetWidth()) >> 1)));
    this->name_text.SetY(y + (((this->rect.y - this->name_text.GetHeight()) >> 1)));
    this->col = color;
    this->ren = win->main_ren;
};
void Button::SetPosition(int x, int y) {
    this->rect.x = x;
    this->rect.y = y;
    this->name_text.SetX(x + (((this->rect.x - this->name_text.GetWidth()) >> 1)));
    this->name_text.SetY(y + (((this->rect.y - this->name_text.GetHeight()) >> 1)));
}
void Button::Draw() {
    SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(ren, &rect);
};
