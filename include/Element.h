#ifndef __GUIELEMENT__
#define __GUIELEMENT__

#include <cstdint>
class Element {
   private:
   public:
    void (*OnClick)();
    void (*OnTyped)(char);
    void (*OnKeyPressed)(uint32_t key);
    void (*OnHovered)();
    virtual void Draw() {};
    virtual bool ContainPoint(int x, int y) {};
    virtual void Click() {};
    virtual void Focuse() {};
    virtual void Unfocuse() {};
    virtual void KeyPress(uint32_t key) {};
    virtual void Type(char) {};
    virtual void Hover() {};
    virtual void UnHover() {};
};
#endif  // !__SHARED_TEXTRE__
