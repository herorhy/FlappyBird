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
    TitleScene(SceneManager& sceneman, ResManager& resman)//���캯��
        : sceneman_(sceneman), resman_(resman) {
        // init scene
        scene_ = std::make_shared<SpriteManager>(3);//����һ��3���Sceneָ��
        //����µ�һ���Ǵ�������
        scene_->CreateSprite<Sprite>(0, "bg", resman_.GetImage("bg1"));
        //
        //�м���Ǵ�����Ϸ���⣬ѡ���Ϣ����������
        scene_->CreateSprite<Sprite>(1, "title", resman_.GetImage("sg"),
            156, 12, 750, 135);
        scene_->CreateSprite<Sprite>(1, "options", resman_.GetImage("sg"),
            0, 200, 440, 395);
        //scene_->CreateSprite<Sprite>(1, "info", resman_.GetImage("sg"),
        //    50, 660, 700, 80);
        //���һ���Ǵ�����ͷ����
        scene_->CreateSprite<Sprite>(2, "arrow", resman_.GetImage("sg"),
            450, 395, 70, 90);
        // init sprites
        //sound
        select = new ChunkSprite(resman.GetChunk("select"));
        //scene_->sprite(1, "demotext")->set_visible(true);
        //������Щ��������꣨���ǳ�ʼ��������Ļ��λ�ã�
        scene_->sprite(1, "title")->set_x(100);
        scene_->sprite(1, "title")->set_y(150);
        scene_->sprite(1, "options")->set_x(200);
        scene_->sprite(1, "options")->set_y(350);
        //scene_->sprite(1, "info")->set_x(200);
        //scene_->sprite(1, "info")->set_y(860);
        scene_->sprite(2, "arrow")->set_x(180);
        scene_->sprite(2, "arrow")->set_y(370);

    }

    void Reset() override {//��д�̳л�����麯�����������ü�ͷ������
        scene_->sprite(2, "arrow")->set_y(370);
        key_pressed_ = true;
    }
    void OnKeyDown(KeyStatus key) {
        if (!key_pressed_ && key) {
            select->Play();
            auto& arrow = scene_->sprite(2, "arrow");
            if (key & kKey_Up) {//��ͷ����
                auto org_y = arrow->y();
                arrow->set_y((370 + ((org_y - 370) - 130 + 390) % 390));
            }
            else if (key & kKey_Down) {//��ͷ����
                auto org_y = arrow->y();
                arrow->set_y((370 + ((org_y - 370) + 130) % 390));
            }
            else if (key & kKey_Enter) {
                switch (arrow->y()) {
                case (370 + 130): {//��ͷλ���м䣬�ٴ�����֮ǰ����Ϸ
                    GameData::LoadGameNextTime();
                    // fall through
                }
                case 370: {//��ʼһ���µ���Ϸ
                    sceneman_.SwitchScene(main_id_);
                    break;
                }
                default: {//�˳���Ϸ
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

    const ScenePtr& GetScene() const override {//��ȡ��ǰ�ĳ���
        return scene_;
    }

    void set_main_id(int main_id) { main_id_ = main_id; }

private:
    SceneManager& sceneman_;//SceneManager������ö���
    ResManager& resman_;//ResManager������ö���
    ScenePtr scene_;//һ��Scene���ָ��
    bool key_pressed_;//�жϼ����Ƿ���
    //sound
    ChunkSprite* select;
    // scene id
    int main_id_;
};

#endif // SG_SCENES_TITLE_H_
