#include "Text.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <iterator>

#include "Font.h"
#include "Image.h"
#include "Window.h"
Text::Text(Window* win, int x, int y, const std::string& text, Font& font, const SDL_Color& text_color)
    : Image(font.ConvertToImage(win->main_ren, x, y, text, text_color)), text(text), font(font) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.h = font.GetLetterHeight();
    this->renderer = win->main_ren;
}

Text::Text(SDL_Renderer* renderer, const std::string& text, Font& font, const SDL_Color& text_color)
    : Image(font.ConvertToImage(renderer, 0, 0, text, text_color)), text(text), font(font) {
    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.h = font.GetLetterHeight();
    this->renderer = renderer;
}

void Text::Init(Window* win, int x, int y, const std::string& text, Font& font, const SDL_Color& text_color) {
    this->renderer = win->main_ren;
    this->font = font;
    Image::operator=(font.ConvertToImage(this->renderer, x, y, text, text_color));
    this->text = text;
    this->rect.x = x;
    this->rect.y = y;
}
void Text::SetText(const ::std::string& text) {
    Image::operator=(font.ConvertToImage(this->renderer, rect.x, rect.y, text));
    this->text = text;
}
