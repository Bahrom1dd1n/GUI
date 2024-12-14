#include "TextField.h"

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <cstdio>

#include "Element.h"

TextField::TextField(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& color,
                     const SDL_Color& text_color)
    : font(font), color(color), text_color(text_color) {
    this->renderer = win->main_ren;
    this->text_color = text_color;
    font.LoadFontTextures(win->main_ren);
    int width = font.GetLetterWidth('A') * length + 2 * padding;
    int height = font.GetLetterHeight() + 2 * padding;
    this->rect = {x, y, width, height};
    this->max_length = length;
}

void TextField::Init(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& color,
                     const SDL_Color& text_color) {
    this->renderer = win->main_ren;
    this->font = font;
    this->color = color;
    this->text_color = text_color;
    font.LoadFontTextures(win->main_ren);
    int width = font.GetLetterWidth('A') * length + 2 * padding;
    int height = font.GetLetterHeight() + 2 * padding;
    this->rect = {x, y, width, height};
    this->max_length = length;
}
void TextField::Draw() {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->renderer, &this->rect);
    SDL_SetRenderDrawColor(this->renderer, 255 - color.b, 255 - color.r, 255 - color.g, 255);
    SDL_RenderDrawRect(this->renderer, &this->rect);
    if (this->text.size()) {
        int32_t length = text.size() - start;
        if (length > max_length) length = max_length;
        text_width = this->font.DrawText(this->renderer, rect.x + padding, rect.y + padding, text.c_str() + start,
                                         length, text_color);
    } else {
        if (!this->focused) {
            uint8_t temp = text_color.a;
            text_color.a = 100;
            text_width = this->font.DrawText(this->renderer, rect.x + padding, rect.y + padding,
                                             placeholder.c_str() + start, placeholder.size(), text_color);
            text_color.a = temp;
        }
    }
    if (this->focused) {
        if (this->cursor_blink > 0) {
            SDL_SetRenderDrawColor(this->renderer, 255 - color.g, color.b, 255 - color.b, color.a);
            SDL_Rect cursor_rect{int(cursor_x + rect.x + padding), rect.y + padding, 2, int(font.GetLetterHeight())};
            SDL_RenderFillRect(renderer, &cursor_rect);
        }
        cursor_blink += 5;
    }
}
// return true if this element contains point of given coordinates
Element* TextField::ContainPoint(int x, int y) {
    if (x < rect.x || x > rect.x + rect.w) return nullptr;
    if (y < rect.y || y > rect.y + rect.h) return nullptr;
    return this;
};
// behavior of gui elemnt when it's been pressed
void TextField::MouseDown(const Event& event) {
    int m_dis = event.button.x - this->rect.x - padding;
    cursor_blink = 1;
    cursor_x = 0;
    cursor_index = start;

    if (m_dis > 0 && text.size()) {
        int i = 0;
        while (cursor_x < m_dis && i < text.size() && i < this->max_length) {
            cursor_x += this->font.GetLetterWidth(this->text[cursor_index]);
            i++;
            cursor_index++;
        }
        int width = font.GetLetterWidth(this->text[cursor_index - 1]);
        if ((cursor_x - m_dis) * 2 > width) {
            cursor_x -= width;
            cursor_index--;
        }
    }
    if (mouse_down_callback) mouse_down_callback(event.button.x, event.button.y);
};
// focuse to current gui element (when mouse clicked on it or some specific event is happened)
void TextField::Focuse() {
    printf("clicked\n");
    this->focused = true;
    cursor_blink = 1;
    this->cursor_x = 0;
    for (char l : this->text) {
        cursor_x += this->font.GetLetterWidth(l);
    }
};
// unfocuses gui element
void TextField::Unfocuse() {
    this->focused = false;
};
// behavior of gui element when when specific key is pressed
void TextField::KeyDown(const Event& event) {
    char letter = event.text.text[0];
    if (31 < letter && 127 > letter) {
        this->Type(letter);
        return;
    };
    switch (event.key.keysym.sym) {
        case SDLK_BACKSPACE:
            cursor_blink = 1;
            if (cursor_index) {
                cursor_index--;
                if (start) {
                    this->start--;
                } else {
                    int temp_width = this->font.GetLetterWidth(this->text[cursor_index]);
                    cursor_x -= temp_width;
                    text_width -= temp_width;
                }
                this->text.erase(cursor_index, 1);
            }
            break;
        case SDLK_DELETE:
            cursor_blink = 1;
            if (cursor_index < this->text.size()) {
                this->text.erase(cursor_index, 1);
            }
            break;

        case SDLK_LEFT:
            cursor_blink = 1;
            if (cursor_index) {
                cursor_index--;
                if (start && cursor_x <= font.GetLetterWidth('A') + padding) {
                    this->start--;
                } else {
                    cursor_x -= this->font.GetLetterWidth(this->text[cursor_index]);
                }
            }
            break;
        case SDLK_RIGHT:
            cursor_blink = 1;
            if (cursor_index < this->text.size()) {
                if (cursor_x < rect.w - 2 * padding) {
                    cursor_x = cursor_x + this->font.GetLetterWidth(this->text[cursor_index]);
                } else {
                    start++;
                }
                cursor_index++;
            }
            break;
    };
    if (key_down_callback) key_down_callback(event.key.keysym.sym);
};
// behavior of gui element when when typed
void TextField::Type(char letter) {
    this->text.insert(cursor_index, 1, letter);
    int lw = this->font.GetLetterWidth(this->text[cursor_index]);
    if (rect.w - padding >= lw + text_width) {
        cursor_x = cursor_x + lw;
        text_width += lw;
    } else {
        start++;
    }
    cursor_index++;
    this->cursor_blink = 1;
};
// behavior of gui element when mouse enters area of gui element
