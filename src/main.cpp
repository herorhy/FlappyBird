#include <cstdlib>
#include <ctime>

#include "gamewin.h"
#include "data.h"
#include "scenes/title.h"
#include "scenes/main.h"
#include "scenes/rank.h"
#include"engine/MusicSprite.h"
#include"SDL_mixer.h"
#include<iostream>
using namespace std;


int main(int argc, char *argv[]) {
    // initialize random seed
    std::srand(std::time(nullptr));
    GameData::LoadData();//载入数据
    // load resources
    GameWindow game;//创建一个GameWindow类的对象，用来初始化界面
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        cout << "Failed to open audio: " << Mix_GetError() << endl;
    }
    auto resman = game.CreateResManager();//创建一个ResManager类的对象
    resman.LoadImages();
    resman.LoadBACKGroundMusics();
    resman.LoadSounds();
    resman.LoadFont("demofont", "res/sample.ttf");
    // init scene
    auto title = std::make_shared<TitleScene>(game.sceneman(), resman);//创建初始背景
    auto title_id = game.sceneman().AddScene(title);//将初始背景加入
    auto game_main = std::make_shared<MainScene>(game.sceneman(), resman);//创建游戏主题场景
    auto main_id = game.sceneman().AddScene(game_main);//将游戏主题场景加入
    auto rank = std::make_shared<RankScene>(game.sceneman(), resman);//创建游戏结束场景
    auto rank_id = game.sceneman().AddScene(rank);//将游戏结束场景加入
    title->set_main_id(main_id);//游戏主题场景的main_id_值是1
    game_main->set_rank_id(rank_id);//游戏结束场景的main_id_值是2
    game_main->set_title_id(title_id);//
    rank->set_title_id(title_id);
    game.sceneman().SwitchScene(title_id);//将场景设置为初始场景
    // main loop
    game.MainLoop();//游戏循环
    // save game data
    GameData::SaveData();//保存数据
    return 0;
}
