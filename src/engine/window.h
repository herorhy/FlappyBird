#ifndef SG_ENGINE_WINDOW_H_
#define SG_ENGINE_WINDOW_H_

#include <string>
#include <mutex>
#include <cstdint>
#include<gamedef.h>
#include "sdltype.h"
#include "spriteman.h"
#include "resman.h"

class Window {
public:
    Window(const std::string &title, int width = Init_WIDTH, int height = Init_HEIGHT)
            : title_(title), width_(width), height_(height),
              handle_events_(true), quit_flag_(false), paused_(0),
              window_(nullptr, nullptr), renderer_(nullptr, nullptr) {
        NewInstance();
        Initialize();
    }

    virtual ~Window() {
        renderer_.release();
        window_.release();
        ReleaseInstance();
    }

    // public methods
    void Render();
    void MainLoop();

    void Quit();
    ResManager CreateResManager() { return ResManager(renderer_); }//创建一个ResManager类的对象

    // setters
    void set_title(const std::string &title) {
        title_ = title;
        SDL_SetWindowTitle(window_.get(), title_.c_str());
    }
    void set_scene(const ScenePtr &scene) { scene_ = scene; }//设置场景
    void set_paused(bool paused) { paused_ = paused; }//设置游戏是否暂停
    // getters
    const std::string &title() const { return title_; }
    int width() const { return width_; }
    int height() const { return height_; }
    const ScenePtr &scene() const { return scene_; }

    bool get_pause() { return paused_; }

protected:
    // event handlers

    // program events
    virtual void QuitEvent() {}
    // window events
    virtual void MinimizedEvent() {}
    virtual void RestoredEvent() {}
    virtual void MouseEnterEvent() {}
    virtual void MouseLeaveEvent() {}
    virtual void GotFocusEvent() {}
    virtual void LostFocusEvent() {}
    virtual void ClosedEvent() {}
    // keyboard events
    virtual void KeyDownEvent(uint32_t keycode) {}
    virtual void KeyUpEvent(uint32_t keycode) {}
    // mouse events
    virtual void MouseMoveEvent(uint32_t state,
            uint32_t x, uint32_t y, int32_t rx, int32_t ry) {}
    virtual void MouseDownEvent(uint8_t button, uint8_t state,
            uint8_t clicks, int32_t x, int32_t y) {}
    virtual void MouseUpEvent(uint8_t button, uint8_t state,
            uint8_t clicks, int32_t x, int32_t y) {}
    virtual void MouseWhellEvent(int32_t x, int32_t y,
            uint32_t direction) {}
    // other events
    virtual void CustomEvent(const SDL_Event &event) {}

    // other functions
    virtual void BeforeRender(const SDLRendererPtr &renderer) {}
    virtual void AfterRender(const SDLRendererPtr &renderer) {}

    void set_handle_events(bool enabled) { handle_events_ = enabled; }

private:
    // ref-counted instance control
    static void NewInstance();
    static void ReleaseInstance();

    // SDL window & renderer initializer
    // NOTE: make sure this function will only be called in constructor
    void Initialize();

    // event handling
    void EventDispatch(const SDL_Event &event);
    
    // shared instance counter
    static int instance_counter_;
    static std::mutex instance_mutex_;
    // properties
    std::string title_;
    const int width_, height_;
    bool handle_events_, quit_flag_, paused_;
    // other private variables
    SDLWindowPtr window_;//窗口界面，一个程序只能有这一个
    SDLRendererPtr renderer_;//渲染器，一个程序只能有这一个
    ScenePtr scene_;
    SDLDisplayMPtr mode_;
};

using WindowPtr = std::shared_ptr<Window>;

#endif // SG_ENGINE_WINDOW_H_
