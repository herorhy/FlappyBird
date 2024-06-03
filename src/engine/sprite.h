#ifndef SG_ENGINE_SPRITE_H_
#define SG_ENGINE_SPRITE_H_

#include <memory>

#include "sdltype.h"
#include "parent.h"
#include"gamedef.h"
class Sprite;
using SpritePtr = std::shared_ptr<Sprite>;//让SpritePtr成为一个Sprite类的指针

class Sprite {
public:

    Sprite(ParentPtr parent)
            : parent_(parent), is_clipped_(false), visible_(false),
              texture_(nullptr), x_(0), y_(0), width_(50), height_(60){}
    Sprite(ParentPtr parent, const SDLTexturePtr &texture)
            : parent_(parent), is_clipped_(false), visible_(true),
              texture_(texture), x_(0), y_(0) {
        InitTextureInfo();
    }
    Sprite(ParentPtr parent, const SDLTexturePtr &texture,
            int cx, int cy, int cw, int ch)
            : parent_(parent), is_clipped_(true), visible_(true),
              clip_({cx, cy, cw, ch}), texture_(texture), x_(0), y_(0) {
        InitTextureInfo();
    }
    Sprite(ParentPtr parent, 
        int cx, int cy, int cw, int ch)
        : parent_(parent), is_clipped_(true), visible_(true),
        clip_({ cx, cy, cw, ch }), x_(0), y_(0) {
        
    }
    virtual ~Sprite() = default;

    virtual void Render(const SDLRendererPtr &renderer);
    virtual bool IsCollide(Sprite *sprite);//是否发生碰撞
    //设置横纵坐标
    void set_x(int x) { x_ = x; }
    void set_y(int y) { y_ = y; }
    //设置图片的宽和高
    void set_width(int width) { width_ = width; }
    void set_height(int height) { height_ = height; }
    //设置图片是否可见
    void set_visible(bool visible) { visible_ = visible; }
    //设置边界.
    void set_bounding(const SDL_Rect &bounding) { bounding_ = bounding; }
    
    //获取信息
    int x() const { return x_; }
    int y() const { return y_; }
    int width() const { return width_; }
    int height() const { return height_; }
    bool visible() const { return visible_; }
    const SDL_Rect &bounding() const { return bounding_; }


protected:
    ParentPtr parent() const { return parent_; }
    bool is_clipped() const { return is_clipped_; }
    const SDL_Rect &clip() const { return clip_; }
    const SDLTexturePtr &texture() const { return texture_; }
    const SDL_Rect *src_ptr() const {//判断是否要进行剪除
        return is_clipped_ ? &clip_ : nullptr;
    }
    //将下面内容改为protected类型，为了派生类方便使用
    void InitTextureInfo();
    SDLTexturePtr texture_;
    ParentPtr parent_;
    bool is_clipped_, visible_;
    SDL_Rect clip_, bounding_, range_;
    //SDL_Surface* surface_;
    int x_, y_, width_, height_;
private:
    
    
};

#endif // SG_ENGINE_SPRITE_H_
