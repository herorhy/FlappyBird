#include "spriteman.h"

void SpriteManager::Render(const SDLRendererPtr &renderer) {
    SDL_RenderClear(renderer.get());//ˢ�½���
    for (auto &&s : sprites_) {//forѭ������ɱ䳤����sprites_��ÿһ��Ԫ�ش����Ӧ�ľ��������Ⱦ��
        for (auto it = s.begin(); it != s.end(); ) {
            it->second.first->Render(renderer);
            if (!it->second.second) {//�������Ҫ��Ԫ��
                it = s.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    SDL_RenderPresent(renderer.get());//��ʾ��Ⱦ��
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
