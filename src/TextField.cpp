#include "TextField.h"

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <cstdio>

#include "Element.h"

TextField::TextField(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color)
    : font(font), bg_color(bg_color) {
    this->renderer = win->main_ren;
    font.ConvertToImage(win->main_ren, "");
    int width = font.GetLetterWidth('A') * length;
    int height = font.GetLetterHeight() + 2 * padding;
    this->rect = {x, y, width, height};
    this->max_length = length;
}

void TextField::Init(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color) {
    this->renderer = win->main_ren;
    this->font = font;
    this->bg_color = bg_color;
    font.ConvertToImage(win->main_ren, "");
    int width = font.GetLetterWidth('A') * length + 2 * padding;
    int height = font.GetLetterHeight() + 2 * padding;
    this->rect = {x, y, width, height};
    this->max_length = length;
}
void TextField::Draw() {
    SDL_SetRenderDrawColor(this->renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderFillRect(this->renderer, &this->rect);
    SDL_SetRenderDrawColor(this->renderer, 255 - bg_color.b, 255 - bg_color.r, 255 - bg_color.g, 255);
    SDL_RenderDrawRect(this->renderer, &this->rect);
    uint32_t length = text.size() - start;
    if (length > max_length) length = max_length;
    this->font.DrawText(this->renderer, rect.x + padding, rect.y + padding, text.c_str() + start, length);
    if (this->focused) {
        if (this->cursor_blink > 0) {
            SDL_SetRenderDrawColor(this->renderer, 255 - bg_color.g, bg_color.b, 255 - bg_color.b, bg_color.a);
            SDL_Rect cursor_rect{int(cursor_x + rect.x + padding), rect.y + padding, 2, int(font.GetLetterHeight())};
            SDL_RenderFillRect(renderer, &cursor_rect);
        }
        cursor_blink += 5;
    }
}
// return true if this element contains point of given coordinates
bool TextField::ContainPoint(int x, int y) {
    if (x < rect.x || x > rect.x + rect.w) return false;
    if (y < rect.y || y > rect.y + rect.h) return false;
    return true;
};
// behavior of gui elemnt when it's been pressed
void TextField::MouseDown(const Event& event) {
    if (!this->ContainPoint(event.button.x, event.button.y)) return;
    int m_dis = event.button.x - this->rect.x;
    cursor_x = padding;
    cursor_index = start;
    int i = start;

    while (cursor_x < m_dis && cursor_index < text.size()) {
        cursor_x += this->font.GetLetterWidth(this->text[i]);
        i++;
        cursor_index++;
    }
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
    if (31 < letter && 127 > letter) this->Type(letter);
    switch (event.key.keysym.sym) {
        case SDLK_BACKSPACE:
            cursor_blink = 1;
            if (cursor_index) {
                cursor_index--;
                if (start) {
                    this->start--;
                } else {
                    cursor_x -= this->font.GetLetterWidth(this->text[cursor_index]);
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
};
// behavior of gui element when when typed
void TextField::Type(char letter) {
    this->text.insert(cursor_index, 1, letter);
    if (cursor_x < rect.w - 2 * padding) {
        cursor_x = cursor_x + this->font.GetLetterWidth(this->text[cursor_index]);
    } else {
        start++;
    }
    cursor_index++;
    this->cursor_blink = 1;
};
// behavior of gui element when mouse enters area of gui element
