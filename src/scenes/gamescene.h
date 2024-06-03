#ifndef SG_SCENES_GAMESCENE_H_
#define SG_SCENES_GAMESCENE_H_

#include <memory>

#include "gamedef.h"
#include "engine/spriteman.h"

class GameSceneInterface {
public:
    virtual ~GameSceneInterface() = default;
    virtual void Reset() = 0;                                       //重新设置
    //帧运行框架
    virtual void FrameBegin(KeyStatus key, MouseStatus mouse) {
        OnKeyDown(key);//处理键盘事件
        OnMouseClickAndMove(mouse);//处理鼠标事件
        CollisionHandle();//处理碰撞事件
        GameRun();//处理其它事件
    }

    virtual const ScenePtr& GetScene() const = 0;   //获取当前场景的指针

    virtual void OnKeyDown(KeyStatus key) = 0;      //键盘事件处理
    virtual void OnMouseClickAndMove(MouseStatus mouse) = 0;//鼠标事件处理
    virtual void CollisionHandle() = 0;//碰撞处理
    virtual void GameRun() = 0; //游戏中自主变化的事件，比如敌机自由下落

protected:
    //const SDLRendererPtr& renderer_;
};

using GameScenePtr = std::shared_ptr<GameSceneInterface>;//让GameScenePtr成为GameSceneInterface类的指针

#endif // SG_SCENES_GAMESCENE_H_
