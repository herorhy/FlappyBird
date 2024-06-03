#include "number.h"

#include <cctype>
extern double  Magnification_Times ;
void Number::Render(const SDLRendererPtr &renderer) {
    if (!visible()) return;
    uint32_t cur_num = number_;
    SDL_Rect src = {0, clip().y, clip().w, clip().h};
    //按比例来设置输出矩形的坐标和宽高
    SDL_Rect dest = {0, y()*Magnification_Times, clip().w * Magnification_Times, clip().h * Magnification_Times };

    for (int i = width() -  clip().w; i >= 0; i -= clip().w) {
        src.x = clip().x + (cur_num % 10) * clip().w;
        dest.x = (x() + i)* Magnification_Times;//设置输出矩形的横坐标
        SDL_RenderCopy(renderer.get(), texture().get(), &src, &dest);
        cur_num /= 10;
    }
}
