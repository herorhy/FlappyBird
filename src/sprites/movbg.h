#ifndef SG_SPRITES_MOVBG_H_
#define SG_SPRITES_MOVBG_H_

#include "engine/sprite.h"

#include "gamedef.h"

class MovingBg : public Sprite {
public:
    MovingBg(ParentPtr parent,
        const SDLTexturePtr& texture, float speed)
        : Sprite(parent, texture), speed_(speed), sub_pos_(kWinWidth) {}

    void Render(const SDLRendererPtr& renderer) override {
        sub_pos_ += speed_;
        if (sub_pos_ <= 0) {
            sub_pos_ = kWinWidth;
        }
        set_x(sub_pos_);
        Sprite::Render(renderer);
        set_x(sub_pos_ - kWinWidth);
        Sprite::Render(renderer);
    }

private:
    float speed_, sub_pos_;
};

#endif // SG_SPRITES_MOVBG_H_
