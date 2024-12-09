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
#include "Frame.h"
#include "HiddenField.h"
#include "Image.h"
#include "Rectangle.h"
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
    HiddenField password;
    Image img;
    Frame frame;
    Rectangle rect_frame;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col) {
        this->rect_frame.Init(this, width / 2 - 150, height / 2 - 250, 300, 500, {0, 200, 30});
        this->img.Init(this, width / 2 - 100, height - 150, "./assets/images/hide.png");
        this->font.Init("./Font2.ttf", 18, {10, 10, 10, 255});
        this->txt.Init(this, 0, rect_frame.GetY() + 30, "PARKING", font);
        this->field.Init(this, 0, txt.GetY() + txt.GetHeight() + 30, 20, font, {255, 255, 255, 255});
        this->password.Init(this, 0, field.GetY() + field.GetHeight() + 20, 20, font, {255, 255, 255, 255});
        this->but.Init(this, width / 2 - 50, password.GetY() + password.GetHeight() + 50, 100, 30, "Log In", font,
                       {200, 20, 200, 255});
        int center = rect_frame.GetX() + rect_frame.GetWidth() / 2;
        txt.SetX(center - txt.GetWidth() / 2);
        field.SetX(center - field.GetWidth() / 2);
        password.SetX(center - password.GetWidth() / 2);
        img.Scale(1);
        img.RotateTo(0);
        but.click_callback = [this](int x, int y) { this->Print(); };
        // but.OnClick = MyWin::Print();
        frame.Add(&rect_frame);
        frame.Add(&txt);
        frame.Add(&but);
        frame.Add(&field);
        frame.Add(&img);
        frame.Add(&password);
        this->Add(&frame);
    }
    void Print() { std::cout << "text = " << this->field.GetText() << std::endl; }
};
int main(int argc, char* args[]) {
    SDL_Color col{255, 255, 255, 255};
    MyWin win(0, 0, 1200, 800, "Hello", col);
    win.Start();
    SDL_Quit();
    return 0;
}
