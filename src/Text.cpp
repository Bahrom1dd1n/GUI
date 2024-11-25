#include "Text.h"

#include <cstdint>

#include "Window.hpp"

inline Text::Text(Window* win, int x, int y, const std::string& text, const Font& font)
    : font(font), text(text), text_texture(font.ConvertToTextuer(text.c_str(), text.size())) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.h = font.GetLetterHeight();
    this->rect.w = this->text_texture.GetWidth();
    this->ren = win->main_ren;
}
inline void Text::Draw() {
    this->text_texture.Render(&this->rect);
};

inline void Text::SetX(int x) {
    this->rect.x = x;
}
inline void Text::SetY(int y) {
    this->rect.y = y;
}
inline void Text::SetPosition(int x, int y) {
    this->rect.x = x;
    this->rect.y = y;
}
Text::~Text() {
}
