#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

// #include "Button.h"
#include "Font.h"
// #include "Text.h"
#include "Window.h"

const int windowWidth = 400;
const int windowHeight = 600;
class Text : public Element {
   private:
    SDL_FRect rect;
    std::string text;
    Texture text_texture;
    Font font;

   public:
    Text() = default;
    Text(Window* win, int x, int y, const std::string& text, const Font& font, const SDL_Color& color = {0, 0, 0, 255});
    void Init(Window* win, int x, int y, const std::string& text, const Font& font,
              const SDL_Color& color = {0, 0, 0, 255});

    void SetX(int x);
    void SetY(int y);
    void SetPosition(int x, int y);
    inline uint32_t GetWidth() const { return this->rect.w; };
    inline uint32_t GetHeight() const { return this->rect.h; };
    inline const std::string& GetText() const { return this->text; };
    // overiding virtual functions of Element class
    void Draw() override;
    void Click() override;
    void Focuse() override;
    void Unfocuse() override;
    void Hover() override;
    void UnHover() override;
    void KeyPress(uint32_t key) override;
    void Type(char) override;
    bool ContainPoint(int x, int y) override;
    ~Text();
};
class MyWin : public Window {
   private:
    // Button but;
    Text txt;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", {255, 255, 255})

    {
        new (&txt) Text(this, 20, 20, "This is Text", Font("./Font2.ttf", 16, {0, 0, 0, 255}));
        //  new (&but)Button(this, 100, 100, 50, 20, "Button", Font("./Font2.ttf", 16, {0, 0, 0, 255}), {0, 255, 100,
        //  255});

        this->Add(&txt);
        // this->Add(&but);
    }
};
int main(int argc, char* args[]) {
    SDL_Color col{255, 255, 255, 255};
    MyWin win(10, 10, 400, 400, "Hello", col);
    win.Start();
    SDL_Quit();
    return 0;
}

Text::Text(Window* win, int x, int y, const std::string& text, const Font& font, const SDL_Color& color) : text(text) {
    new (&this->font) Font(font);
    new (&this->text_texture) Texture(this->font.ConvertToTextuer(win->main_ren, text));
    this->rect.x = x;
    this->rect.y = y;
    this->rect.h = font.GetLetterHeight();
    this->rect.w = this->text_texture.GetWidth();
    this->renderer = win->main_ren;
}

void Text::Init(Window* win, int x, int y, const std::string& text, const Font& font, const SDL_Color& color) {
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
