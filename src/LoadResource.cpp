#include "engine/resman.h"

//=====================================================
//ResManager::LoadImage: ��ͼƬ������Դ������resman
//����resman:	ResManager
//����ֵ: ��
//=====================================================
void ResManager::LoadImages()
{

    //		����ͼƬ�ӿڼ�·��		
    std::map<std::string, std::string>images = {
        //{"�ӿ�",					"·��"}, ... , {"�ӿ�",					"·��"}
            //{"bg",					"res/bg.png"	},
            {"bg1",					"res/bg1.png"	},
            {"tube1",				"res/tube1.png"	},
            {"bird",				"res/bird.png"	},
            {"sg",					"res/sg.png"}
            //{"Fighter",			"res/Fighter.png"},
            //{"Enemy",				"res/Enemy.png"},
            //{"player_blt",		"res/player_blt.png"}
    };

    //����
    for (auto x : images)
    {
        LoadImage(x.first, x.second);
    }
}

void ResManager::LoadFonts()
{

}

void ResManager::LoadBACKGroundMusics()
{
    //		����ͼƬ�ӿڼ�·��		
    std::map<std::string, std::string>BGMs = {
        //{"�ӿ�",					"·��"}, ... , {"�ӿ�",					"·��"}

        {"bgm","res/background.mp3"}
       


    };

    //����
    for (auto x : BGMs)
    {
        LoadBackGroundMusic(x.first, x.second);
    }
}

void ResManager::LoadSounds()
{
    //		����ͼƬ�ӿڼ�·��		
    std::map<std::string, std::string>Sounds = {
        //{"�ӿ�",					"·��"}, ... , {"�ӿ�",					"·��"}

        {"sound1","sound1.mp3"}
        ,{"sound2","sound2.mp3"}
        ,{"ding","res/ding.mp3"}
        ,{"crash","res/crash.mp3"}
        ,{"fly","res/fly.mp3"}
        ,{"fail","res/fail.mp3"}
        ,{"select","res/select.mp3"}
        


    };

    //����
    for (auto x : Sounds)
    {
        LoadSound(x.first, x.second);
    }
}
