#ifndef SG_SCENEMAN_H_
#define SG_SCENEMAN_H_

#include <vector>

#include "engine/window.h"
#include "scenes/gamescene.h"

class SceneManager {
public:
    SceneManager(Window *game) : game_(game), cur_index_(0) {}//���캯���������Ϸ���洰��

    int AddScene(const GameScenePtr &scene) {//����һ���³���
        scenes_.push_back(scene);
        return scenes_.size() - 1;
    }

    void FrameBegin(KeyStatus key,MouseStatus mouse) {//��ǰ�����Ŀ��Ʋ���
        scenes_[cur_index_]->FrameBegin(key,mouse);
    }

    void QuitGame() { game_->Quit(); }//�˳���Ϸ
    void PauseGame(bool is_paused) { game_->set_paused(is_paused); }//��Ϸ��ͣ
    void RenderGame() { game_->Render(); }
    void SwitchScene(int id) {//ѡ���id�鳡��������
        cur_index_ = id;
        scenes_[cur_index_]->Reset();
        game_->set_scene(scenes_[cur_index_]->GetScene());
    }

    bool isPause() { return game_->get_pause(); }

    const ScenePtr &cur_scene() const {//��õ�ǰ����
        return scenes_[cur_index_]->GetScene();
    }

private:
    Window *game_;//Window��ָ��
    std::vector<GameScenePtr> scenes_;//�ɱ䳤���飬ÿ������Ԫ����GameSceneInterface��ָ��
    int cur_index_;
};

#endif // SG_SCENEMAN_H_
