
#include "Image.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>

#include "Element.h"
#include "Window.h"

Image::Image(int x, int y, SDL_Renderer* ren, SDL_Texture* _texture) {
    this->rect.x = x;
    this->rect.y = y;
    this->renderer = ren;
    if (!_texture) return;  // if no texture is provided exit
    SDL_QueryTexture(_texture, NULL, NULL, &rect.w, &rect.h);

    this->img_info = new ImageInfo{_texture, 1, rect.w, rect.h};
}

Image::Image(int x, int y, SDL_Renderer* ren, SDL_Surface* surf) {
    this->rect.x = x;
    this->rect.y = y;
    this->renderer = ren;
    if (!surf) return;  // if no texture is provided exit
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surf);
    this->img_info = new ImageInfo{texture, 1, surf->w, surf->h};
}

Image::Image(const Image& t) {
    if (!t.img_info) return;
    this->img_info = t.img_info;
    this->renderer = t.renderer;
    this->img_info->link_count++;  // another Image created on top of SDL_Texture* so ,
                                   // number of Images using same SDL_Texture increments by 1
}
Image::Image(Image&& t) noexcept {
    if (!t.img_info) return;
    this->img_info = t.img_info;
    this->renderer = t.renderer;
    delete t.img_info;
    t.img_info = nullptr;
}

Image::Image(Window* win, int x, int y, const char* path) {
    this->renderer = win->main_ren;
    SDL_Texture* temp = IMG_LoadTexture(this->renderer, path);
    if (!temp) {
        std::cerr << "Couldn't load texture\n" << std::endl;
        exit(1);
    }
    printf("Image Succesfully loaded\n");
    this->rect.x = x;
    this->rect.y = y;
    SDL_QueryTexture(temp, NULL, NULL, &rect.w, &rect.h);
    this->img_info = new ImageInfo{temp, 1, rect.w, rect.h};
}

Image& Image::operator=(const Image& t) {
    if (this->img_info) {
        this->Destroy();
    }
    if (t.img_info) {
        this->img_info = t.img_info;
        this->renderer = t.renderer;
        this->rect = t.rect;
        this->img_info->link_count++;
    }
    return *this;
}

void Image::Init(Window* win, int x, int y, const char* path) {
    this->renderer = win->main_ren;
    this->Load(path);
    this->rect.x = x;
    this->rect.y = y;
}

void Image::Load(const char* path, Window* win) {
    try {
        if (win) this->renderer = renderer;
        if (!this->renderer) return;
        SDL_Texture* temp = IMG_LoadTexture(this->renderer, path);
        if (!temp) {
            std::cerr << " image with name " << path << " not found" << std::endl;
            exit(1);
        }
        this->Destroy();
        this->rect.x = 0;
        this->rect.y = 0;
        SDL_QueryTexture(temp, NULL, NULL, &rect.w, &rect.h);
        this->img_info = new ImageInfo{temp, 1, rect.w, rect.h};
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

inline void Image::DrawPart(const SDL_Rect* src_rect) const {
    if (!this->img_info) return;
    if (this->angle) {
        SDL_RenderCopyEx(this->renderer, this->img_info->texture, src_rect, &this->rect, this->angle, NULL,
                         SDL_FLIP_NONE);
    } else {
        SDL_RenderCopy(this->renderer, this->img_info->texture, src_rect, &this->rect);
    }
}

void Image::Draw() {
    this->DrawPart(NULL);
};
// return true if this element contains point of given coordinates
Element* Image::ContainPoint(int x, int y) {
    if (this->angle) {
        x = (x - rect.x) * cos_a;
        y = (y - rect.y) * sin_a;

        if (x > rect.w || x < 0) return nullptr;
        if (y > rect.h || y < 0) return nullptr;
        return this;
    }
    if (x < this->rect.x || x > this->rect.x + this->rect.w) return nullptr;
    if (y < this->rect.y || y > this->rect.y + this->rect.h) return nullptr;
    return this;
};
// behavior of gui elemnt when it's been pressed
void Image::Focuse() {

};
// unfocuses gui element
void Image::Unfocuse() {

};
// behavior of gui element when when specific key is pressed
void Image::KeyDown(const Event& event) {};
void Image::MouseDown(const Event& event) {};
inline void Image::Destroy() {
    if (this->img_info) {
        if (this->img_info->link_count == 1) {
            SDL_DestroyTexture(this->img_info->texture);
            delete this->img_info;
            this->img_info = nullptr;
            return;
        }
        this->img_info->link_count--;
    }
}
Image::~Image() {
    this->Destroy();
}
