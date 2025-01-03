#ifndef __FRAME__
#define __FRAME__

#include <vector>

#include "Element.h"
class Frame : public Element {
   private:
    std::vector<Element*> children;
    Element* focused = nullptr;

   public:
    Frame() = default;
    inline void Add(Element* element) { this->children.push_back(element); };
    inline void RemoveChild(int index) {
        if (index >= this->children.size()) return;
        this->children.erase(this->children.begin() + index);
    }
    inline void RemoveLastChild() { this->children.pop_back(); }
    inline std::vector<Element*>& GetChildren() { return this->children; }
    void Draw() override;
    // return true if this element contains point of given coordinates
    Element* ContainPoint(int x, int y) override;
    // behavior of gui elemnt when it's has been clicked by mouse
    void MouseDown(const Event& e) override;
    // behavior of gui element when key is pressed while it was focused
    void KeyDown(const Event& e) override;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    void Focuse() override;
    // unfocuses gui element
    void Unfocuse() override;
    inline ~Frame() override {};
};

#endif  // !__FRAME__
