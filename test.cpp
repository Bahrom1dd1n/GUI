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
    Font font = Font("./Font2.ttf", 14, {0, 0, 0, 255});
    Button but = Button(this, 10, 10, 100, 30, "Button", font, {10, 200, 10});
    Text txt = Text(this, 10, 60, "Hello", font);

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col)

    {
        //  new (&but)Button(this, 100, 100, 50, 20, "Button", Font("./Font2.ttf", 16, {0, 0, 0, 255}), {0, 255, 100,
        //  255});

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
