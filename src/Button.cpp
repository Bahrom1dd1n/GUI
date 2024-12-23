#include "Button.h"

#include "Element.h"

void Button::Click() {
    this->clicked = 2 * dw;
};

void Button::Focuse() {};
void Button::Unfocuse() {};
void Button::MouseDown(const Event& event) {
    this->Click();
    if (this->click_callback) this->click_callback(event.button.x, event.button.y);
}
void Button::KeyDown(const Event& event) {};

Element* Button::ContainPoint(int x, int y) {
    if (x < this->rect.x || x > this->rect.x + this->rect.w) return nullptr;
    if (y < this->rect.y || y > this->rect.y + this->rect.h) return nullptr;
    return this;
}
Button::Button(Window* win, int x, int y, int width, int height, const std::string& name, Font& font,
               const SDL_Color& color)
    : name_text(win, x, y, name, font) {
    this->renderer = win->main_ren;
    this->rect = {x, y, width, height};
    if (name_text.GetHeight() + 2 * nm_padding >= height) name_text.SetHeight(height - 2 * nm_padding);
    if (name_text.GetWidth() + 2 * nm_padding >= width) name_text.SetWidth(width - 2 * nm_padding);
    this->name_text.SetX(x + (((this->rect.w - this->name_text.GetWidth()) >> 1)));
    this->name_text.SetY(y + (((this->rect.h - this->name_text.GetHeight()) >> 1)));
    this->color = color;
};

Button::Button(Window* win, int x, int y, int width, int height, Image& img) {
    this->renderer = win->main_ren;
    this->rect = {x, y, width, height};
    this->color = {255, 255, 255, 255};
    this->SetImage(img);
}

void Button::Init(Window* win, int x, int y, int width, int height, const std::string& name, Font& font,
                  const SDL_Color& color) {
    this->renderer = win->main_ren;
    this->rect = {x, y, width, height};
    this->name_text.Init(win, x, y, name, font);
    if (name_text.GetHeight() + 2 * nm_padding >= height) name_text.SetHeight(height - 2 * nm_padding);
    if (name_text.GetWidth() + 2 * nm_padding >= width) name_text.SetWidth(width - 2 * nm_padding);
    this->name_text.SetX(x + (((this->rect.w - this->name_text.GetWidth()) >> 1)));
    this->name_text.SetY(y + (((this->rect.h - this->name_text.GetHeight()) >> 1)));
    this->color = color;
};
void Button::SetImage(Image& new_image) {
    this->img = new_image;
    if (img.GetWidth() > rect.w) img.SetWidth(rect.x, true);
    if (img.GetHeight() > rect.h) img.SetHeight(rect.h, true);
    this->img.SetX(rect.x + ((rect.w - img.GetWidth()) >> 1));
    this->img.SetY(rect.y + ((rect.h - img.GetHeight()) >> 1));
}
void Button::Draw() {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->renderer, &rect);
    // if (this->clicked > 0) {
    //     this->clicked--;
    //
    // } else {
    //     if (this->clicked == 1) {
    //         this->rect = {rect.x - dw, rect.y - dw, rect.w + dw * 2, rect.h + dw * 2};
    //         this->clicked = 0;
    //     }
    // }
    if (clicked > 0) {
        if (clicked > dw) {
            rect = {rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2};
        } else {
            rect = {rect.x - 1, rect.y - 1, rect.w + 2, rect.h + 2};
        }
        clicked--;
    }
    if (name_text.GetText().size())
        name_text.Draw();
    else if (this->img)
        img.Draw();
};
