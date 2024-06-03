#include "spriteman.h"

void SpriteManager::Render(const SDLRendererPtr &renderer) {
    SDL_RenderClear(renderer.get());//刷新界面
    for (auto &&s : sprites_) {//for循环处理可变长数组sprites_对每一个元素处理对应的精灵类的渲染器
        for (auto it = s.begin(); it != s.end(); ) {
            it->second.first->Render(renderer);
            if (!it->second.second) {//清除不需要的元素
                it = s.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    SDL_RenderPresent(renderer.get());//显示渲染器
}

void SpriteManager::RemoveObject(void *id) {
    for (auto &&s : sprites_) {
        for (auto &&i : s) {
            if (i.second.first.get() == id) {
                i.second.second = false;
                return;
            }
        }
    }
}
