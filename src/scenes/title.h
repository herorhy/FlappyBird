#ifndef SG_SCENES_TITLE_H_
#define SG_SCENES_TITLE_H_

#include "engine/background.h"

#include "sceneman.h"
#include "scenes/gamescene.h"
#include "data.h"
#include"engine/MusicSprite.h"
#include"engine/ChunkSprite.h"
class TitleScene : public GameSceneInterface {
public:
    TitleScene(SceneManager& sceneman, ResManager& resman)//构造函数
        : sceneman_(sceneman), resman_(resman) {
        // init scene
        scene_ = std::make_shared<SpriteManager>(3);//设置一个3层的Scene指针
        //最底下的一层是创建背景
        scene_->CreateSprite<Sprite>(0, "bg", resman_.GetImage("bg1"));
        //
        //中间层是创建游戏标题，选项，信息这三个精灵
        scene_->CreateSprite<Sprite>(1, "title", resman_.GetImage("sg"),
            156, 12, 750, 135);
        scene_->CreateSprite<Sprite>(1, "options", resman_.GetImage("sg"),
            0, 200, 440, 395);
        //scene_->CreateSprite<Sprite>(1, "info", resman_.GetImage("sg"),
        //    50, 660, 700, 80);
        //最后一层是创建箭头精灵
        scene_->CreateSprite<Sprite>(2, "arrow", resman_.GetImage("sg"),
            450, 395, 70, 90);
        // init sprites
        //sound
        select = new ChunkSprite(resman.GetChunk("select"));
        //scene_->sprite(1, "demotext")->set_visible(true);
        //设置这些精灵的坐标（他们初始出现在屏幕的位置）
        scene_->sprite(1, "title")->set_x(100);
        scene_->sprite(1, "title")->set_y(150);
        scene_->sprite(1, "options")->set_x(200);
        scene_->sprite(1, "options")->set_y(350);
        //scene_->sprite(1, "info")->set_x(200);
        //scene_->sprite(1, "info")->set_y(860);
        scene_->sprite(2, "arrow")->set_x(180);
        scene_->sprite(2, "arrow")->set_y(370);

    }

    void Reset() override {//覆写继承基类的虚函数，重新设置箭头的坐标
        scene_->sprite(2, "arrow")->set_y(370);
        key_pressed_ = true;
    }
    void OnKeyDown(KeyStatus key) {
        if (!key_pressed_ && key) {
            select->Play();
            auto& arrow = scene_->sprite(2, "arrow");
            if (key & kKey_Up) {//箭头上移
                auto org_y = arrow->y();
                arrow->set_y((370 + ((org_y - 370) - 130 + 390) % 390));
            }
            else if (key & kKey_Down) {//箭头下移
                auto org_y = arrow->y();
                arrow->set_y((370 + ((org_y - 370) + 130) % 390));
            }
            else if (key & kKey_Enter) {
                switch (arrow->y()) {
                case (370 + 130): {//箭头位于中间，再次载入之前的游戏
                    GameData::LoadGameNextTime();
                    // fall through
                }
                case 370: {//开始一局新的游戏
                    sceneman_.SwitchScene(main_id_);
                    break;
                }
                default: {//退出游戏
                    sceneman_.QuitGame();
                    break;
                }
                }
            }
            key_pressed_ = true;
            
        }
        if (key_pressed_ && !key) {
            key_pressed_ = false;
        }
    }
    void OnMouseClickAndMove(MouseStatus mouse) {

    }
    void CollisionHandle() {

    }
    void GameRun() {

    }

    const ScenePtr& GetScene() const override {//获取当前的场景
        return scene_;
    }

    void set_main_id(int main_id) { main_id_ = main_id; }

private:
    SceneManager& sceneman_;//SceneManager类的引用对象
    ResManager& resman_;//ResManager类的引用对象
    ScenePtr scene_;//一个Scene类的指针
    bool key_pressed_;//判断键盘是否按下
    //sound
    ChunkSprite* select;
    // scene id
    int main_id_;
};

#endif // SG_SCENES_TITLE_H_
