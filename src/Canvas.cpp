#include "Canvas.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <cstddef>
#include <cstdio>

#include "Window.h"

Canvas::Canvas(Window* win, int x, int y, int width, int height) {
    this->rect = {x, y, width, height};
    this->renderer = win->main_ren;
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}
void Canvas::Clear(const SDL_Color& color) {
    SDL_SetRenderTarget(this->renderer, this->texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}
void Canvas::Draw() {
    SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rect);
    if (!this->border_width) return;
    // drawing borders
    SDL_Rect border = {rect.x - border_width, rect.y, border_width, rect.h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->renderer, &border);
    border.x = rect.x + rect.w;
    SDL_RenderFillRect(this->renderer, &border);
    border = {rect.x - border_width, rect.y - border_width, rect.w + 2 * border_width, border_width};
    SDL_RenderFillRect(this->renderer, &border);
    border.y = rect.y + rect.h;
    SDL_RenderFillRect(this->renderer, &border);
}
void Canvas::DrawLine(int x, int y, int x2, int y2, const SDL_Color& color) {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    SDL_SetRenderTarget(this->renderer, this->texture);
    SDL_RenderDrawLine(this->renderer, x, y, x2, y2);
    SDL_SetRenderTarget(this->renderer, nullptr);
};
void Canvas::DrawImage(int x, int y, const Image& img) {
    SDL_Rect temp = img.GetBorders();
    temp.x = x;
    temp.y = y;
    SDL_SetRenderTarget(this->renderer, this->texture);
    img.DrawTo(&temp);
    SDL_SetRenderTarget(renderer, nullptr);
};
void Canvas::FillRectangle(int x, int y, int w, int h, const SDL_Color& color) {
    SDL_Rect temp = {x, y, w, h};
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderTarget(renderer, nullptr);
}
void Canvas::DrawRectangle(int x, int y, int w, int h, int border_width, const SDL_Color& border_color) {
    SDL_Rect temp = {x, y, w, h};
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
    if (border_width == 1) {
        SDL_RenderDrawRect(renderer, &temp);
        SDL_SetRenderTarget(renderer, nullptr);
        return;
    }
    temp.w = border_width;
    SDL_RenderFillRect(renderer, &temp);
    temp.x = x + w - border_width;
    SDL_RenderFillRect(renderer, &temp);
    temp = {x, y, w, border_width};
    SDL_RenderFillRect(renderer, &temp);
    temp.y = y + h - border_width;
    SDL_RenderFillRect(renderer, &temp);
    SDL_SetRenderTarget(renderer, nullptr);
};
void Canvas::DrawText(int x, int y, const char* text, uint32_t length, Font& font, const SDL_Color& color) {
    SDL_SetRenderTarget(this->renderer, this->texture);
    font.DrawText(this->renderer, x, y, text, length, color);
    SDL_SetRenderTarget(this->renderer, nullptr);
}
