#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "Button.h"
#include "Font.h"
#include "Window.h"

SDL_Renderer* main_ren;
const int windowWidth = 400;
const int windowHeight = 600;
const int delay = 30;
int time_elapsed = 0;
class MyWin : public Window {
   private:
    Button but;
    Text txt;

   public:
    MyWin()
        : Window(100, 100, 500, 400, "My Window", {255, 255, 255}),
          txt(this, 20, 20, "This is Text", Font("./font2.ttf", 16, {0, 0, 0, 255})),
          but(this, 100, 100, 50, 20, "Button", Font("./Font2.ttf", 16, {0, 0, 0, 255}), {0, 255, 100, 255})

    {}
};
int main(int argc, char* args[]) {
    SDL_Color col{255, 255, 255, 255};
    Window win(10, 10, 400, 400, "Hello", col);
    win.Start();
    SDL_Quit();
    return 0;
}
