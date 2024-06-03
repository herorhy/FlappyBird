#ifndef SG_SPRITES_BULLET_H_
#define SG_SPRITES_BULLET_H_

#include "engine/sprite.h"

#include "gamedef.h"

class Bullet : public Sprite {
public:
    Bullet(ParentPtr parent, const SDLTexturePtr &texture,
            int cx, int cy, int cw, int ch, int speed)
            : Sprite(parent, texture, cx, cy, cw, ch), speed_(speed) {}

    void Render(const SDLRendererPtr &renderer) override {
        set_y(y() + speed_);
        if (y() > kAreaHeight) {
            parent()->RemoveObject(this);
            return;
        }
        Sprite::Render(renderer);
    }

    bool IsCollide(Sprite *sprite) override {
        if (Sprite::IsCollide(sprite)) {
            parent()->RemoveObject(this);
            return true;
        }
        else {
            return false;
        }
    }

private:
    int speed_;
};

#endif // SG_SPRITES_BULLET_H_
