#ifndef SG_ENGINE_SCENE_H_
#define SG_ENGINE_SCENE_H_

#include <memory>
#include <utility>
#include <string>
#include <map>
#include <vector>
#include <queue>

#include "sdltype.h"
#include "sprite.h"
#include "parent.h"

class SpriteManager : public ParentInterface {
public:
    SpriteManager(int layer_count) {
        sprites_.resize(layer_count);
    }

    template <typename T, typename ...Args>
    void CreateSprite(int layer, const std::string &name, Args &&...args) {//创建精灵
        sprites_[layer][name] = {std::make_shared<T>(this,
                std::forward<Args>(args)...), true};//第layer层名字为name的精灵是……
    }

    void AddSprite(int layer, const std::string &name,
            const SpritePtr &sprite) {
        sprites_[layer][name] = {sprite, true};
    }

    void RemoveSprite(int layer, const std::string &name) {
        auto &cur_layer = sprites_[layer];
        auto it = cur_layer.find(name);
        if (it != cur_layer.end()) {
            cur_layer.erase(it);
        }
    }

    void RemoveObject(void *id) override;

    void Render(const SDLRendererPtr &renderer);

    const SpritePtr &sprite(int layer, const std::string &name) {
        return sprites_[layer][name].first;//返回第layer层，key是name的值的第一个元素
    }

private:
    using TaggedSprite = std::pair<SpritePtr, bool>;//可以理解为创建一个将SpritePtr和bool绑定在一起的结构体
    using SpriteMap = std::map<std::string, TaggedSprite>;//让SpriteMap充当一个集合
    std::vector<SpriteMap> sprites_;//可变长数组，变量类型是SpriteMap
};

using ScenePtr = std::shared_ptr<SpriteManager>;//让ScenePtr成为Scene类的一个指针

#endif // SG_ENGINE_SCENE_H_
