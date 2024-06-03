#ifndef SG_ENGINE_TYPE_H_
#define SG_ENGINE_TYPE_H_

#include <memory>

#include <SDL.h>

using SDLWindowPtr =
        //创建SDL_Window指针，和删除指针的函数void SDL_DestroyWindow(SDL_Window*win)
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using SDLRendererPtr =
        //创建SDL_Renderer指针，和删除指针的函数void SDL_DestroyRenderer(SDL_Renderer*ren)
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
using SDLSurfacePtr =
        //创建SDL_Surface指针，和删除指针的函数void SDL_FreeSurface(SDLSurface*sur)
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
using SDLTexturePtr = std::shared_ptr<SDL_Texture>;//令SDLTexturePtr托管一个SDL_Texture指针
using SDLDisplayMPtr = std::shared_ptr<SDL_DisplayMode>;
#endif // SG_ENGINE_TYPE_H_
