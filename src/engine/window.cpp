#include "window.h"

#include <stdexcept>
#include<cmath>
#include "logger.h"
#include<SDL_ttf.h>
int cur_h = Init_HEIGHT;	//当前的界面高度
int cur_w = Init_WIDTH;	//当前的界面宽度
int last_width = Init_WIDTH, last_height = Init_HEIGHT;//上一次的宽高
double Magnification_Times = 1.0;//放大系数，当前窗口大小与初始窗口大小之比
int Window::instance_counter_ = 0;
std::mutex Window::instance_mutex_;
//初始化SDL
void Window::NewInstance() {
    std::lock_guard<std::mutex> lock(instance_mutex_);
    if (!instance_counter_) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            Logger::LogError("Window::NewInstance");
            throw std::runtime_error("failed to initialize window");
        }
        Logger::LogDebug("SDL has been initialized");
        if (TTF_Init() != 0) {//初始化ttf文字
            Logger::LogError("Window::NewInstance");
            throw std::runtime_error("failed to initialize window");
        }
        Logger::LogDebug("TTF has been initialized");
    }
    ++instance_counter_;
    Logger::LogDebug("window created");
}

void Window::ReleaseInstance() {
    Logger::LogDebug("window destroyed");
    std::lock_guard<std::mutex> lock(instance_mutex_);
    --instance_counter_;
    if (!instance_counter_) {
        SDL_Quit();
        TTF_Quit();
        Logger::LogDebug("SDL has been shutdown");
    }
}
//初始化窗口界面
void Window::Initialize() {
    // initialize window
    // TODO: window size!
    window_ = SDLWindowPtr(
        SDL_CreateWindow(title_.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                width_ /2, height_ /2,
                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI),
        SDL_DestroyWindow
    );
    if (window_) {
        // initialize renderer
        renderer_ = SDLRendererPtr(
            SDL_CreateRenderer(window_.get(), -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer
        );
        if (renderer_) return;
    }
    // error occurred
    ReleaseInstance();
    Logger::LogError("Window::Initialize");
    throw std::runtime_error("failed to initialize window");
}
//事件处理函数，以下函数还都还只是空函数
void Window::EventDispatch(const SDL_Event &event) {
    switch (event.type) {
        case SDL_QUIT: QuitEvent(); break;
        case SDL_KEYDOWN: KeyDownEvent(event.key.keysym.sym); break;
        case SDL_KEYUP: KeyUpEvent(event.key.keysym.sym); break;
        case SDL_WINDOWEVENT: {
            switch (event.window.type) {
                case SDL_WINDOWEVENT_MINIMIZED: MinimizedEvent(); break;
                case SDL_WINDOWEVENT_RESTORED: RestoredEvent(); break;
                case SDL_WINDOWEVENT_ENTER: MouseEnterEvent(); break;
                case SDL_WINDOWEVENT_LEAVE: MouseLeaveEvent(); break;
                case SDL_WINDOWEVENT_FOCUS_GAINED: GotFocusEvent(); break;
                case SDL_WINDOWEVENT_FOCUS_LOST: LostFocusEvent(); break;
                case SDL_WINDOWEVENT_CLOSE: ClosedEvent(); break;
                default: CustomEvent(event); break;
            }
            break;
        }
        case SDL_MOUSEMOTION: {
            MouseMoveEvent(event.motion.state,
                    event.motion.x, event.motion.y,
                    event.motion.xrel, event.motion.yrel);
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            MouseDownEvent(event.button.button, event.button.state,
                    event.button.clicks, event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            MouseUpEvent(event.button.button, event.button.state,
                    event.button.clicks, event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEWHEEL: {
            MouseWhellEvent(event.wheel.x, event.wheel.y,
                    event.wheel.direction);
            break;
        }
        default: CustomEvent(event); break;
    }
}

void Window::Render() {//处理渲染器

    if (scene_) scene_->Render(renderer_);
}

void Window::MainLoop() {//游戏主题循环
    while (!quit_flag_) {
        // handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (handle_events_) EventDispatch(event);
            if (event.type == SDL_QUIT) return;
        }
        
        last_height = cur_h;
        last_width = cur_w;
        double proportion;                                                                                                  //比例系数确定初始宽高比值
        proportion = 1.0*Init_WIDTH / Init_HEIGHT;
        SDL_GetWindowSize(window_.get(), &cur_w, &cur_h);                                       //获取当前界面窗口的宽和高
        if (fabs(cur_w - last_width) >=1e-6 || fabs(cur_h - last_height) >= 1e-6) {
            //如果窗口大小发生改变
            if (fabs(1.0 * cur_w / cur_h - 1.0 * Init_WIDTH / Init_HEIGHT) >= 1e-6) {       //如果当前宽比高与默认值不相等
                if (cur_w != last_width) {          //宽度发生改变
                    cur_h = cur_w / proportion; //调整高度的值，让它与宽度的比值与初始比例相等
                }
                if (cur_h != last_height) {         //高度发生改变
                    cur_w = cur_h * proportion;//调整宽度的值，让它与高度的比值与初始比例相等
                }
                SDL_SetWindowSize(window_.get(), cur_w, cur_h);//设置界面新的高和宽
            }
        }
        Magnification_Times = 1.0 * cur_w / Init_WIDTH;//获取新的放大系数

        // render
        BeforeRender(renderer_);
        if (!paused_) Render();
        AfterRender(renderer_);
        // delay
        SDL_Delay(10);
    }
}

void Window::Quit() {
    quit_flag_ = true;
}