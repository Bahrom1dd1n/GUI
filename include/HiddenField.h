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
    void Draw() override;
    Element* ContainPoint(int x, int y) override;
    void MouseDown(const Event& event) override;
};
#endif  // !__HIDDENFIELD__
