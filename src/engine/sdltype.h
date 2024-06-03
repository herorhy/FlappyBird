#ifndef SG_ENGINE_TYPE_H_
#define SG_ENGINE_TYPE_H_

#include <memory>

#include <SDL.h>

using SDLWindowPtr =
        //����SDL_Windowָ�룬��ɾ��ָ��ĺ���void SDL_DestroyWindow(SDL_Window*win)
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using SDLRendererPtr =
        //����SDL_Rendererָ�룬��ɾ��ָ��ĺ���void SDL_DestroyRenderer(SDL_Renderer*ren)
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
using SDLSurfacePtr =
        //����SDL_Surfaceָ�룬��ɾ��ָ��ĺ���void SDL_FreeSurface(SDLSurface*sur)
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
using SDLTexturePtr = std::shared_ptr<SDL_Texture>;//��SDLTexturePtr�й�һ��SDL_Textureָ��
using SDLDisplayMPtr = std::shared_ptr<SDL_DisplayMode>;
#endif // SG_ENGINE_TYPE_H_
