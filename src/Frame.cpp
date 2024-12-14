#include "Frame.h"

#include "Element.h"
void Frame::Draw() {
    for (auto i : children) {
        i->Draw();
    }
}
// return true if this element contains point of given coordinates
Element* Frame::ContainPoint(int x, int y) {
    for (auto it = children.rbegin(); it != children.rend(); it++) {
        if ((*it)->IsVisible() && (*it)->ContainPoint(x, y)) {
            return *it;
        };
    }
    return nullptr;
};
// behavior of gui elemnt when it's has been clicked by mouse
void Frame::MouseDown(const Event& event) {
}
// behavior of gui element when key is pressed while it was focused
void Frame::KeyDown(const Event& event) {
}
// focuse to current gui element (when mouse clicked on it or some specific event is happened)
void Frame::Focuse() {
}
// unfocuses gui element
void Frame::Unfocuse() {
}
