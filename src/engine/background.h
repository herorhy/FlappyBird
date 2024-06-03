#ifndef SG_ENGINE_BACKGROUND_H_
#define SG_ENGINE_BACKGROUND_H_

#include "sprite.h"

class Background : public Sprite {
public:
    enum class Arrange : char {
        Tile, Stretch, Fill
    };

    Background(ParentPtr parent,
            const SDLTexturePtr &texture, Arrange arrange)
            : Sprite(parent, texture), arrange_(arrange) {}
    Background(ParentPtr parent, const SDLTexturePtr &texture,
            int cx, int cy, int cw, int ch, Arrange arrange)
            : Sprite(parent, texture, cx, cy, cw, ch), arrange_(arrange) {}

    void Render(const SDLRendererPtr &renderer) override;

private:
    Arrange arrange_;
};

#endif // SG_ENGINE_BACKGROUND_H_
