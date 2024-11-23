
/*
 header file of Text graphical object
*/

#ifndef __TEXT__
#define __TEXT__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <iostream>

#include "Element.h"
#include "Font.h"
#include "Texture.h"
#include "Window.h"

class Text : public Element {
   private:
    SDL_FRect rect;
    SDL_Renderer* ren = nullptr;
    std::string text;
    Texture text_texture;
    Font font;
    Element* parent = nullptr;

   public:
    inline Text(Window* win, int x, int y, const std::string& text, const Font& font);
    inline void SetX(int x);
    inline void SetY(int y);
    inline void SetPosition(int x, int y);
    inline uint32_t GetWidth() const;
    inline uint32_t GetHeight() const;
    inline const std::string& GetText() const;
    void Draw() override;
    void Click() override;
    void Focuse() override;
    void Unfocuse() override;
    void Hover() override;
    void UnHover() override;
    void KeyPress(uint32_t key) override;
    void Type(char) override;
    bool ContainPoint(int x, int y) override;
    ~Text();
};

#endif  // !__TEXT__
