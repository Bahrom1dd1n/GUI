
#include "ScrollBox.h"

ScrollBox::ScrollBox(Window* win, int x, int y, int w, int visible_items, Font& font)
    : Canvas(win, x, y, w, visible_items * (font.GetLetterHeight() + 2 * padding)),
      font(font),
      visible_items(visible_items),
      item_height(font.GetLetterHeight() + 2 * padding) {
    color = {255, 255, 255, 255};
    Canvas::Clear(color);
    changed = true;
}

void ScrollBox::AddItem(const std::string& item) {
    this->changed = true;
    items.push_back(item);
}

void ScrollBox::MouseDown(const Event& event) {
    this->changed = true;
    int y = event.button.y - rect.y;
    selected_index = start_index + (y + scroll_offset) / item_height;

    if (selected_index < 0 || selected_index >= items.size()) {
        selected_index = -1;
        return;
    }
    if (selection_callback) {
        selection_callback(selected_index, event.button.button);
    }
}

void ScrollBox::ScrollUp() {
    this->changed = true;
    if (scroll_offset > 0) {
        scroll_offset -= 5;
        return;
    }
    if (start_index) {
        start_index--;
        scroll_offset = item_height - 1;
    }
}

void ScrollBox::ScrollDown() {
    this->changed = true;
    if (scroll_offset < item_height) {
        scroll_offset += 5;
        return;
    }
    if (start_index < items.size() - visible_items) {
        start_index++;
        scroll_offset = 0;
    }
}

void ScrollBox::MouseWheel(const Event& event) {
    if (event.wheel.y > 0) {
        ScrollUp();
    } else if (event.wheel.y < 0) {
        ScrollDown();
    }
}

void ScrollBox::Draw() {
    Canvas::Draw();
    if (!changed) return;
    Canvas::Clear({255, 255, 255, 255});
    if (selected_index > -1) {
        Canvas::FillRectangle(0, (selected_index - start_index) * item_height - this->scroll_offset, rect.w,
                              item_height, this->select_color);
    }
    for (int i = 0; i < visible_items && i + start_index < items.size(); i++) {
        Canvas::DrawRectangle(0, i * item_height - scroll_offset, rect.w, item_height, 1, {0, 0, 0, 255});
        char* txt = items[i + start_index].data();
        int size = items[i + start_index].size();
        auto d = font.GetTextDimensions(txt);
        Canvas::DrawText((rect.w - d.x) >> 1, i * item_height - this->scroll_offset, txt, size, font, this->text_color);
    }
    changed = false;
}

ScrollBox::~ScrollBox() {
}
