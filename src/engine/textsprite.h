 #ifndef _TEXT_SPRITE_H_
#define _TEXT_SPRITE_H_

#include<iostream>
#include<SDL_ttf.h>
#include<SDL.h>
#include"sprite.h"
//#include"resman.h"
#include"logger.h"
#include<memory>
using namespace std;
class TextSprite;
using TextSpritePtr = std::shared_ptr<TextSprite>;//建立一个TextSprite的共享指针
class TextSprite :public Sprite//继承Sprite类
{
public:
	//三种构造函数，对应三种Sprite的初始化
	TextSprite(ParentPtr parent, const SDLRendererPtr& renderer,  TTF_Font* font);
	TextSprite(ParentPtr parent, const SDLRendererPtr& renderer,  TTF_Font* font, string msg ,int size =36);
	TextSprite(ParentPtr parent, const SDLRendererPtr& renderer,  TTF_Font* font, string msg,  int cx, int cy, int cw, int ch, int size = 36);
	~TextSprite() { }//析构函数释放之前的表面与字体
	
	void set_color(Uint8 R, Uint8 G, Uint8 B, Uint8 A);//设置字体颜色
	void set_size(int size);//设置字体大小,这只是一个想法，还没找到实现的办法。
	
	void Render(const SDLRendererPtr& renderer) override;//覆盖基类的render函数
	SDL_Color GetColor() { return color_; }//获取当前颜色
	int GetSize() { return size_; }//获取当前字体大小
	//void HandleVisible(KeyStatus key);//处理文本是否可见
private:
	bool key_Pressed_;
protected:
	void CreatTextTure();
	TTF_Font* font_;
	string msg_;	//文字信息
	SDL_Color color_;//颜色
	//SDL_Surface* surface_;
	const SDLRendererPtr& renderer_;
	int size_;//字体大小
	double changeSize_;//改变字体大小的比例。
};

#endif // !_TEXT_SPRITE_H_


