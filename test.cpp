#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
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
    Frame login_page;
    Frame reg_page;
    Font font;
    Font header1;
    std::vector<Image> bg_images;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col, 40,
                 SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS) {
        this->font.Init("./Font2.ttf", 18, FontStyle::NORMAL);
        this->header1.Init("./Font2.ttf", 25, FontStyle::BOLD);
        bg_images.resize(3);
        for (int i = 0; i < bg_images.size(); i++) {
            char location[50];
            snprintf(location, sizeof(location), "./assets/images/bg_images/bg%d.jpg", i + 1);
            bg_images[i] = Image(this, 0, 0, location);
        }
        this->SetBackground(bg_images[0]);
        this->InitLoginPage();
        this->InitRegPage();
        login_page.SetVisible(true);
        reg_page.SetVisible(false);
        this->Add(&login_page);
        this->Add(&reg_page);
    }
    void InitLoginPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 500, {20, 20, 230, 255});
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Log In", header1, {255, 255, 255, 255});
        TextField* field = new TextField(this, 0, txt->GetY() + txt->GetHeight() + 30, 20, font, {255, 255, 255, 255});
        HiddenField* password =
            new HiddenField(this, 0, field->GetY() + field->GetHeight() + 20, 20, font, {255, 255, 255, 255});
        Button* but = new Button(this, this->GetWidth() / 2 - 50, password->GetY() + password->GetHeight() + 50, 100,
                                 30, "Log In", font, {200, 20, 20, 255});
        int center = this->GetWidth() >> 1;
        rect_frame->SetCenterX(center);
        txt->SetCenterX(center);

        field->SetCenterX(center);
        field->SetPlaceholder("username");

        password->SetPlaceholder("password");
        password->SetCenterX(center);

        but->click_callback = [this](int x, int y) {
            login_page.SetVisible(false);
            reg_page.SetVisible(true);
            this->SetBackground(bg_images[1]);
        };

        login_page.Add(rect_frame);
        login_page.Add(txt);
        login_page.Add(but);
        login_page.Add(field);
        login_page.Add(password);
    }
    void InitRegPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 500, {20, 20, 230, 255});
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Register", header1, {255, 255, 255, 255});
        TextField* field = new TextField(this, 0, txt->GetY() + txt->GetHeight() + 30, 20, font, {255, 255, 255, 255});
        HiddenField* password =
            new HiddenField(this, 0, field->GetY() + field->GetHeight() + 20, 20, font, {255, 255, 255, 255});
        HiddenField* password2 =
            new HiddenField(this, 0, password->GetCenterY() + field->GetHeight() + 20, 20, font, {255, 255, 255, 255});

        Button* but = new Button(this, 0, password2->GetCenterY() + password2->GetHeight() + 50, 100, 30, "Save", font,
                                 {200, 20, 200, 255});

        int center = this->GetWidth() >> 1;
        rect_frame->SetCenterX(center);
        txt->SetCenterX(center);
        txt->SetCenterX(center);

        field->SetCenterX(center);
        field->SetPlaceholder("username");

        password->SetCenterX(center);
        password->SetPlaceholder("Enter password");
        password2->SetCenterX(center);
        password2->SetPlaceholder("Renter password");
        but->SetCenterX(center);
        but->click_callback = [this](int x, int y) {
            login_page.SetVisible(true);
            reg_page.SetVisible(false);
            this->SetBackground(bg_images[0]);
        };

        // but.OnClick = MyWin::Print();
        reg_page.Add(rect_frame);
        reg_page.Add(txt);
        reg_page.Add(field);
        reg_page.Add(password);
        reg_page.Add(password2);
        reg_page.Add(but);
    }

    ~MyWin() {
        for (auto i : login_page.GetChildren()) delete i;

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
