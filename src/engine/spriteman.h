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
    void CreateSprite(int layer, const std::string &name, Args &&...args) {//��������
        sprites_[layer][name] = {std::make_shared<T>(this,
                std::forward<Args>(args)...), true};//��layer������Ϊname�ľ����ǡ���
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
        return sprites_[layer][name].first;//���ص�layer�㣬key��name��ֵ�ĵ�һ��Ԫ��
    }

private:
    using TaggedSprite = std::pair<SpritePtr, bool>;//�������Ϊ����һ����SpritePtr��bool����һ��Ľṹ��
    using SpriteMap = std::map<std::string, TaggedSprite>;//��SpriteMap�䵱һ������
    std::vector<SpriteMap> sprites_;//�ɱ䳤���飬����������SpriteMap
};

using ScenePtr = std::shared_ptr<SpriteManager>;//��ScenePtr��ΪScene���һ��ָ��

#endif // SG_ENGINE_SCENE_H_
