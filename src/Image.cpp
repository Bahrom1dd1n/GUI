#include "Image.h"

#include <cstddef>
#include <iostream>
Image::Image(SDL_Texture* _texture) {
    this->rect.x = 0;
    this->rect.y = 0;
    SDL_QueryTexture(_texture, NULL, NULL, &rect.w, &rect.h);
    this->img_info = new ImageInfo{_texture, 1};
}

Image::Image(const Image& t) {
    if (!t.img_info) return;
    this->img_info = t.img_info;
    this->img_info->link_count++;  // another Image created on top of SDL_Texture* so ,
                                   // number of Images using same SDL_Texture increments by 1
}
Image::Image(Image&& t) noexcept {
    if (!t.img_info) return;
    this->img_info = t.img_info;
    delete t.img_info;
    t.img_info = nullptr;
}

Image::Image(const char* path) {
    SDL_Texture* temp = IMG_LoadTexture(this->renderer, path);
    if (!temp) {
        std::cerr << "Couldn't load texture\n" << std::endl;
        exit(1);
    }
    printf("Image Succesfully loaded\n");
    this->rect.x = 0;
    this->rect.y = 0;
    SDL_QueryTexture(temp, NULL, NULL, &rect.w, &rect.h);
    this->img_info = new ImageInfo{temp, 1};
}

Image& Image::operator=(const Image& t) {
    if (this->img_info) {
        this->~Image();
    }
    if (t.img_info) {
        this->img_info = t.img_info;
        this->rect = t.rect;
        this->img_info->link_count++;
    }
    return *this;
}

void Image::Load(const char* path) {
    SDL_Texture* temp = IMG_LoadTexture(this->renderer, path);
    if (!temp) {
        std::cerr << " image with name " << path << " not found" << std::endl;
        exit(1);
    }
    this->~Image();
    this->rect.x = 0;
    this->rect.y = 0;
    SDL_QueryTexture(temp, NULL, NULL, &rect.w, &rect.h);
    this->img_info = new ImageInfo{temp, 1};
}

void Image::Draw(const SDL_Rect* src_rect) const {
    if (!this->img_info) return;
    if (this->angle) {
        SDL_RenderCopyEx(this->renderer, this->img_info->texture, src_rect, &this->rect, this->angle, NULL,
                         SDL_FLIP_NONE);
    } else {
        SDL_RenderCopy(this->renderer, this->img_info->texture, src_rect, &this->rect);
    }
}

Image::~Image() {
    if (this->img_info) {
        if (this->img_info->link_count == 1) {
            SDL_DestroyTexture(this->img_info->texture);
            delete[] this->img_info;
            this->img_info = nullptr;
            return;
        }
        this->img_info->link_count--;
    }
}
