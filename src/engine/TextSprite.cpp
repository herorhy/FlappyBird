#include"textsprite.h"
#include<memory>
#include<string>
using namespace std;
extern double Magnification_Times;

void TextSprite::set_color(Uint8 R, Uint8 G, Uint8 B, Uint8 A)
{
	color_ = { R,G,B,A };//设置字体颜色
	SDL_GetTextureColorMod(texture_.get(), &R, &G, &B);
}
void TextSprite::set_size(int size) {
	changeSize_ = size / size_;
	size_ = size;
}
void TextSprite::Render(const SDLRendererPtr& renderer) 
{
	
	if (visible_) {//当前纹理如果是可见的，将它复制到渲染器
	   //将渲染器上的输出内容按比例改变,这里的比例包括显示器的比例和字体大小的比例。
		
		
		SDL_Rect dest = { x_ * Magnification_Times* changeSize_, y_ * Magnification_Times*changeSize_, width_ * Magnification_Times* changeSize_, height_ * Magnification_Times* changeSize_ };
		SDL_RenderCopy(renderer.get(), texture_.get(), src_ptr(), &dest);
	}
}
//三个构造函数用来初始化
TextSprite::TextSprite(ParentPtr parent, const SDLRendererPtr& renderer,TTF_Font* font)
	:Sprite(parent), font_(font),renderer_(renderer){
	//CreatTextTure();
}
TextSprite::TextSprite(ParentPtr parent, const SDLRendererPtr& renderer, TTF_Font* font, string msg,int size)
	:Sprite(parent), msg_(msg),size_(size), changeSize_(1.0), font_(font), renderer_(renderer) {
	this->set_color(0, 0, 0, 255);
	CreatTextTure();
	int length = msg_.size();
	this->set_width(width_ * length);
	
	//InitTextureInfo();
}
TextSprite::TextSprite(ParentPtr parent, const SDLRendererPtr& renderer, TTF_Font* font
	, string msg, int cx, int cy, int cw, int ch, int size)
	:Sprite(parent, cx, cy, cw, ch), msg_(msg), size_(size),changeSize_(1.0), font_(font), renderer_(renderer) {

	CreatTextTure();
	int length = msg_.size();
	this->set_width(width_ * length);
	this->set_color(255, 255, 255, 255);
	//InitTextureInfo();

}
void TextSprite::CreatTextTure() {

	SDL_Surface*  surface_ = TTF_RenderText_Blended(font_, msg_.c_str(), color_);//创建表面
	if (!surface_) {
		Logger::LogError("TextSprite::CreatSurface");
	}
	texture_= SDLTexturePtr(
	    SDL_CreateTextureFromSurface(renderer_.get(), surface_),
	    [](SDL_Texture* texture) { SDL_DestroyTexture(texture);}
	);//将表面转化成纹理
	if (!texture_) {
		    Logger::LogError("TextSprite::CreatTextTure");
		    throw std::runtime_error("failed to load font");
			return;
	}
	SDL_FreeSurface(surface_);//释放临时的表面

}
//void TextSprite::HandleVisible(KeyStatus key) {
//    if (!key_Pressed_ && key) {
//		if (key & kKey_Enter){
//			set_visible(0);
//        }
//		else if (key & kKey_Space) {
//			set_visible(1);
//		}
//        key_Pressed_ = true;
//    }
//    if (key_Pressed_ && !key) {
//        key_Pressed_ = false;
//    }
//}