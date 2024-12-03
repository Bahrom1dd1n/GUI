#ifndef __FRAME__
#define __FRAME__

#include <vector>

#include "Element.h"
class Frame : public Element {
   private:
    std::vector<Element*> children;
    Element* focused = nullptr;
    Element* may_focused = nullptr;

   public:
    Frame() = default;
    inline void Add(Element* element) { this->children.push_back(element); };
    inline const std::vector<Element*>& GetChildren() const { return this->children; }
    void Draw() override;
    // return true if this element contains point of given coordinates
    bool ContainPoint(int x, int y) override;
    // behavior of gui elemnt when it's has been clicked by mouse
    void MouseDown(const Event& e) override;
    // behavior of gui element when key is pressed while it was focused
    void KeyDown(const Event& e) override;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    void Focuse() override;
    // unfocuses gui element
    void Unfocuse() override;
};

#endif  // !__FRAME__
