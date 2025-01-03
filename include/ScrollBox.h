// ScrollBox.h
#ifndef __SCROLLBOX__
#define __SCROLLBOX__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "Canvas.h"
#include "Element.h"
#include "Font.h"
#include "Image.h"
#include "Window.h"

class ScrollBox : public Canvas {
   private:
    int scroll_offset = 0;
    int start_index = 0;
    int visible_items = 0;
    int item_height = 20;
    int selected_index = -1;

    Font font;

    bool changed = false;
    const static int padding = 2;

   public:
    std::vector<std::string> items;
    std::function<void(int, int)> selection_callback;
    SDL_Color select_color = {200, 43, 43, 255};
    SDL_Color text_color{0, 0, 0, 255};

    ScrollBox(Window* win, int x, int y, int w, int visible_items, Font& font);
    void AddItem(const std::string& item);
    void MouseDown(const Event& event) override;
    void ScrollUp();
    void ScrollDown();
    void MouseWheel(const Event& event) override;
    void Draw() override;
    void SelectItem(int index) {
        if (index >= items.size() || index < 0) return;
        this->selected_index = index;
        this->changed = true;
    }
    void RemoveItem(int index) {
        if (index >= items.size() || index < 0) return;
        this->items.erase(items.begin() + index);
        this->changed = true;
    }
    void Unselect() {
        this->selected_index = -1;
        changed = true;
    }
    ~ScrollBox() override;
};

#endif  // __SCROLLBOX__
