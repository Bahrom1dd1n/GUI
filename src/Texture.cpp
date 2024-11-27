#include "Texture.h"

#include <iostream>
#include <ostream>
Texture::Texture(SDL_Texture* _texture) {
    this->info = new int[3]{1};
    SDL_QueryTexture(_texture, NULL, NULL, info + 1, info + 2);
    texture = _texture;
}

Texture::Texture(const Texture& t) {
    if (!t.info) return;
    this->texture = t.texture;
    this->info = t.info;
    this->info[0]++;  // another Texture created on top of SDL_Texture* so ,
                      // number of Textures using same SDL_Texture increments by 1
}
Texture::Texture(Texture&& t) noexcept {
    if (!t.info) return;

    this->texture = t.texture;
    this->info = t.info;
    t.info = nullptr;
    t.texture = nullptr;
}
Texture::Texture(const char* path) {
    SDL_Texture* temp = IMG_LoadTexture(main_ren, path);
    if (!temp) {
        std::cerr << "Couldn't load texture\n" << std::endl;
        exit(1);
    }
    printf("Texture Succesfully loaded\n");
    texture = temp;
    info = new int[3]{1};
    SDL_QueryTexture(texture, NULL, NULL, info + 1, info + 2);
}
Texture& Texture::operator=(const Texture& t) {
    if (this->info) {
        if (*this->info > 1)
            this->info[0]--;
        else {
            SDL_DestroyTexture(this->texture);
            delete this->info;
        }
    }

    if (t.info) {
        this->info = t.info;
        this->texture = t.texture;
        this->info[0]++;
    }

    return *this;
}
void Texture::Load(const char* path) {
    SDL_Texture* temp = IMG_LoadTexture(main_ren, path);
    if (!temp) {
        std::cerr << " image with name " << path << " not found" << std::endl;
        exit(1);
    }
    if (this->info) {
        if (*info == 1) {
            SDL_DestroyTexture(this->texture);
        } else {
            info[0]--;
            this->info = new int[3]{1};
        }
    } else
        this->info = new int[3]{1};
    SDL_QueryTexture(temp, NULL, NULL, info + 1, info + 2);
    texture = temp;
}
void Texture::Render(const SDL_FRect* dst_rect, const SDL_Rect* src_rect) const {
    if (!this->info) return;
    SDL_RenderCopyF(main_ren, this->texture, src_rect, dst_rect);
}
void Texture::Render(const SDL_FRect* dst_rect, const float angle, const SDL_FPoint* center,
                     const SDL_Rect* src_rect) const {
    if (!this->info) return;
    SDL_RenderCopyExF(main_ren, this->texture, src_rect, dst_rect, angle, center, SDL_FLIP_NONE);
}

Texture::~Texture() {
    if (this->info) {
        if (*this->info == 1) {
            SDL_DestroyTexture(this->texture);
            delete[] this->info;
            info = nullptr;
            return;
        }
        this->info[0]--;
    }
}
