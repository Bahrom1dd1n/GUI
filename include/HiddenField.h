#ifndef __HIDDENFIELD__
#define __HIDDENFIELD__
#include "Element.h"
#include "Image.h"
#include "TextField.h"
class HiddenField : public TextField {
   private:
    static Image global_img;
    Image eye;
    bool hidden = true;
    SDL_Rect eye_src;

   public:
    HiddenField() = default;
    HiddenField(Window* win, int x, int y, uint32_t length, Font& font,
                const SDL_Color& bg_color = {255, 255, 255, 255});
    void Init(Window* win, int x, int y, uint32_t length, Font& font, const SDL_Color& bg_color = {255, 255, 255, 255});
    inline void SetX(int x) {
        eye.SetX(eye.GetX() + x - rect.x);
        rect.x = x;
    }
    inline void SetY(int y) {
        eye.SetY(eye.GetY() + y - rect.y);
        rect.y = y;
    }
    inline void SetPosition(int x, int y) {
        this->SetY(y);
        this->SetX(x);
    }
    void Draw() override;
    Element* ContainPoint(int x, int y) override;
    void MouseDown(const Event& event) override;
};
#endif  // !__HIDDENFIELD__
