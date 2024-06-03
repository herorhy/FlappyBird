#ifndef SG_SCENEMAN_H_
#define SG_SCENEMAN_H_

#include <vector>

#include "engine/window.h"
#include "scenes/gamescene.h"

class SceneManager {
public:
    SceneManager(Window *game) : game_(game), cur_index_(0) {}//构造函数，获得游戏界面窗口

    int AddScene(const GameScenePtr &scene) {//加入一个新场景
        scenes_.push_back(scene);
        return scenes_.size() - 1;
    }

    void FrameBegin(KeyStatus key,MouseStatus mouse) {//当前场景的控制操作
        scenes_[cur_index_]->FrameBegin(key,mouse);
    }

    void QuitGame() { game_->Quit(); }//退出游戏
    void PauseGame(bool is_paused) { game_->set_paused(is_paused); }//游戏暂停
    void RenderGame() { game_->Render(); }
    void SwitchScene(int id) {//选择第id组场景并设置
        cur_index_ = id;
        scenes_[cur_index_]->Reset();
        game_->set_scene(scenes_[cur_index_]->GetScene());
    }

    bool isPause() { return game_->get_pause(); }

    const ScenePtr &cur_scene() const {//获得当前场景
        return scenes_[cur_index_]->GetScene();
    }

private:
    Window *game_;//Window类指针
    std::vector<GameScenePtr> scenes_;//可变长数组，每个数组元素是GameSceneInterface类指针
    int cur_index_;
};

#endif // SG_SCENEMAN_H_
