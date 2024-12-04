#ifndef __IMAGE__
#define __IMAGE__

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cmath>
#include <cstdint>

#include "Element.h"
#include "Window.h"
class Image : public Element {
   protected:
    struct ImageInfo {
        SDL_Texture* texture = nullptr;
        uint32_t link_count = 0;
        uint32_t original_width = 0;
        uint32_t original_height = 0;
    };
    SDL_Rect rect = {0, 0, 0, 0};
    ImageInfo* img_info = nullptr;  // information about texture, SDL_Texture , how many references to it
    double angle = 0;
    float cos_a = 1.0f;
    float sin_a = 0.0f;
    Image(int x, int y, SDL_Renderer* ren, SDL_Texture* texture);

   public:
    Image() = default;
    Image(const Image& t);
    Image(Image&& t) noexcept;
    Image(Window* win, int x, int y, const char* path);
    Image& operator=(const Image& t);
    void Init(Window* win, int x, int y, const char* path);
    void Load(const char* path, Window* win = nullptr);
    void Scale(double ratio) {
        this->rect.w = this->img_info->original_width * ratio;
        this->rect.h = this->img_info->original_height * ratio;
    }

    void DrawPart(const SDL_Rect* src_rect = NULL) const;

    inline void RotateTo(const double angle) {
        this->angle = angle;
        this->cos_a = std::cos(angle);
        this->sin_a = std::sin(angle);
    }
    inline int GetHeight() const { return this->rect.h; }
    inline int GetWidth() const { return this->rect.w; }
    inline int GetX() const { return this->rect.x; }
    inline int GetY() const { return this->rect.y; }

    inline void SetWidth(int width) { this->rect.w = width; }
    inline void SetHeight(int height) { this->rect.h = height; }
    inline void SetX(const int x) { this->rect.x = x; }
    inline void SetY(const int y) { this->rect.y = y; }
    inline void SetPosition(const int x, const int y) {
        this->rect.x = x;
        this->rect.y = y;
    }

    void Draw() override;
    // return true if this element contains point of given coordinates
    Element* ContainPoint(int x, int y) override;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    void Focuse() override;
    // unfocuses gui element
    void Unfocuse() override;
    // Behavior of Image element whene Mouse is clicked on it
    void MouseDown(const Event& event) override;
    // behavior of gui element when when specific key is pressed
    void KeyDown(const Event& event) override;
    // behavior of gui element when when typed
    ~Image();
    friend class Font;
};

#endif  // !__IMAGE__
