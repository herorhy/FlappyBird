#include "sprite.h"

#include <stdexcept>

#include "logger.h"
#include "window.h"
extern double Magnification_Times;

void Sprite::InitTextureInfo() {//��ʼ��texture_
    if (!texture_) {
        Logger::LogError("Sprite::InitTextureInfo");
        throw std::runtime_error("texture pointer cannot be null");
    }
    int w, h;
    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &w, &h);//��ѯ��ǰ����Ŀ�͸�
    if (is_clipped_) {//�����Ҫ��������͸���Ϊ�������
        if (clip_.x + clip_.w > w || clip_.y + clip_.h > h) {
            Logger::LogError("Sprite::InitTextureInfo");
            throw std::runtime_error("invalid clip arguments");
        }
        width_ = clip_.w;
        height_ = clip_.h;
    }
    else {//�������Ҫ��ֱ�Ӹ�ֵ
        width_ = w;
        height_ = h;
    }
    bounding_ = {0, 0, width_, height_};
}

void Sprite::Render(const SDLRendererPtr &renderer) {//�������Ƶ���Ⱦ����
    if (visible_) {//��ǰ��������ǿɼ��ģ��������Ƶ���Ⱦ��
        //����Ⱦ���ϵ�������ݰ������ı�
        SDL_Rect dest = {x_*Magnification_Times, y_ * Magnification_Times, width_* Magnification_Times, height_* Magnification_Times };
        SDL_RenderCopy(renderer.get(), texture_.get(), src_ptr(), &dest);
    }
}

bool Sprite::IsCollide(Sprite *sprite) {//�ж��Ƿ�����ײ
    if (!visible_) return false;//
    auto h_dist = SDL_abs(x_ + bounding_.x -
            (sprite->x_ + sprite->bounding_.x));
    auto v_dist = SDL_abs(y_ + bounding_.y -
            (sprite->y_ + sprite->bounding_.y));
    auto half_w = (bounding_.w + sprite->bounding_.w) / 2;
    auto half_h = (bounding_.h + sprite->bounding_.h) / 2;
    return h_dist < half_w && v_dist < half_h;
}
