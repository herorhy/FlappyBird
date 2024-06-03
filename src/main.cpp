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
    GameData::LoadData();//��������
    // load resources
    GameWindow game;//����һ��GameWindow��Ķ���������ʼ������
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        cout << "Failed to open audio: " << Mix_GetError() << endl;
    }
    auto resman = game.CreateResManager();//����һ��ResManager��Ķ���
    resman.LoadImages();
    resman.LoadBACKGroundMusics();
    resman.LoadSounds();
    resman.LoadFont("demofont", "res/sample.ttf");
    // init scene
    auto title = std::make_shared<TitleScene>(game.sceneman(), resman);//������ʼ����
    auto title_id = game.sceneman().AddScene(title);//����ʼ��������
    auto game_main = std::make_shared<MainScene>(game.sceneman(), resman);//������Ϸ���ⳡ��
    auto main_id = game.sceneman().AddScene(game_main);//����Ϸ���ⳡ������
    auto rank = std::make_shared<RankScene>(game.sceneman(), resman);//������Ϸ��������
    auto rank_id = game.sceneman().AddScene(rank);//����Ϸ������������
    title->set_main_id(main_id);//��Ϸ���ⳡ����main_id_ֵ��1
    game_main->set_rank_id(rank_id);//��Ϸ����������main_id_ֵ��2
    game_main->set_title_id(title_id);//
    rank->set_title_id(title_id);
    game.sceneman().SwitchScene(title_id);//����������Ϊ��ʼ����
    // main loop
    game.MainLoop();//��Ϸѭ��
    // save game data
    GameData::SaveData();//��������
    return 0;
}
