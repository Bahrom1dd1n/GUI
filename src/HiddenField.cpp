#include "HiddenField.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "Element.h"
#include "Image.h"
#include "TextField.h"
#include "image_data.h"  // emded image data of eye icon

void HiddenField::LoadEmbeddedImage() {
    SDL_RWops* rw = SDL_RWFromConstMem(hide_png, hide_png_len);
    if (!rw) {
        printf("Failed to create RWops from memory: %s", SDL_GetError());
        exit(1);
        return;
    }

    SDL_Surface* image = IMG_Load_RW(rw, 1);  // 1 means SDL will free the RWops
    if (!image) {
        printf("Failed to load image from RWops: %s", IMG_GetError());
        exit(1);
    }
    this->global_img = Image(0, 0, this->renderer, image);
    SDL_FreeSurface(image);
}
Image HiddenField::global_img;
HiddenField::HiddenField(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color)
    : TextField(win, x, y, length, font, bg_color) {
    if (!HiddenField::global_img) {
        this->LoadEmbeddedImage();
    }
    global_img.Init(win, 0, 0, "assets/images/hide.png");
    this->eye = global_img;
    eye.SetX(rect.x + rect.w);
    eye.SetY(rect.y);
    eye.SetWidth(eye.GetWidth() / 2);
    eye.SetHeight(rect.h, true);
    eye_src = {0, 0, global_img.GetWidth() >> 1, global_img.GetHeight()};
}

void HiddenField::Init(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color) {
    TextField::Init(win, x, y, length, font);

    if (!HiddenField::global_img) this->LoadEmbeddedImage();
    this->eye = global_img;
    eye.SetX(rect.x + rect.w);
    eye.SetY(rect.y);
    eye.SetWidth(eye.GetWidth() / 2);
    eye.SetHeight(rect.h, true);
    eye_src = {0, 0, global_img.GetWidth() >> 1, global_img.GetHeight()};
};
void HiddenField::Draw() {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->renderer, &this->rect);
    eye.DrawPart(&eye_src);
    SDL_SetRenderDrawColor(this->renderer, 255 - color.b, 255 - color.r, 255 - color.g, 255);
    SDL_RenderDrawRect(this->renderer, &this->rect);
    uint32_t length = text.size() - start;
    if (length > max_length) length = max_length;
    if (!(text.size() || focused)) {
        uint8_t temp_a = text_color.a;
        text_color.a = 100;
        length = placeholder.length() > max_length ? length : placeholder.size();
        font.DrawText(renderer, rect.x + padding, rect.y + padding, placeholder.c_str() + start, length, text_color);
        text_color.a = temp_a;
        return;
    }
    if (hidden) {
        SDL_Rect dst_rect = {rect.x + padding, rect.y + padding, font.GetLetterWidth('*'), font.GetLetterHeight()};
        SDL_Rect src_rect = {font.font_info->letters['*' - 32], 0, dst_rect.w, dst_rect.h};
        SDL_SetTextureAlphaMod(font.font_info->texture, 255);
        for (int i = 0; i < length; i++) {
            SDL_RenderCopy(this->renderer, font.font_info->texture, &src_rect, &dst_rect);
            dst_rect.x += dst_rect.w;
        }
    } else
        text_width =
            this->font.DrawText(this->renderer, rect.x + padding, rect.y + padding, text.c_str() + start, length);
    if (this->focused) {
        if (this->cursor_blink > 0) {
            SDL_SetRenderDrawColor(this->renderer, 255 - color.g, color.b, 255 - color.b, color.a);
            SDL_Rect cursor_rect{int(cursor_x + rect.x + padding), rect.y + padding, 2, int(font.GetLetterHeight())};
            SDL_RenderFillRect(renderer, &cursor_rect);
        }
        cursor_blink += 5;
    }
    // SDL_RenderDrawRect(renderer, &eye.GetBorders());
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
            eye_src.x = global_img.GetWidth() >> 1;
            hidden = false;
        } else {
            eye_src.x = 0;
            hidden = true;
        }
        return;
    }
    TextField::MouseDown(event);
}
