#ifndef __GUIELEMENT__
#define __GUIELEMENT__
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

#include <cstdint>
#include <functional>

typedef SDL_Event Event;
class Element {
   protected:
    SDL_Renderer* renderer = nullptr;
    bool visible = true;

   public:
    inline bool IsVisible() const { return this->visible; };
    inline void SetVisible(bool visible) { this->visible = visible; };
    // drawing gui element on to the parent window
    virtual void Draw() = 0;
    // returns Element under point
    virtual Element* ContainPoint(int x, int y) = 0;
    // behavior of gui elemnt when it's has been clicked by mouse
    virtual void MouseDown(const Event& e) = 0;
    // behavior of gui element when key is pressed while it was focused
    virtual void KeyDown(const Event& e) = 0;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    virtual void Focuse() = 0;
    // unfocuses gui element
    virtual void Unfocuse() = 0;
    virtual ~Element() = 0;
};
inline Element::~Element() {};
#endif  // !__SHARED_TEXTRE__
