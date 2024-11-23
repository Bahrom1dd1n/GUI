#ifndef __SHARED_TEXUTRE__
#define __SHARED_TEXUTRE__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <iostream>

extern SDL_Renderer* main_ren;
class Texture {
   private:
    SDL_Texture* texture = nullptr;
    int* info = nullptr;  // information about texture, info[0] = use_count , info[1] = width, info[2] = height

   public:
    inline Texture() = default;

    inline Texture(const Texture& t);
    inline Texture(Texture&& t) noexcept;
    inline Texture(const char* path);
    inline Texture(SDL_Texture* texture);
    inline Texture& operator=(const Texture& t);

    inline void Load(const char* path);

    inline void Render(const SDL_FRect* dst_rect, const SDL_Rect* src_rect = NULL) const;

    inline void Render(const SDL_FRect* dst_rect, const float angle, const SDL_FPoint* center = NULL,
                       const SDL_Rect* src_rect = NULL) const;

    inline int GetHeight() const;

    inline int GetWidth() const;

    inline ~Texture();
};

#endif  // !__SHARED_TEXUTRE__
