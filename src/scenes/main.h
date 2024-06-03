#ifndef SG_SCENES_MAIN_H_
#define SG_SCENES_MAIN_H_

#include <cstdlib>
#include<iostream>
#include "sceneman.h"
#include "scenes/gamescene.h"
#include "engine/timer.h"

// sprites
#include "engine/number.h"
#include "engine/group.h"
#include "sprites/movbg.h"
#include "sprites/enemy.h"
#include "sprites/bullet.h"
#include "sprites/tip.h"
#include"engine/MusicSprite.h"
#include"engine/ChunkSprite.h"

class MainScene : public GameSceneInterface {
public:
    MainScene(SceneManager& sceneman, ResManager& resman)
        : sceneman_(sceneman), resman_(resman) {
        // init scene
        scene_ = std::make_shared<SpriteManager>(4);//创建4层的Scene指针
        scene_->CreateSprite<MovingBg>(0, "bg1", resman.GetImage("bg1"), -2.5f);//第0层（最底层）载入背景
        scene_->CreateSprite<Group>(1, "enemies");//第一层载入敌机
        //scene_->CreateSprite<Group>(2, "enemy_blt");//第2层载入敌机子弹
        scene_->CreateSprite<Sprite>(2, "player", resman.GetImage("bird"));
        scene_->CreateSprite<Sprite>(3, "paused", resman.GetImage("sg"),
            760, 840, 160, 100);
        scene_->CreateSprite<Number>(3, "score", resman.GetImage("sg"),
            0, 906, 50, 54);
        //SOUND
        ding = new ChunkSprite(resman.GetChunk("ding"));
        crash = new ChunkSprite(resman.GetChunk("crash"));
        bgm = new MusicSprite(resman.GetMusic("bgm"));
        fly = new ChunkSprite(resman.GetChunk("fly"));
        //SCORE
        score_ = static_cast<Number*>(scene_->sprite(3, "score").get());
        score_->set_x(360);
        score_->set_y(150);
        //PAUSE
        paused_ = scene_->sprite(3, "paused");
        paused_->set_x(300);
        paused_->set_y(420);

        //PLAYER
        player_ = scene_->sprite(2, "player");
        player_->set_bounding({ 50, 50, 100, 100 });
        speed = 1;
        count = 0;
        //
        /*b_state = 1;
        */
        enemies_1 = static_cast<Group*>(scene_->sprite(1, "enemies").get());
        enemies_2 = static_cast<Group*>(scene_->sprite(1, "enemies").get());

        last_score = GameData::score();
        pause = false;
    }

    void Reset() override {
        bgm->Play();
        auto status = GameData::NewGame();
        enemies_1->Clear();
        enemies_2->Clear();
        speed = 0;
        count = 0;
        if (status.is_valid) {
            // load a saved game
            player_->set_x(status.fixed_data.player_x);
            player_->set_y(status.fixed_data.player_y);
            
        }
        else {
            player_->set_x(kPlayerInitX);
            player_->set_y(kPlayerInitY);
        }
        
        keySpace_pressed_ = false;
        keyEnter_pressed_ = false;
        //b_state = 1;
        last_score = GameData::score();
    }

    //键盘事件处理
    void OnKeyDown(KeyStatus key) {
        // handle quit
        if (key & kKey_Esc) {    //Esc键退出
            sceneman_.PauseGame(false);
            sceneman_.SwitchScene(title_id_);
            bgm->MusicShutDown();
            return;
        }
        
         // handle pause
        if (!keyEnter_pressed_ && (key & kKey_Enter)) {
            keyEnter_pressed_ = true;
            paused_->set_visible(!paused_->visible());
            pause = paused_->visible();
            if (pause)enemy_gen_.Pause();
            if (!pause)enemy_gen_.Resume();
            sceneman_.PauseGame(paused_->visible());
            sceneman_.RenderGame();   // force redraw   
        }
        if (keyEnter_pressed_ && !(key & kKey_Enter)) {
            keyEnter_pressed_ = false;
        }
        if (paused_->visible()) return;
        // handle player move*/
        if (key & kKey_Space) {
            if (keySpace_pressed_ == false) {
                speed = -10;
                fly->Play();
            }
            keySpace_pressed_ = true;
            if (count == 2)
            {
                speed = speed + 1;
                count = 0;
            }
            else
                count++;
        }
        else
        {
            if (count == 2)
            {
                speed = speed + 1;
                count = 0;
            }
            else
                count++;
            keySpace_pressed_ = false;
        }
       
    }
    //鼠标事件处理
    void OnMouseClickAndMove(MouseStatus mouse) {
        
    }
    //碰撞处理
    void CollisionHandle() {
        if (!pause) {
            if ((player_->y() >= kAreaHeight - 150) || (player_->y() <= 0)) {
                score_->set_number(GameData::score());
                sceneman_.SwitchScene(rank_id_);
                bgm->MusicShutDown();
                crash->Play();
            }
            if (enemies_1->IsCollide(player_.get()) || enemies_2->IsCollide(player_.get()))
            {
                score_->set_number(GameData::score());
                sceneman_.SwitchScene(rank_id_);
                bgm->MusicShutDown();
                crash->Play();
            }
        }
    }
    //游戏中自主变化的事件，比如敌机下落
    void GameRun() {
        if (!pause) {
            if (player_->y() <= kAreaHeight - 150) {
                player_->set_y(player_->y() + speed);
            }

            // generate new enemy
            if (enemy_gen_.CheckInterval(kIntervalEnemyGen)) {
                enemy_gen_.Restart();
                NewEnemy();
            }

            // update data display
            score_->set_number(GameData::score());
            if (last_score < GameData::score()) {
                ding->Play();
                last_score = GameData::score();
            }
        }
    }

    const ScenePtr& GetScene() const override {
        return scene_;
    }

    void set_title_id(int title_id) { title_id_ = title_id; }
    void set_rank_id(int rank_id) { rank_id_ = rank_id; }

private:
    void NewEnemy() {
        posy_ = -(std::rand() % 600);
        enemies_1->CreateSprite<Enemy>(resman_, posy_);
        enemies_2->CreateSprite<Enemy>(resman_, (posy_ + 1100));
    }
    

    SceneManager& sceneman_;
    ResManager& resman_;

    ScenePtr scene_;

    bool keySpace_pressed_,keyEnter_pressed_;
    Timer  enemy_gen_;
    
    int title_id_, rank_id_;
    int speed;
    int count;
    int posy_;
    // sprites
    Number* score_;
    SpritePtr paused_, player_;
    Group* enemies_1;
    Group* enemies_2;

    //sound
    ChunkSprite* ding;
    ChunkSprite* crash;
    ChunkSprite* fly;
    MusicSprite* bgm;

    // bullet states
    //int b_state;
    int last_score;
    bool pause;
};

#endif // SG_SCENES_MAIN_H_
