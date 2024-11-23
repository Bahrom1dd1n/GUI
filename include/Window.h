#ifndef __WINDOW__
#define __WINDOW__
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
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
    void OnMouseDown(int x, int y);

    void OnMouseMove(int x, int y);

    inline void OnTyped(char letter);
    inline void OnKeyDown(uint32_t key);

   public:
    Window(uint32_t x, uint32_t y, uint32_t window_width, uint32_t window_height, const std::string& title,
           const SDL_Color& background_cl, uint32_t max_fps = 0);

    bool IsRunning() const;
    void Start();
    void Stop();
    ~Window();

    friend class Button;
    friend class Text;
};

#endif  //!__WINDOW__
