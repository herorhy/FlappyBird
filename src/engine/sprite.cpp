#include "sprite.h"

#include <stdexcept>

#include "logger.h"
#include "window.h"
extern double Magnification_Times;

void Sprite::InitTextureInfo() {//初始化texture_
    if (!texture_) {
        Logger::LogError("Sprite::InitTextureInfo");
        throw std::runtime_error("texture pointer cannot be null");
    }
    int w, h;
    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &w, &h);//查询当前纹理的宽和高
    if (is_clipped_) {//如果需要剪除将宽和高设为剪除后的
        if (clip_.x + clip_.w > w || clip_.y + clip_.h > h) {
            Logger::LogError("Sprite::InitTextureInfo");
            throw std::runtime_error("invalid clip arguments");
        }
        width_ = clip_.w;
        height_ = clip_.h;
    }
    else {//如果不需要，直接赋值
        width_ = w;
        height_ = h;
    }
    bounding_ = {0, 0, width_, height_};
}

void Sprite::Render(const SDLRendererPtr &renderer) {//将纹理复制到渲染器上
    if (visible_) {//当前纹理如果是可见的，将它复制到渲染器
        //将渲染器上的输出内容按比例改变
        SDL_Rect dest = {x_*Magnification_Times, y_ * Magnification_Times, width_* Magnification_Times, height_* Magnification_Times };
        SDL_RenderCopy(renderer.get(), texture_.get(), src_ptr(), &dest);
    }
}

bool Sprite::IsCollide(Sprite *sprite) {//判断是否发生碰撞
    if (!visible_) return false;//
    auto h_dist = SDL_abs(x_ + bounding_.x -
            (sprite->x_ + sprite->bounding_.x));
    auto v_dist = SDL_abs(y_ + bounding_.y -
            (sprite->y_ + sprite->bounding_.y));
    auto half_w = (bounding_.w + sprite->bounding_.w) / 2;
    auto half_h = (bounding_.h + sprite->bounding_.h) / 2;
    return h_dist < half_w && v_dist < half_h;
}
