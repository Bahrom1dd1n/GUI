#ifndef __IMAGE__
#define __IMAGE__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "Element.h"

class Image : public Element {
   protected:
    struct ImageInfo {
        SDL_Texture* texture = nullptr;
        uint32_t link_count = 0;
    };
    SDL_Rect rect = {0, 0, 0, 0};
    ImageInfo* img_info = nullptr;  // information about texture, SDL_Texture , how many references to it
    double angle = 0;

   public:
    Image() = default;
    Image(const Image& t);
    Image(Image&& t) noexcept;
    Image(const char* path);
    Image(SDL_Texture* texture);
    Image& operator=(const Image& t);

    void Load(const char* path);

    void Draw(const SDL_Rect* src_rect = NULL) const;

    inline int GetHeight() const { return this->rect.h; }

    inline int GetWidth() const { return this->rect.w; }

    void Draw() override;
    // return true if this element contains point of given coordinates
    bool ContainPoint(int x, int y) override;
    // behavior of gui elemnt when it's been pressed
    void Click() override;
    // focuse to current gui element (when mouse clicked on it or some specific event is happened)
    void Focuse() override;
    // unfocuses gui element
    void Unfocuse() override;
    // behavior of gui element when when specific key is pressed
    void KeyPress(uint32_t key) override;
    // behavior of gui element when when typed
    void Type(char) override;
    // behavior of gui element when mouse enters area of gui element
    void Hover() override;
    // behavior of gui element when mouse goes out of it's area
    void UnHover() override;

    ~Image();
};

#endif  // !__IMAGE__
