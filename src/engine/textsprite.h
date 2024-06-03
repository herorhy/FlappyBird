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
using TextSpritePtr = std::shared_ptr<TextSprite>;//����һ��TextSprite�Ĺ���ָ��
class TextSprite :public Sprite//�̳�Sprite��
{
public:
	//���ֹ��캯������Ӧ����Sprite�ĳ�ʼ��
	TextSprite(ParentPtr parent, const SDLRendererPtr& renderer,  TTF_Font* font);
	TextSprite(ParentPtr parent, const SDLRendererPtr& renderer,  TTF_Font* font, string msg ,int size =36);
	TextSprite(ParentPtr parent, const SDLRendererPtr& renderer,  TTF_Font* font, string msg,  int cx, int cy, int cw, int ch, int size = 36);
	~TextSprite() { }//���������ͷ�֮ǰ�ı���������
	
	void set_color(Uint8 R, Uint8 G, Uint8 B, Uint8 A);//����������ɫ
	void set_size(int size);//���������С,��ֻ��һ���뷨����û�ҵ�ʵ�ֵİ취��
	
	void Render(const SDLRendererPtr& renderer) override;//���ǻ����render����
	SDL_Color GetColor() { return color_; }//��ȡ��ǰ��ɫ
	int GetSize() { return size_; }//��ȡ��ǰ�����С
	//void HandleVisible(KeyStatus key);//�����ı��Ƿ�ɼ�
private:
	bool key_Pressed_;
protected:
	void CreatTextTure();
	TTF_Font* font_;
	string msg_;	//������Ϣ
	SDL_Color color_;//��ɫ
	//SDL_Surface* surface_;
	const SDLRendererPtr& renderer_;
	int size_;//�����С
	double changeSize_;//�ı������С�ı�����
};

#endif // !_TEXT_SPRITE_H_


