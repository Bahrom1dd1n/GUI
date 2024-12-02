#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "Button.h"
#include "Font.h"
#include "Image.h"
#include "Text.h"
#include "TextField.h"
#include "Window.h"

const int windowWidth = 400;
const int windowHeight = 600;

class MyWin : public Window {
   private:
    Font font;
    Button but;
    Text txt;
    TextField field;
    Image img;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col) {
        this->font.Init("./Font2.ttf", 18, {10, 10, 10, 255});
        this->txt.Init(this, 10, 60, "This is Text", font);
        this->but.Init(this, 10, 10, 100, 30, "Button", font, {10, 200, 10, 255});
        this->field.Init(this, 120, 10, 20, font, {255, 255, 255, 255});
        this->img.Init(this, 10, 200, "./assets/images/toretto.jpg");
        img.Scale(0.3);
        img.RotateTo(45);

        // but.OnClick = MyWin::Print();

        this->Add(&txt);
        this->Add(&but);
        this->Add(&field);
        this->Add(&img);
    }
    void Print() { std::cout << "text = " << this->field.GetText(); }
};
int main(int argc, char* args[]) {
    SDL_Color col{255, 255, 255, 255};
    MyWin win(0, 0, 1200, 1000, "Hello", col);
    win.Start();
    SDL_Quit();
    return 0;
}
