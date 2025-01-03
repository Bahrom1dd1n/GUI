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
#include "Image.h"
class Window {
   protected:
    static int open_sessions;
    SDL_Rect window_rect;
    uint32_t frame_delay = 0;   // stricting frame rate using delay in main loop
    uint32_t time_elapsed = 0;  // last time interval taken in main loop
    uint64_t current_time = 0;  // last time window was Rendered ( in main loop )

    SDL_Renderer* main_ren = nullptr;
    SDL_Window* window = nullptr;
    Uint32 windowID = 0;
    SDL_Color bg_cl = {255, 255, 255, 255};  // background color
    std::vector<Element*> children;          // list of children which will be drawn on Window
    Element* focused_element = nullptr;      // focused element , focused by mouse click or some event
    Element* hovered_element = nullptr;      // element which mouse is moving over
    Image bg_img;

    bool running = false;  // condition of main loop of Window
    void OnMouseDown(const Event& event);
    void MouseWheel(const Event& event);
    void OnKeyUp(const Event& event);
    // void OnMouseMove(const Event& event);

    void OnKeyDown(const Event& event);

   public:
    std::function<void(int x, int y, int mb)> mousedown_callback;  // mouse click event handler
    std::function<void(uint32_t key)> keydown_callback;            //
    std::function<void()> draw_frame_callback;
    std::function<void(uint32_t key)> keyup_callback;
    Window(uint32_t x, uint32_t y, uint32_t window_width, uint32_t window_height, const std::string& title,
           const SDL_Color& background_cl = {255, 255, 255, 255}, int flags = SDL_WINDOW_SHOWN, uint32_t max_fps = 0);

    inline bool IsRunning() const { return this->running; };
    inline void SetBackground(const Image& img) { this->bg_img = img; };
    inline int GetWidth() const { return window_rect.w; }
    inline int GetHeight() const { return window_rect.h; }
    inline int GetCenterX() const { return window_rect.w >> 1; }
    inline int GetCenterY() const { return window_rect.h >> 1; }
    void Start();
    void Stop();
    void Add(Element* elem);
    SDL_Renderer* GetRenderer() { return this->main_ren; }
    ~Window();

    friend class Button;
    friend class Text;
    friend class Font;
    friend class Image;
    friend class TextField;
    friend class HiddenField;
    friend class Rectangle;
    friend class Canvas;
};
#endif  //!__WINDOW__
