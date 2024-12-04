#include "HiddenField.h"

#include "Element.h"
#include "Image.h"
#include "TextField.h"
Image HiddenField::global_img;
HiddenField::HiddenField(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color)
    : TextField(win, x, y, length, font, bg_color) {
    if (!HiddenField::global_img.Loaded()) global_img.Init(win, 0, 0, "assets/images/hide.png");
    this->eye = global_img;
    eye.SetX(rect.x + rect.w);
    eye.SetY(rect.y);
    eye.SetWidth(eye.GetWidth() / 2);
    eye.SetHeight(rect.h, true);
    eye_src = {global_img.GetWidth() >> 1, 0, global_img.GetWidth() >> 1, global_img.GetHeight()};
}

void HiddenField::Init(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color) {
    TextField::Init(win, x, y, length, font);
    if (!HiddenField::global_img.Loaded()) global_img.Init(win, 0, 0, "assets/images/hide.png");
    this->eye = global_img;
    eye.SetX(rect.x + rect.w);
    eye.SetY(rect.y);
    eye.SetWidth(eye.GetWidth() / 2);
    eye.SetHeight(rect.h, true);
    eye_src = {global_img.GetWidth() >> 1, 0, global_img.GetWidth() >> 1, global_img.GetHeight()};
};
void HiddenField::Draw() {
    SDL_SetRenderDrawColor(this->renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderFillRect(this->renderer, &this->rect);
    SDL_SetRenderDrawColor(this->renderer, 255 - bg_color.b, 255 - bg_color.r, 255 - bg_color.g, 255);
    SDL_RenderDrawRect(this->renderer, &this->rect);
    uint32_t length = text.size() - start;
    if (length > max_length) length = max_length;

    if (hidden) {
        char star[] = "*";
        int dx = font.GetLetterWidth('*');
        int x = rect.x + padding;
        for (int i = 0; i < length; i++, x += dx) this->font.DrawText(this->renderer, x, rect.y + padding, star, 1);
    } else
        this->font.DrawText(this->renderer, rect.x + padding, rect.y + padding, text.c_str() + start, length);

    if (this->focused) {
        if (this->cursor_blink > 0) {
            SDL_SetRenderDrawColor(this->renderer, 255 - bg_color.g, bg_color.b, 255 - bg_color.b, bg_color.a);
            SDL_Rect cursor_rect{int(cursor_x + rect.x + padding), rect.y + padding, 2, int(font.GetLetterHeight())};
            SDL_RenderFillRect(renderer, &cursor_rect);
        }
        cursor_blink += 5;
    }
    eye.DrawPart(&eye_src);
}

Element* HiddenField::ContainPoint(int x, int y) {
    if (this->eye.ContainPoint(x, y)) return this;
    if (x < rect.x || x > rect.x + rect.w) return nullptr;
    if (y < rect.y || y > rect.y + rect.h) return nullptr;
    return this;
};
void HiddenField::MouseDown(const Event& event) {
    if (eye.ContainPoint(event.button.x, event.button.y)) {
        if (hidden) {
            eye_src.x = 0;
            hidden = false;
        } else {
            hidden = true;
            eye_src.x = global_img.GetWidth() >> 1;
        }
        return;
    }
    TextField::MouseDown(event);
}
