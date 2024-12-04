#ifndef __WINDOW__
#define __WINDOW__
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

#include "Element.h"

class Window {
   private:
#define _MOUSE_MOVE_DELAY 300  // delay between capturing mouse hovering elevent
    uint32_t window_width = 0;
    uint32_t window_height = 0;
    uint32_t frame_delay = 0;   // stricting frame rate using delay in main loop
    uint32_t time_elapsed = 0;  // last time interval taken in main loop
    uint64_t current_time = 0;  // last time window was Rendered ( in main loop )

    SDL_Renderer* main_ren = nullptr;
    SDL_Window* window = nullptr;
    SDL_Color bg_cl = {0, 0, 0};         // background color
    std::vector<Element*> elements;      // list of elements which will be drawn on Window
    Element* focused_element = nullptr;  // focused element , focused by mouse click or some event
    Element* hovered_element = nullptr;  // element which mouse is moving over
    bool running = false;                // condition of main loop of Window

    std::function<void(int x, int y)> mousedown_callback;
    std::function<void(uint32_t key)> keydown_callback;
    void OnMouseDown(const Event& event);

    // void OnMouseMove(const Event& event);

    void OnKeyDown(const Event& event);

   public:
    Window(uint32_t x, uint32_t y, uint32_t window_width, uint32_t window_height, const std::string& title,
           const SDL_Color& background_cl, uint32_t max_fps = 0);

    inline bool IsRunning() const { return this->running; };
    void Start();
    void Stop();
    void Add(Element* elem);
    ~Window();

    friend class Button;
    friend class Text;
    friend class Font;
    friend class Image;
    friend class TextField;
};

#endif  //!__WINDOW__
