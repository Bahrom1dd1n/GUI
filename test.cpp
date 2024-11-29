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
#include "Text.h"
#include "Window.h"

const int windowWidth = 400;
const int windowHeight = 600;

class MyWin : public Window {
   private:
    Font font;
    Button but;
    Text txt;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col)

    {
        this->font.Init("./Font2.ttf", 14, {10, 10, 10, 255});
        this->txt.Init(this, 10, 60, "Hello", font);
        this->but.Init(this, 10, 10, 100, 30, "Button", font, {10, 200, 10, 255});
        this->Add(&txt);
        this->Add(&but);
    }
};
int main(int argc, char* args[]) {
    SDL_Color col{255, 255, 255, 255};
    MyWin win(10, 10, 400, 400, "Hello", col);
    win.Start();
    SDL_Quit();
    return 0;
}
