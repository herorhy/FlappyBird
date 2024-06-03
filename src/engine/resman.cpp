#include "resman.h"

#include <stdexcept>
#include <SDL_image.h>

#include "logger.h"

void ResManager::LoadImage(const std::string &name,
        const std::string &path) {
    auto image = SDLTexturePtr(
        IMG_LoadTexture(renderer_.get()/*取得render_托管的指针SDL_Renderer* */, path.c_str()/*获取图片路径*/),//将图片纹理导入到渲染器render_中
        [](SDL_Texture *texture) { SDL_DestroyTexture(texture); }/*这里是一个Lambda表达式，不使用任何外部变量，参数为SDL_Texture *texture返回值是空，语句体式调用了SDL_DestroyTexture(texture)函数*/
    );
    if (!image) {
        //如果没有成功导入就返回错误信息
        Logger::LogError("ResManager::LoadImage");
        throw std::runtime_error("failed to load image");//抛出runtime_error的异常：载入图片是失败
    }
    images_[name] = image;//建立一个映射关系，key是图片名字，value是SDL_Texture指针
}

void ResManager::LoadFont(const std::string& name,  const std::string& path,int size) {//导入字体

    TTF_Font* font_ = TTF_OpenFont(path.c_str(), size);
    if (!font_) {
            Logger::LogError("ResManager::LoadFonts");
            throw std::runtime_error("failed to load font");
            return;
    }
    fonts_[name] = font_;
}

void ResManager::LoadBackGroundMusic(const string& name, const string& path)
{
    Mix_Music* music = Mix_LoadMUS(path.c_str());

    //判断是否导入成功
    //
    if (!music) {
        Logger::LogError("ResManager::LoadBackGroundMusic: Fail to Load"+name);
        return;
    }
    music_[name] = music;
}

void ResManager::LoadSound(const string& name, const string& path)
{
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());

    //判断是否导入成功
    //
    if (!chunk) {
        Logger::LogError("ResManager::LoadSound : Fail to load chunk"+name);
        return;
    }

    chunks_[name] = chunk;
}
