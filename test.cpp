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
    std::vector<Image> bg_images;  // background images
    Frame login_page;              // login page
    Frame reg_page;                //
    Frame reg2_page;               //
    Frame floors_page;             // page of floors and
    Frame pay_page;                // payment page
    Frame paydetail_page;
    Frame checkout_page;

    Font font;
    Font header1;
    Font header2;
    Image ret_img;
    // information about selected slot and building
    // elemensts of login page
    struct {
        TextField* username = nullptr;
        HiddenField* password = nullptr;
    } login_var;

    // elements of register page
    struct {
        TextField* username = nullptr;
        HiddenField* password = nullptr;
        TextField* name = nullptr;
        TextField* plate_num = nullptr;
        TextField* vehicle_type = nullptr;
        TextField* addres = nullptr;
        TextField* phone_number = nullptr;
        TextField* email = nullptr;
    } reg_var;
    struct {
        Canvas* canvas = nullptr;
        Chart chart;
        // map of the building
        SDL_Rect selected_rect = {0, 0, 0, 0};
        int selected_floor = 0, selected_block = 0, selected_slot = 0;  // index of selected
        int current_floor = 0;
        int cell = 0;
        bool slot_selected = false;  // slot selected or not
    } floor_var;

   public:
    MyWin(int x, int y, int width, int height, const std::string& title, const SDL_Color& col)
        : Window(x, y, width, height, "My Window", col, 40,
                 SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS) {
        this->font.Init("./Font2.ttf", 18, FontStyle::NORMAL);
        this->header1.Init("./Font2.ttf", 25, FontStyle::BOLD);
        this->header2.Init("./Font2.ttf", 20, FontStyle::BOLD);
        ret_img.Init(this, 0, 0, "./assets/images/return.png");
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
        this->InitPayDetailsPage();
        this->InitCheckoutPage();
        login_page.SetVisible(true);
        reg_page.SetVisible(false);
        reg2_page.SetVisible(false);
        pay_page.SetVisible(false);
        floors_page.SetVisible(false);
        checkout_page.SetVisible(false);
        paydetail_page.SetVisible(false);
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
        login_var.password = password;
        login_var.username = field;

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

        Button* ret = new Button(this, 10, 10, 40, 30, ret_img);
        ret->click_callback = [&](int, int) {
            login_page.SetVisible(true);
            reg_page.SetVisible(false);
            this->SetBackground(bg_images[0]);
        };

        // but.OnClick = MyWin::Print();
        reg_page.Add(ret);
        reg_page.Add(rect_frame);
        reg_page.Add(txt);
        reg_page.Add(field);
        reg_page.Add(password);
        reg_page.Add(password2);
        reg_page.Add(but);

        reg_var.username = field;
        reg_var.password = password;

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
        std::string placehoders[] = {"Enter full name",    "Enter plate number", "Enter vehicle type",
                                     "Enter your address", "Enter phone number", "Enter email addres"};
        TextField** fields[] = {&reg_var.name,   &reg_var.plate_num,    &reg_var.vehicle_type,
                                &reg_var.addres, &reg_var.phone_number, &reg_var.email};
        for (int i = 0; i < 6; i++) {
            field = new TextField(this, 0, field->GetY() + field->GetHeight() + 20, 30, font, {255, 255, 255, 255});
            field->SetCenterX(center);
            field->SetPlaceholder(placehoders[i]);
            *fields[i] = field;
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

        Button* ret = new Button(this, 10, 10, 40, 30, ret_img);
        ret->click_callback = [&](int, int) {
            reg2_page.SetVisible(false);
            reg_page.SetVisible(true);
            this->SetBackground(bg_images[1]);
        };
        // but.OnClick = MyWin::Print();
        reg2_page.Add(ret);
        reg2_page.Add(txt);
        reg2_page.Add(but);

        this->Add(&reg2_page);
    }

    void InitFloors() {
        floor_var.chart.Load("chart.dat");
        Canvas* canvas = MakeCanvas(this->GetWidth() - 200, this->GetHeight(), floor_var.chart);
        if ((this->GetWidth() - canvas->GetWidth()) >> 1 > 200)
            canvas->SetCenterX(this->GetCenterX());
        else
            canvas->SetX(this->GetWidth() - canvas->GetWidth());
        canvas->SetCenterY(this->GetCenterY());
        DrawChart(canvas, floor_var.chart, 0);
        canvas->SetBorderWidth(8);
        canvas->SetBorderColor({10, 100, 100, 255});
        canvas->click_callback = [this](int x, int y) { SelectSlot(x, y); };

        for (int i = 0, y = (this->GetHeight() - floor_var.chart.floors.size() * 100 + 50) >> 1;
             i < floor_var.chart.floors.size(); i++, y += 100) {
            char name[10] = {0};
            snprintf(name, 10, "Level %d", i + 1);
            Button* but = new Button(this, 25, y, 150, 50, name, font, {255, 165, 0, 255});
            but->click_callback = [this, i, canvas](int, int) {
                if (i == floor_var.current_floor) return;
                DrawChart(canvas, floor_var.chart, i);
                floor_var.slot_selected = false;
                floor_var.current_floor = i;
            };

            floors_page.Add(but);
        };
        Button* choose = new Button(this, 25, this->GetHeight() - 70, 120, 50, "Select", font, {220, 20, 20, 255});
        choose->click_callback = [this](int x, int y) {
            floors_page.SetVisible(false);
            paydetail_page.SetVisible(true);
            this->SetBackground(bg_images[3]);
        };

        Button* ret = new Button(this, 10, 10, 40, 30, ret_img);
        ret->click_callback = [&](int, int) {
            reg2_page.SetVisible(true);
            floors_page.SetVisible(false);
            this->SetBackground(bg_images[2]);
        };
        floors_page.Add(ret);
        floors_page.Add(choose);
        floors_page.Add(canvas);
        floor_var.canvas = canvas;
        this->Add(&floors_page);
    }

    void SelectSlot(int x, int y) {
        int cell = floor_var.cell;
        if (floor_var.slot_selected && floor_var.current_floor == floor_var.selected_floor) {
            auto& r = floor_var.selected_rect;
            floor_var.canvas->FillRectangle(r.x, r.y, r.w, r.h, {100, 250, 100, 255});
            floor_var.canvas->DrawRectangle(r.x, r.y, r.w, r.h, 2, {50, 50, 240, 255});
            char number[5];
            auto sp = floor_var.chart.floors[floor_var.selected_floor]->at(floor_var.selected_block);
            int len = snprintf(number, 5, "%d", sp->start_index + floor_var.selected_slot);
            auto dimension = font.GetTextDimensions(number);
            floor_var.canvas->DrawText(((r.w - dimension.x) >> 1) + r.x, r.y + ((r.h - dimension.y) >> 1), number, len,
                                       font, {255, 255, 255, 255});
        }
        floor_var.slot_selected = false;
        int n = 0;

        for (auto i : *floor_var.chart.floors[floor_var.current_floor]) {
            n++;
            int w, h;
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
            int left = i->y * cell;
            int right = left + h;
            if (y < left) continue;
            if (y > right) continue;
            left = i->x * cell;
            right = left + i->size * w;
            if (x < left) continue;
            if (x > right) continue;

            // it is shure that blockof slot has been clicked
            floor_var.selected_floor = floor_var.current_floor;
            floor_var.selected_block = n - 1;
            std::cout << "x = " << x << "\nleft = " << left << "\nw = " << w << std::endl;
            floor_var.selected_slot = (x - left) / w;
            floor_var.slot_selected = true;
            right = i->x * cell + floor_var.selected_slot * w;

            floor_var.selected_rect = {right, i->y * cell, w, h};

            break;
        }

        if (floor_var.slot_selected) {
            auto& r = floor_var.selected_rect;
            floor_var.canvas->FillRectangle(r.x, r.y, r.w, r.h, {50, 250, 250, 255});
            floor_var.canvas->DrawRectangle(r.x, r.y, r.w, r.h, 2, {50, 50, 240, 255});
            char number[5];
            auto sp = floor_var.chart.floors[floor_var.selected_floor]->at(floor_var.selected_block);
            int len = snprintf(number, 5, "%d", sp->start_index + floor_var.selected_slot);
            auto dimension = font.GetTextDimensions(number);
            floor_var.canvas->DrawText(((r.w - dimension.x) >> 1) + r.x, r.y + ((r.h - dimension.y) >> 1), number, len,
                                       font, {255, 255, 255, 255});
        }
    }

    void InitPayPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 350, {20, 20, 230, 255});
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Payment Details", header1, {255, 255, 255, 255});
        HiddenField* card_num =
            new HiddenField(this, 0, txt->GetY() + txt->GetHeight() + 20, 16, font, {255, 255, 255, 255});
        card_num->SetPlaceholder("Enter Card number");
        card_num->SetMaxTextLength(16);
        TextField* exp_date =
            new TextField(this, 0, card_num->GetY() + card_num->GetHeight() + 30, 5, font, {255, 255, 255, 255});
        exp_date->SetPlaceholder("mm/yy");
        TextField* cvv =
            new TextField(this, 0, card_num->GetY() + card_num->GetHeight() + 30, 3, font, {255, 255, 255, 255});
        cvv->SetPlaceholder("cvv");
        cvv->SetMaxTextLength(3);
        Button* but = new Button(this, 0, rect_frame->GetY() + rect_frame->GetHeight() - 60, 100, 30, "Pay", font,
                                 {200, 20, 20, 255});

        int center = this->GetWidth() >> 1;
        rect_frame->SetCenterX(center);
        txt->SetCenterX(center);

        card_num->SetCenterX(center);
        exp_date->SetX(card_num->GetX());
        cvv->SetX(card_num->GetX() + card_num->GetWidth() - cvv->GetWidth());
        card_num->SetPlaceholder("Enter card number");
        but->SetCenterX(center);

        but->click_callback = [this](int x, int y) {
            pay_page.SetVisible(false);
            checkout_page.SetVisible(true);
            this->SetBackground(bg_images[0]);
        };

        Button* ret = new Button(this, 10, 10, 40, 30, ret_img);
        ret->click_callback = [&](int, int) {
            pay_page.SetVisible(false);
            paydetail_page.SetVisible(true);
            this->SetBackground(bg_images[3]);
        };

        // but.OnClick = MyWin::Print();
        pay_page.Add(ret);
        pay_page.Add(rect_frame);
        pay_page.Add(txt);
        pay_page.Add(card_num);
        pay_page.Add(but);
        pay_page.Add(exp_date);
        pay_page.Add(cvv);
        this->Add(&pay_page);
    }
    void InitPayDetailsPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 450, {20, 20, 230, 255});
        rect_frame->SetCenterX(this->GetCenterX());
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        paydetail_page.Add(rect_frame);
        // drawing "Payment details text"
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Payment Details", header1, {255, 255, 255, 255});
        txt->SetCenterX(rect_frame->GetCenterX());
        paydetail_page.Add(txt);
        // drawing time spent
        txt = new Text(this, 0, txt->GetY() + txt->GetHeight() + 20, "Time spent details", font, {255, 255, 255, 255});
        Text* time_details = new Text(this, 0, txt->GetY() + txt->GetHeight() + 10, "1:12:20", font);
        Rectangle* rect = new Rectangle(this, 0, time_details->GetY() - 8, rect_frame->GetWidth() - 40,
                                        time_details->GetHeight() + 16, {255, 255, 255, 255});
        rect->SetCenterX(rect_frame->GetCenterX());
        time_details->SetCenterX(rect_frame->GetCenterX());
        txt->SetCenterX(rect_frame->GetCenterX());
        paydetail_page.Add(rect);
        paydetail_page.Add(txt);
        // drawing floor details
        txt = new Text(this, 0, rect->GetY() + rect->GetHeight() + 20, "Floor details", font, {255, 255, 255, 255});
        Text* floor_details = new Text(this, 0, txt->GetY() + txt->GetHeight() + 10, "floor 1, index 24", font);
        rect = new Rectangle(this, 0, floor_details->GetY() - 8, rect_frame->GetWidth() - 40,
                             floor_details->GetHeight() + 16, {255, 255, 255, 255});
        rect->SetCenterX(rect_frame->GetCenterX());
        floor_details->SetCenterX(rect_frame->GetCenterX());
        txt->SetCenterX(rect_frame->GetCenterX());
        paydetail_page.Add(rect);
        paydetail_page.Add(txt);
        // drawing pay amount
        txt = new Text(this, 0, rect->GetY() + rect->GetHeight() + 20, "Payment amount", font, {255, 255, 255, 255});
        Text* payment = new Text(this, 0, txt->GetY() + txt->GetHeight() + 10, "$200", font);
        rect = new Rectangle(this, 0, payment->GetY() - 8, rect_frame->GetWidth() - 40, payment->GetHeight() + 16,
                             {255, 255, 255, 255});
        rect->SetCenterX(rect_frame->GetCenterX());
        payment->SetCenterX(rect_frame->GetCenterX());
        txt->SetCenterX(rect_frame->GetCenterX());
        paydetail_page.Add(rect);
        paydetail_page.Add(txt);

        Button* but = new Button(this, 0, rect_frame->GetY() + rect_frame->GetHeight() - 60, 100, 30, "Continue", font,
                                 {200, 20, 20, 255});
        but->SetCenterX(rect_frame->GetCenterX());
        paydetail_page.Add(but);

        but->click_callback = [this](int x, int y) {
            paydetail_page.SetVisible(false);
            pay_page.SetVisible(true);
            this->SetBackground(bg_images[3]);
        };

        Button* ret = new Button(this, 10, 10, 40, 30, ret_img);
        ret->click_callback = [&](int, int) {
            floors_page.SetVisible(true);
            paydetail_page.SetVisible(false);
            this->SetBackground(bg_images[3]);
        };

        // but.OnClick = MyWin::Print();
        paydetail_page.Add(ret);
        paydetail_page.Add(time_details);
        paydetail_page.Add(floor_details);
        paydetail_page.Add(payment);
        this->Add(&paydetail_page);
    }
    void InitCheckoutPage() {
        Rectangle* rect_frame = new Rectangle(this, 0, 0, 300, 450, {20, 20, 230, 255});
        rect_frame->SetCenterX(this->GetCenterX());
        rect_frame->SetCenterY(this->GetHeight() >> 1);
        checkout_page.Add(rect_frame);
        // drawing "Payment details text"
        Text* txt = new Text(this, 0, rect_frame->GetY() + 30, "Checkout", header1, {255, 255, 255, 255});
        txt->SetCenterX(rect_frame->GetCenterX());
        checkout_page.Add(txt);

        txt = new Text(this, rect_frame->GetX() + 20, txt->GetY() + txt->GetHeight() + 20, "Payment method", header2,
                       {255, 255, 255, 255});
        checkout_page.Add(txt);
        txt = new Text(this, rect_frame->GetX() + 20, txt->GetY() + txt->GetHeight() + 20, "Visa", font);
        checkout_page.Add(txt);
        Text* card_num =
            new Text(this, rect_frame->GetX() + 20, txt->GetY() + txt->GetHeight() + 10, "**** **** **** 1234", font);
        Rectangle* rect = new Rectangle(this, rect_frame->GetX() + 5, txt->GetY() - 8, card_num->GetWidth() + 10,
                                        card_num->GetHeight() + txt->GetHeight() + 15, {255, 255, 255, 255});
        checkout_page.Add(rect);
        rect->SetX(card_num->GetX() - 5);
        checkout_page.Add(txt);

        // drawing time spent
        txt = new Text(this, rect_frame->GetX() + 20, rect->GetY() + rect->GetHeight() + 20, "Payment", header2,
                       {255, 255, 255, 255});
        checkout_page.Add(txt);
        txt = new Text(this, rect_frame->GetX() + 30, txt->GetY() + txt->GetHeight() + 20, "Time spent", font,
                       {255, 255, 255, 255});
        checkout_page.Add(txt);
        Text* time_details = new Text(this, 0, txt->GetY(), "1:12:20", font);
        time_details->SetX(rect_frame->GetX() + rect_frame->GetWidth() - time_details->GetWidth() - 20);
        rect = new Rectangle(this, 0, time_details->GetY() - 8, rect_frame->GetWidth() - 40,
                             time_details->GetHeight() + 16, {255, 255, 255, 255});

        // drawing paymand amount
        txt = new Text(this, rect_frame->GetX() + 20, rect->GetY() + rect->GetHeight() + 20, "Payment amount", font,
                       {255, 255, 255, 255});
        checkout_page.Add(txt);
        Text* payment = new Text(this, time_details->GetX(), txt->GetY(), "$200", font);

        Button* but = new Button(this, 0, rect_frame->GetY() + rect_frame->GetHeight() - 60, 100, 30, "Checkout", font,
                                 {200, 20, 20, 255});
        but->SetCenterX(rect_frame->GetCenterX());
        checkout_page.Add(but);

        but->click_callback = [this](int x, int y) {
            checkout_page.SetVisible(false);
            floors_page.SetVisible(true);
            this->SetBackground(bg_images[3]);
        };

        Button* ret = new Button(this, 10, 10, 40, 30, ret_img);
        ret->click_callback = [&](int, int) {
            checkout_page.SetVisible(false);
            floors_page.SetVisible(true);
            this->SetBackground(bg_images[1]);
        };

        // but.OnClick = MyWin::Print();
        checkout_page.Add(ret);
        checkout_page.Add(card_num);
        checkout_page.Add(time_details);
        checkout_page.Add(payment);
        this->Add(&checkout_page);
    }
    Canvas* MakeCanvas(int max_width, int max_height, Chart& chart) {
        uint16_t cell_x = max_width / chart.width;
        uint16_t cell_y = max_height / chart.height;
        uint16_t cell = cell_x > cell_y ? cell_y : cell_x;
        floor_var.cell = cell;
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
