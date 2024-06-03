#ifndef SG_SCENES_RANK_H_
#define SG_SCENES_RANK_H_

#include "engine/background.h"
#include "engine/number.h"

#include "sceneman.h"
#include "scenes/gamescene.h"
#include "data.h"

class RankScene : public GameSceneInterface {
public:
    RankScene(SceneManager& sceneman, ResManager& resman/*, const SDLRendererPtr& renderer*/)
        : sceneman_(sceneman), resman_(resman) {
        // init scene
        scene_ = std::make_shared<SpriteManager>(2);//设置一个2层的Scene指针
        scene_->CreateSprite<Sprite>(0, "bg", resman_.GetImage("bg1"));
        //scene_->CreateSprite<TextSprite>(1, "demotext", resman.GetRenderer(), resman.GetFont("demofont"), "demotext");
        scene_->CreateSprite<Sprite>(1, "lose", resman.GetImage("sg"),
            50, 750, 495, 145);
        scene_->CreateSprite<Sprite>(1, "win", resman.GetImage("sg"),
            510, 465, 395, 185);
        scene_->CreateSprite<Sprite>(1, "got", resman.GetImage("sg"),
            570, 735, 190, 110);
        scene_->CreateSprite<Sprite>(1, "rank", resman.GetImage("sg"),
            570, 845, 175, 105);
        scene_->CreateSprite<Number>(1, "score", resman.GetImage("sg"),
            0, 906, 50, 54);
        scene_->CreateSprite<Number>(1, "0", resman.GetImage("sg"),
            0, 906, 50, 54);
        scene_->CreateSprite<Number>(1, "1", resman.GetImage("sg"),
            0, 906, 50, 54);
        scene_->CreateSprite<Number>(1, "2", resman.GetImage("sg"),
            0, 906, 50, 54);
        scene_->CreateSprite<Number>(1, "3", resman.GetImage("sg"),
            0, 906, 50, 54);
        scene_->CreateSprite<Number>(1, "4", resman.GetImage("sg"),
            0, 906, 50, 54);
        //最高层处理信息
        //
        fail = new ChunkSprite(resman.GetChunk("fail"));
        //scene_->sprite(1, "demotext")->set_visible(true);
        // init sprites
        scene_->sprite(1, "lose")->set_x((kWinWidth - 495) / 2);
        scene_->sprite(1, "lose")->set_y(150);
        scene_->sprite(1, "win")->set_x((kWinWidth - 395) / 2);
        scene_->sprite(1, "win")->set_y(130);
    }

    void Reset() override {
        // get sprites

        auto score = static_cast<Number*>(scene_->sprite(1, "score").get());
        Number* rank[] = {
            static_cast<Number*>(scene_->sprite(1, "0").get()),
            static_cast<Number*>(scene_->sprite(1, "1").get()),
            static_cast<Number*>(scene_->sprite(1, "2").get()),
            static_cast<Number*>(scene_->sprite(1, "3").get()),
            static_cast<Number*>(scene_->sprite(1, "4").get()),
        };
        // set number & get max width
        score->set_number(GameData::score());
        int max_width = score->width(), index = 0;
        for (const auto& i : GameData::rank()) {
            rank[index]->set_number(i);
            if (rank[index]->width() > max_width) {
                max_width = rank[index]->width();
            }
            if (++index >= 5) break;
        }
        // set position of score & rank area
        const int kOffsetX = 50, kGapSize = 20, kVertDist = 70;
        scene_->sprite(1, "got")->set_x((kWinWidth -
            (190 + kGapSize + max_width)) / 2 - kOffsetX);
        scene_->sprite(1, "got")->set_y(370);
        score->set_x(scene_->sprite(1, "got")->x() + 190 + kGapSize);
        score->set_y(400);
        scene_->sprite(1, "rank")->set_x(scene_->sprite(1, "got")->x() + 7);
        scene_->sprite(1, "rank")->set_y(500);
        rank[0]->set_x(score->x());
        rank[0]->set_y(530);
        for (int i = 1; i < 5; ++i) {
            rank[i]->set_x(score->x());
            rank[i]->set_y(rank[i - 1]->y() + kVertDist);
        }
        // set visibility
        scene_->sprite(1, "lose")->set_visible(GameData::game_over());
        scene_->sprite(1, "win")->set_visible(GameData::game_won());
        fail->Play();
    }
    void OnKeyDown(KeyStatus key) {
        if (key & kKey_Enter) {
            sceneman_.SwitchScene(title_id_);
            
        }
    }
    void OnMouseClickAndMove(MouseStatus mouse) {

    }
    void CollisionHandle() {

    }
    void GameRun() {

    }


    const ScenePtr& GetScene() const override {
        return scene_;
    }

    void set_title_id(int title_id) { title_id_ = title_id; }

private:
    SceneManager& sceneman_;
    ResManager& resman_;
    ScenePtr scene_;
    //sound
    ChunkSprite* fail;
    // scene id
    int title_id_;
};

#endif // SG_SCENES_RANK_H_
