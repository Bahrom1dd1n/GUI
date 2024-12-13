#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <cstdio>
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
    Frame reg_page;
    Font font;
    std::vector<Image> bg_images;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col, 40,
                 SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS) {
        this->InitRegPage();
    }
    void InitRegPage() {
        this->font.Init("./Font2.ttf", 18, {10, 10, 10, 255});
        Rectangle* rect_frame =
            new Rectangle(this, this->GetWidth() / 2 - 150, this->GetHeight() / 2 - 250, 300, 500, {0, 200, 30, 255});
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "PARKING", font);
        TextField* field = new TextField(this, 0, txt->GetY() + txt->GetHeight() + 30, 20, font, {255, 255, 255, 255});
        HiddenField* password =
            new HiddenField(this, 0, field->GetY() + field->GetHeight() + 20, 20, font, {255, 255, 255, 255});
        Button* but = new Button(this, this->GetWidth() / 2 - 50, password->GetY() + password->GetHeight() + 50, 100,
                                 30, "Log In", font, {200, 20, 200, 255});
        int center = rect_frame->GetX() + rect_frame->GetWidth() / 2;
        txt->SetX(center - txt->GetWidth() / 2);
        field->SetX(center - field->GetWidth() / 2);
        field->SetPlaceholder("Name");
        password->SetX(center - password->GetWidth() / 2);
        but->click_callback = [this](int x, int y) { this->Print(); };
        bg_images.resize(3);
        for (int i = 0; i < bg_images.size(); i++) {
            char location[50];
            snprintf(location, sizeof(location), "./assets/images/bg_images/bg%d.jpg", i + 1);
            bg_images[i] = Image(this, 0, 0, location);
        }
        // but.OnClick = MyWin::Print();
        reg_page.Add(rect_frame);
        reg_page.Add(txt);
        reg_page.Add(but);
        reg_page.Add(field);
        reg_page.Add(password);
        this->Add(&reg_page);
    }
    void Print() {
        static int i = 0;
        this->SetBackground(bg_images[i]);
        i++;
        if (i >= bg_images.size()) i = 0;
    }
    ~MyWin() {
        for (auto i : reg_page.GetChildren()) delete i;
    }
};
int main(int argc, char* args[]) {
    SDL_Color col{255, 255, 255, 255};
    MyWin win(0, 0, 1200, 760, "Hello", col);
    win.Start();
    SDL_Quit();
    return 0;
}
