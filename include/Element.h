#ifndef __GUIELEMENT__
#define __GUIELEMENT__
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <functional>
class Element {
   protected:
    SDL_Renderer* renderer = nullptr;
    bool visible = true;

   public:
    std::function<void(int x, int y)> click_callback;
    std::function<void(uint32_t key)> keypress_callback;
    inline bool IsVisible() const { return this->visible; };
    inline void SetVisible(bool visible) { this->visible = visible; };
    // drawing gui element on to the parent window
    virtual void Draw() = 0;
    // return true if this element contains point of given coordinates
    virtual bool ContainPoint(int x, int y) = 0;
    // behavior of gui elemnt when it's been pressed
    virtual void Click() = 0;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    virtual void Focuse() = 0;
    // unfocuses gui element
    virtual void Unfocuse() = 0;
    // behavior of gui element when when specific key is pressed
    virtual void KeyPress(uint32_t key) = 0;
    // behavior of gui element when when typed
    virtual void Type(char) = 0;
    // behavior of gui element when mouse enters area of gui element
};
#endif  // !__SHARED_TEXTRE__
