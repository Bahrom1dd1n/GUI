#ifndef __POPUP__
#define __POPUP__
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "Button.h"
#include "Element.h"
#include "Font.h"
#include "Image.h"
#include "Text.h"
#include "Window.h"

class PopUp : public Window {
   protected:
    Font header1;
    Font font;
    Button ok;
    Text text;

   public:
    PopUp(const std::string& messages)
        : Window(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, "Warning", {255, 255, 255, 255},
                 SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP, 40),
          header1("./assets/fonts/Font.ttf", 21, FontStyle::BOLD),
          font("./assets/fonts/Font.ttf", 18) {
        text.Init(this, 0, 0, messages, header1, {255, 43, 43, 255});
        text.SetCenterX(this->GetCenterX());
        text.SetCenterY(this->GetCenterY());
        ok.Init(this, 0, 0, 200, 50, "OK", font, {43, 255, 43, 255}, {255, 255, 255, 255});
        ok.SetCenterX(this->GetCenterX());
        ok.SetY(this->GetHeight() - ok.GetHeight() - 50);
        ok.click_callback = [this](int, int, int mb) {
            if (mb == 1) this->Stop();
        };
        this->Add(&ok);
        this->Add(&text);
    };
    void AddMessage(const std::string& messages, const SDL_Color& col) {
        Text* text = new Text(this, 0, 0, messages, header1, col);
        text->SetCenterX(this->GetCenterX());
        text->SetCenterY(this->GetCenterY());
        int w = this->GetHeight() / (this->children.size() + 1);
        this->Add(text);
        for (int i = 0; i < this->children.size(); i++) {
            Rectangle* rec = (Rectangle*)children[i];
            rec->SetCenterY(i * w + w);
        }
    }
    ~PopUp() {
        for (int i = 2; i < this->children.size() + 1; i++) delete children[i];
    }
    void SetBackgroundColor(const SDL_Color& bg_color) { this->bg_cl = bg_color; }
};

#endif  //!__POPUP__
