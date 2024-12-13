#include "Text.h"

#include <SDL2/SDL_pixels.h>

#include "Font.h"
#include "Image.h"
#include "Window.h"
Text::Text(Window* win, int x, int y, const std::string& text, Font& font)
    : Image(font.ConvertToImage(win->main_ren, x, y, text)), text(text), font(font) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.h = font.GetLetterHeight();
    this->renderer = win->main_ren;
}

void Text::Init(Window* win, int x, int y, const std::string& text, Font& font) {
    this->renderer = win->main_ren;
    this->font = font;
    Image::operator=(font.ConvertToImage(this->renderer, x, y, text));
    this->text = text;
    this->rect.x = x;
    this->rect.y = y;
}
void Text::SetText(const ::std::string& text) {
    Image::operator=(font.ConvertToImage(this->renderer, rect.x, rect.y, text));
    this->text = text;
}
