#ifndef SG_SPRITES_TIP_H_
#define SG_SPRITES_TIP_H_

#include "engine/sprite.h"
#include "engine/timer.h"

class Tip : public Sprite {
public:
    Tip(ParentPtr parent, const SDLTexturePtr &texture,
            int cx, int cy, int cw, int ch, int interval)
            : Sprite(parent, texture, cx, cy, cw, ch), interval_(interval) {
        set_visible(false);
    }

    void Render(const SDLRendererPtr &renderer) override {
        if (visible()) {
            Sprite::Render(renderer);
            if (timer_.CheckInterval(interval_)) {
                set_visible(false);
            }
        }
    }

    void ShowTip() {
        set_visible(true);
        timer_.Restart();
    }

private:
    Timer timer_;
    int interval_;
};

#endif // SG_SPRITES_TIP_H_
