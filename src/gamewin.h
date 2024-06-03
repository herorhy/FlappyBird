#ifndef SG_GAMEWIN_H_
#define SG_GAMEWIN_H_

#include "engine/window.h"

#include "gamedef.h"
#include "sceneman.h"
#include<iostream>
class GameWindow : public Window {
public:
    GameWindow() : Window("Flappy Bird"), sceneman_(this), key_(0) {
        set_handle_events(false);
    }

    SceneManager& sceneman() { return sceneman_; }

protected:
    void BeforeRender(const SDLRendererPtr& renderer) override {

        //捕获键盘信息
        GetKeyCode();
        //捕获鼠标信息
        GetMouseCode();
        //通知当前场景
        sceneman_.FrameBegin(key_, mouse_);
    }

    void GetKeyCode() {

        //捕获键盘信息
        const uint8_t* state = SDL_GetKeyboardState(nullptr);


        //将键盘信息存入key_
        key_ = 0;
        if (state[SDL_SCANCODE_A]) key_ |= kKey_A;
        if (state[SDL_SCANCODE_B]) key_ |= kKey_B;
        if (state[SDL_SCANCODE_C]) key_ |= kKey_C;
        if (state[SDL_SCANCODE_D]) key_ |= kKey_D;
        if (state[SDL_SCANCODE_E]) key_ |= kKey_E;
        if (state[SDL_SCANCODE_F]) key_ |= kKey_F;
        if (state[SDL_SCANCODE_G]) key_ |= kKey_G;
        if (state[SDL_SCANCODE_H]) key_ |= kKey_H;
        if (state[SDL_SCANCODE_I]) key_ |= kKey_I;
        if (state[SDL_SCANCODE_J]) key_ |= kKey_J;
        if (state[SDL_SCANCODE_K]) key_ |= kKey_K;
        if (state[SDL_SCANCODE_L]) key_ |= kKey_L;
        if (state[SDL_SCANCODE_M]) key_ |= kKey_M;
        if (state[SDL_SCANCODE_N]) key_ |= kKey_N;
        if (state[SDL_SCANCODE_O]) key_ |= kKey_O;
        if (state[SDL_SCANCODE_P]) key_ |= kKey_P;
        if (state[SDL_SCANCODE_Q]) key_ |= kKey_Q;
        if (state[SDL_SCANCODE_R]) key_ |= kKey_R;
        if (state[SDL_SCANCODE_S]) key_ |= kKey_S;
        if (state[SDL_SCANCODE_T]) key_ |= kKey_T;
        if (state[SDL_SCANCODE_U]) key_ |= kKey_U;
        if (state[SDL_SCANCODE_V]) key_ |= kKey_V;
        if (state[SDL_SCANCODE_W]) key_ |= kKey_W;
        if (state[SDL_SCANCODE_X]) key_ |= kKey_X;
        if (state[SDL_SCANCODE_Y]) key_ |= kKey_Y;
        if (state[SDL_SCANCODE_Z]) key_ |= kKey_Z;

        if (state[SDL_SCANCODE_0])key_ |= kKey_0;
        if (state[SDL_SCANCODE_1])key_ |= kKey_1;
        if (state[SDL_SCANCODE_2])key_ |= kKey_2;
        if (state[SDL_SCANCODE_3])key_ |= kKey_3;
        if (state[SDL_SCANCODE_4])key_ |= kKey_4;
        if (state[SDL_SCANCODE_5])key_ |= kKey_5;
        if (state[SDL_SCANCODE_6])key_ |= kKey_6;
        if (state[SDL_SCANCODE_7])key_ |= kKey_7;
        if (state[SDL_SCANCODE_8])key_ |= kKey_8;
        if (state[SDL_SCANCODE_9])key_ |= kKey_9;

        if (state[SDL_SCANCODE_F1])key_ |= kKey_F1;
        if (state[SDL_SCANCODE_F2])key_ |= kKey_F2;
        if (state[SDL_SCANCODE_F3])key_ |= kKey_F3;
        if (state[SDL_SCANCODE_F4])key_ |= kKey_F4;
        if (state[SDL_SCANCODE_F5])key_ |= kKey_F5;
        if (state[SDL_SCANCODE_F6])key_ |= kKey_F6;
        if (state[SDL_SCANCODE_F7])key_ |= kKey_F7;
        if (state[SDL_SCANCODE_F8])key_ |= kKey_F8;
        if (state[SDL_SCANCODE_F9])key_ |= kKey_F9;
        if (state[SDL_SCANCODE_F10])key_ |= kKey_F10;
        if (state[SDL_SCANCODE_F11])key_ |= kKey_F11;
        if (state[SDL_SCANCODE_F12])key_ |= kKey_F12;

        if (state[SDL_SCANCODE_RIGHT])    key_ |= kKey_Right;
        if (state[SDL_SCANCODE_LEFT])       key_ |= kKey_Left;
        if (state[SDL_SCANCODE_UP])           key_ |= kKey_Up;
        if (state[SDL_SCANCODE_DOWN])    key_ |= kKey_Down;

        if (state[SDL_SCANCODE_RETURN]) key_ |= kKey_Enter;
        if (state[SDL_SCANCODE_ESCAPE])  key_ |= kKey_Esc;
        if (state[SDL_SCANCODE_TAB]) key_ |= kKey_Tab;
        if (state[SDL_SCANCODE_SPACE]) key_ |= kKey_Space;

    }
    void GetMouseCode() {
        mouse_.Status = SDL_GetMouseState(&mouse_.x, &mouse_.y);
    }
private:
    SceneManager sceneman_;
    KeyStatus key_;
    MouseStatus mouse_;
};

#endif // SG_GAMEWIN_H_
