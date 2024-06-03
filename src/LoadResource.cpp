#include "engine/resman.h"

//=====================================================
//ResManager::LoadImage: 将图片导入资源管理器resman
//参数resman:	ResManager
//返回值: 无
//=====================================================
void ResManager::LoadImages()
{

    //		设置图片接口及路径		
    std::map<std::string, std::string>images = {
        //{"接口",					"路径"}, ... , {"接口",					"路径"}
            //{"bg",					"res/bg.png"	},
            {"bg1",					"res/bg1.png"	},
            {"tube1",				"res/tube1.png"	},
            {"bird",				"res/bird.png"	},
            {"sg",					"res/sg.png"}
            //{"Fighter",			"res/Fighter.png"},
            //{"Enemy",				"res/Enemy.png"},
            //{"player_blt",		"res/player_blt.png"}
    };

    //导入
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
    //		设置图片接口及路径		
    std::map<std::string, std::string>BGMs = {
        //{"接口",					"路径"}, ... , {"接口",					"路径"}

        {"bgm","res/background.mp3"}
       


    };

    //导入
    for (auto x : BGMs)
    {
        LoadBackGroundMusic(x.first, x.second);
    }
}

void ResManager::LoadSounds()
{
    //		设置图片接口及路径		
    std::map<std::string, std::string>Sounds = {
        //{"接口",					"路径"}, ... , {"接口",					"路径"}

        {"sound1","sound1.mp3"}
        ,{"sound2","sound2.mp3"}
        ,{"ding","res/ding.mp3"}
        ,{"crash","res/crash.mp3"}
        ,{"fly","res/fly.mp3"}
        ,{"fail","res/fail.mp3"}
        ,{"select","res/select.mp3"}
        


    };

    //导入
    for (auto x : Sounds)
    {
        LoadSound(x.first, x.second);
    }
}
