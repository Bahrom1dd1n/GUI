#include "Text.h"

#include "Font.h"
#include "Window.h"
Text::Text(Window* win, int x, int y, const std::string& text, const Font& font) : text(text) {
    new (&this->font) Font(font);
    new (&this->text_texture) Texture(this->font.ConvertToTextuer(win->main_ren, text));
    this->rect.x = x;
    this->rect.y = y;
    this->rect.h = font.GetLetterHeight();
    this->rect.w = this->text_texture.GetWidth();
    this->renderer = win->main_ren;
}

void Text::Init(Window* win, int x, int y, const std::string& text, const Font& font) {
    this->text = text;
    this->~Text();
    new (&this->font) Font(font);
    new (&this->text_texture) Texture(this->font.ConvertToTextuer(win->main_ren, text));
    this->rect.x = x;
    this->rect.y = y;
    this->rect.h = font.GetLetterHeight();
    this->rect.w = this->text_texture.GetWidth();
    this->renderer = win->main_ren;
}
void Text::Draw() {
    this->text_texture.Render(&this->rect);
};

void Text::SetX(int x) {
    this->rect.x = x;
}
void Text::SetY(int y) {
    this->rect.y = y;
}
void Text::SetPosition(int x, int y) {
    this->rect.x = x;
    this->rect.y = y;
}
// overiding virtual functinos of bstract class Element
void Text::Click() {};
void Text::Focuse() {};
void Text::Unfocuse() {};
void Text::Hover() {};
void Text::UnHover() {};
void Text::KeyPress(uint32_t key) {};
void Text::Type(char) {};
bool Text::ContainPoint(int x, int y) {
    if (x < this->rect.x || x > this->rect.x + this->rect.w) return false;
    if (y < this->rect.y || y > this->rect.y + this->rect.h) return false;
    return true;
};

Text::~Text() {
}
