#include "Text.h"

#include <SDL2/SDL_pixels.h>

#include "Font.h"
#include "Image.h"
#include "Window.h"
Text::Text(Window* win, int x, int y, const std::string& text, Font& font, const SDL_Color& color)
    : Image(font.ConvertToImage(this->renderer, text)), text(text), font(font) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.h = font.GetLetterHeight();
    this->renderer = win->main_ren;
}

void Text::Init(Window* win, int x, int y, const std::string& text, Font& font, const SDL_Color& color) {
    this->renderer = win->main_ren;
    this->font = font;
    Image::operator=(font.ConvertToImage(this->renderer, text));
    this->text = text;
    this->rect.x = x;
    this->rect.y = y;
}
Text::~Text() {
}
