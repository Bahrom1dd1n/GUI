#include "Frame.h"
void Frame::Draw() {
    for (auto i : children) {
        i->Draw();
    }
}
// return true if this element contains point of given coordinates
bool Frame::ContainPoint(int x, int y) {
    for (auto i : children) {
        if (i->ContainPoint(x, y)) {
            this->may_focused = i;
            return true;
        };
    }
    return false;
};
// behavior of gui elemnt when it's has been clicked by mouse
void Frame::MouseDown(const Event& event) {
    if (this->focused) this->focused->MouseDown(event);
}
// behavior of gui element when key is pressed while it was focused
void Frame::KeyDown(const Event& event) {
    if (this->focused) this->focused->KeyDown(event);
}
// focuse to current gui element (when mouse clicked on it or some specific event is happened)
void Frame::Focuse() {
    this->focused = may_focused;
    this->focused->Focuse();
}
// unfocuses gui element
void Frame::Unfocuse() {
    this->focused->Unfocuse();
    this->focused = nullptr;
}
