#include "resman.h"

#include <stdexcept>
#include <SDL_image.h>

#include "logger.h"

void ResManager::LoadImage(const std::string &name,
        const std::string &path) {
    auto image = SDLTexturePtr(
        IMG_LoadTexture(renderer_.get()/*ȡ��render_�йܵ�ָ��SDL_Renderer* */, path.c_str()/*��ȡͼƬ·��*/),//��ͼƬ�����뵽��Ⱦ��render_��
        [](SDL_Texture *texture) { SDL_DestroyTexture(texture); }/*������һ��Lambda���ʽ����ʹ���κ��ⲿ����������ΪSDL_Texture *texture����ֵ�ǿգ������ʽ������SDL_DestroyTexture(texture)����*/
    );
    if (!image) {
        //���û�гɹ�����ͷ��ش�����Ϣ
        Logger::LogError("ResManager::LoadImage");
        throw std::runtime_error("failed to load image");//�׳�runtime_error���쳣������ͼƬ��ʧ��
    }
    images_[name] = image;//����һ��ӳ���ϵ��key��ͼƬ���֣�value��SDL_Textureָ��
}

void ResManager::LoadFont(const std::string& name,  const std::string& path,int size) {//��������

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

    //�ж��Ƿ���ɹ�
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

    //�ж��Ƿ���ɹ�
    //
    if (!chunk) {
        Logger::LogError("ResManager::LoadSound : Fail to load chunk"+name);
        return;
    }

    chunks_[name] = chunk;
}
