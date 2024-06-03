#ifndef SG_ENGINE_RESMAN_H_
#define SG_ENGINE_RESMAN_H_

#include <string>
#include <map>
#include <SDL_mixer.h>
#include "sdltype.h"
#include"engine/textsprite.h"

//using TextSpritePtr = std::shared_ptr<TextSprite>;
class ResManager {
public:
    ResManager(const SDLRendererPtr &renderer) : renderer_(renderer) {}//���캯��
    //ResManager(const SDLRendererPtr& renderer, const TextSpritePtr& textsprite) :renderer_(renderer), color_({255,255,255,255}) { textsprite_ = textsprite; };//��Ҫ����������ʱ���õĹ��캯��
    void LoadImage(const std::string &name,const std::string &path);           //����ͼƬ
    SDLTexturePtr &GetImage(const std::string &name) {                              //��ȡӳ����Ϣ
        return images_[name];
    }
    TTF_Font*& GetFont(const std::string& name) {//��ȡ������Ϣ
        return fonts_[name];
    }
    const SDLRendererPtr& GetRenderer() {
        return renderer_;
    }
    Mix_Music*&  GetMusic(const std::string& name) {
        return music_[name];
    }
    Mix_Chunk*& GetChunk(const std::string& name) {
        return chunks_[name];
    }

    void LoadFont(const std::string& name,  const std::string& path,int size=10);//��������
    void LoadBackGroundMusic(const string&name ,const string& path);
    void LoadSound(const string& name, const string& path);

    void LoadImages();                                                                                     // �������ͼƬ
    void LoadFonts();
    void LoadBACKGroundMusics();
    void LoadSounds();
    //void LoadFonts();

private:
    const SDLRendererPtr &renderer_;                                                            //����һ����Ⱦ��������Ⱦ�������ٽ��иĶ�
    std::map<std::string, SDLTexturePtr> images_;   //����һ�������������ӳ��
    std::map<std::string,TTF_Font*>fonts_; 
    std::map<std::string, Mix_Music*>music_;
    std::map<std::string, Mix_Chunk*>chunks_;

    //TextSpritePtr textsprite_;
    SDL_Color color_;
};

#endif // SG_ENGINE_RESMAN_H_