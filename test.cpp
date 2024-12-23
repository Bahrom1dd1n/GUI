#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Button.h"
#include "Canvas.h"
#include "Chart.h"
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
    Frame reg2_page;
    Frame floors_page;
    Frame pay_page;
    Chart chart;
    Font font;
    Font header1;
    std::vector<Image> bg_images;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col, 40,
                 SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS) {
        this->font.Init("./Font2.ttf", 18, FontStyle::NORMAL);
        this->header1.Init("./Font2.ttf", 25, FontStyle::BOLD);
        bg_images.resize(4);
        for (int i = 0; i < bg_images.size(); i++) {
            char location[50];
            snprintf(location, sizeof(location), "./assets/images/bg_images/bg%d.jpg", i + 1);
            bg_images[i] = Image(this, 0, 0, location);
        }
        this->SetBackground(bg_images[0]);
        this->InitLoginPage();
        this->InitRegPage();
        this->InitReg2Page();
        this->InitFloors();
        this->InitPayPage();
        login_page.SetVisible(true);
        reg_page.SetVisible(false);
        reg2_page.SetVisible(false);
        pay_page.SetVisible(false);
        floors_page.SetVisible(false);
    }
    void InitLoginPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 350, {20, 20, 230, 255});
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Log In", header1, {255, 255, 255, 255});
        TextField* field = new TextField(this, 0, txt->GetY() + txt->GetHeight() + 50, 20, font, {255, 255, 255, 255});
        HiddenField* password =
            new HiddenField(this, 0, field->GetY() + field->GetHeight() + 20, 20, font, {255, 255, 255, 255});
        Button* but = new Button(this, 0, rect_frame->GetY() + rect_frame->GetHeight() - 60, 100, 30, "Next", font,
                                 {200, 20, 20, 255});
        int center = this->GetWidth() >> 1;
        rect_frame->SetCenterX(center);
        txt->SetCenterX(center);

        field->SetCenterX(center);
        field->SetPlaceholder("username");

        password->SetPlaceholder("password");
        password->SetCenterX(center);
        but->SetCenterX(center);
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

        this->Add(&login_page);
    }
    void InitRegPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 350, {20, 20, 230, 255});
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Register", header1, {255, 255, 255, 255});
        TextField* field = new TextField(this, 0, txt->GetY() + txt->GetHeight() + 50, 20, font, {255, 255, 255, 255});
        HiddenField* password =
            new HiddenField(this, 0, field->GetY() + field->GetHeight() + 20, 20, font, {255, 255, 255, 255});
        HiddenField* password2 =
            new HiddenField(this, 0, password->GetY() + field->GetHeight() + 20, 20, font, {255, 255, 255, 255});

        Button* but = new Button(this, 0, rect_frame->GetY() + rect_frame->GetHeight() - 60, 100, 30, "Next", font,
                                 {200, 20, 20, 255});

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
            reg2_page.SetVisible(true);
            reg_page.SetVisible(false);
            this->SetBackground(bg_images[2]);
        };

        // but.OnClick = MyWin::Print();
        reg_page.Add(rect_frame);
        reg_page.Add(txt);
        reg_page.Add(field);
        reg_page.Add(password);
        reg_page.Add(password2);
        reg_page.Add(but);

        this->Add(&reg_page);
    }
    void InitReg2Page() {
        int center = this->GetCenterX();
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 400, 450, {20, 20, 230, 255});
        rect_frame->SetCenterX(center);
        rect_frame->SetCenterY(this->GetCenterY());
        reg2_page.Add(rect_frame);

        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Personal Info", header1, {255, 255, 255, 255});
        txt->SetCenterX(center);

        TextField* field = (TextField*)txt;
        std::string placehoders[] = {"Emter full name",    "Enter plate number", "Enter vehicle type",
                                     "Enter your address", "Enter phone number", "Enter email addres"};
        for (int i = 0; i < 6; i++) {
            field = new TextField(this, 0, field->GetY() + field->GetHeight() + 20, 30, font, {255, 255, 255, 255});
            field->SetCenterX(center);
            field->SetPlaceholder(placehoders[i]);
            reg2_page.Add(field);
        }

        Button* but =
            new Button(this, 0, field->GetY() + field->GetHeight() + 30, 100, 30, "Save", font, {200, 20, 20, 255});
        but->SetCenterX(center);
        but->click_callback = [this](int x, int y) {
            reg2_page.SetVisible(false);
            floors_page.SetVisible(true);
            this->SetBackground(bg_images[3]);
        };

        // but.OnClick = MyWin::Print();
        reg2_page.Add(txt);
        reg2_page.Add(but);

        this->Add(&reg2_page);
    }
    void InitFloors() {
        chart.Load("chart.dat");
        Canvas* canvas = MakeCanvas(this->GetWidth() - 200, this->GetHeight(), chart);
        if ((this->GetWidth() - canvas->GetWidth()) >> 1 > 200)
            canvas->SetCenterX(this->GetCenterX());
        else
            canvas->SetX(this->GetWidth() - canvas->GetWidth());
        canvas->SetCenterY(this->GetCenterY());
        DrawChart(canvas, chart, 0);
        canvas->SetBorderWidth(8);
        canvas->SetBorderColor({10, 100, 100, 255});
        for (int i = 0, y = (this->GetHeight() - chart.floors.size() * 100 + 50) >> 1; i < chart.floors.size();
             i++, y += 100) {
            char name[10] = {0};
            snprintf(name, 10, "Level %d", i + 1);
            Button* but = new Button(this, 25, y, 150, 50, name, font, {255, 165, 0, 255});
            but->click_callback = [this, i, canvas](int, int) { DrawChart(canvas, chart, i); };

            floors_page.Add(but);
        };
        Button* choose = new Button(this, 25, this->GetHeight() - 70, 120, 50, "Select", font, {220, 20, 20, 255});
        choose->click_callback = [this](int x, int y) {
            floors_page.SetVisible(false);
            pay_page.SetVisible(true);
            this->SetBackground(bg_images[3]);
        };
        floors_page.Add(choose);
        floors_page.Add(canvas);
        this->Add(&floors_page);
    }
    void InitPayPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 350, {20, 20, 230, 255});
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Payment Details", header1, {255, 255, 255, 255});
        HiddenField* card_num =
            new HiddenField(this, 0, txt->GetY() + txt->GetHeight() + 20, 16, font, {255, 255, 255, 255});

        Button* but = new Button(this, 0, rect_frame->GetY() + rect_frame->GetHeight() - 60, 100, 30, "Pay", font,
                                 {200, 20, 20, 255});

        int center = this->GetWidth() >> 1;
        rect_frame->SetCenterX(center);
        txt->SetCenterX(center);

        card_num->SetCenterX(center);
        card_num->SetPlaceholder("Enter card number");
        but->SetCenterX(center);
        but->click_callback = [this](int x, int y) {
            pay_page.SetVisible(false);
            login_page.SetVisible(true);
            this->SetBackground(bg_images[0]);
        };

        // but.OnClick = MyWin::Print();
        pay_page.Add(rect_frame);
        pay_page.Add(txt);
        pay_page.Add(card_num);
        pay_page.Add(but);
        this->Add(&pay_page);
    }
    Canvas* MakeCanvas(int max_width, int max_height, Chart& chart) {
        uint16_t cell_x = max_width / chart.width;
        uint16_t cell_y = max_height / chart.height;
        uint16_t cell = cell_x > cell_y ? cell_y : cell_x;
        Canvas* canvas = new Canvas(this, 0, 0, cell * chart.width, cell * chart.height);
        return canvas;
    }
    void DrawChart(Canvas* canvas, const Chart& chart, uint16_t num_floor) {
        if (num_floor >= chart.floors.size()) {
            printf("out of floors index\n");
            return;
        }
        int cell_x = (canvas->GetWidth()) / chart.width;
        int cell_y = (canvas->GetHeight()) / chart.height;
        int cell = cell_x > cell_y ? cell_y : cell_x;
        canvas->Clear({100, 100, 100, 255});
        for (auto i : *chart.floors[num_floor]) {
            int x = i->x * cell;
            int y = i->y * cell;
            int w = 0, h = 0;
            switch (i->car_type) {
                case 1:
                    w = cell >> 1;
                    h = cell;
                    break;
                case 2:
                    w = cell;
                    h = 2 * cell;
                    break;
                case 3:
                    w = 2 * cell;
                    h = 3 * cell;
                    break;
            }
            if (i->orientation) {
                w = w + h;
                h = w - h;
                w -= h;
            }

            int c_y = (h - font.GetLetterHeight()) >> 1;
            for (int n = 0; n < i->size; n++) {
                canvas->FillRectangle(x, y, w, h, {100, 250, 100, 255});
                canvas->DrawRectangle(x, y, w, h, 2, {50, 50, 240, 255});
                char number[5];
                int len = snprintf(number, 5, "%d", n + i->start_index);
                auto dimension = font.GetTextDimensions(number);
                canvas->DrawText(((w - dimension.x) >> 1) + x, y + c_y, number, len, font, {255, 255, 255, 255});
                if (i->orientation)
                    y += h;
                else
                    x += w;
            }
        }
    }
    ~MyWin() {
        for (auto i : login_page.GetChildren()) delete i;

        for (auto i : reg_page.GetChildren()) delete i;
        for (auto i : reg2_page.GetChildren()) delete i;
    }
};
int main(int argc, char* args[]) {
    SDL_Color col{255, 255, 255, 255};
    MyWin win(0, 0, 1200, 760, "Hello", col);
    win.Start();
    SDL_Quit();
    return 0;
}
