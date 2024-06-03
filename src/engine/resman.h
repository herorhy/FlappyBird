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
    ResManager(const SDLRendererPtr &renderer) : renderer_(renderer) {}//构造函数
    //ResManager(const SDLRendererPtr& renderer, const TextSpritePtr& textsprite) :renderer_(renderer), color_({255,255,255,255}) { textsprite_ = textsprite; };//需要加入文字类时调用的构造函数
    void LoadImage(const std::string &name,const std::string &path);           //载入图片
    SDLTexturePtr &GetImage(const std::string &name) {                              //获取映射信息
        return images_[name];
    }
    TTF_Font*& GetFont(const std::string& name) {//获取字体信息
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

    void LoadFont(const std::string& name,  const std::string& path,int size=10);//导入字体
    void LoadBackGroundMusic(const string&name ,const string& path);
    void LoadSound(const string& name, const string& path);

    void LoadImages();                                                                                     // 导入多张图片
    void LoadFonts();
    void LoadBACKGroundMusics();
    void LoadSounds();
    //void LoadFonts();

private:
    const SDLRendererPtr &renderer_;                                                            //创建一个渲染器，该渲染器不可再进行改动
    std::map<std::string, SDLTexturePtr> images_;   //创建一个名字与纹理的映射
    std::map<std::string,TTF_Font*>fonts_; 
    std::map<std::string, Mix_Music*>music_;
    std::map<std::string, Mix_Chunk*>chunks_;

    //TextSpritePtr textsprite_;
    SDL_Color color_;
};

#endif // SG_ENGINE_RESMAN_H_