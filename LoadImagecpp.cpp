#include <map>
#include "LoadImage.h"

void LodaImage(ResManager& resman)
{
    std::map<std::string, std::string>Images = {
        {"bg", "res/bg.png"},
        {"sg", "res/sg.png"},
        {"Fighter", "res/Fighter.png"},
        {"Enemy", "res/Enemy.png"},
        {"player_blt", "res/player_blt.png"}
    };

    for (auto x : Images)
    {
        resman.LoadImage(x.first, x.second);
    }
}