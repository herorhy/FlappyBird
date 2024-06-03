#ifndef SG_SCENES_GAMESCENE_H_
#define SG_SCENES_GAMESCENE_H_

#include <memory>

#include "gamedef.h"
#include "engine/spriteman.h"

class GameSceneInterface {
public:
    virtual ~GameSceneInterface() = default;
    virtual void Reset() = 0;                                       //��������
    //֡���п��
    virtual void FrameBegin(KeyStatus key, MouseStatus mouse) {
        OnKeyDown(key);//��������¼�
        OnMouseClickAndMove(mouse);//��������¼�
        CollisionHandle();//������ײ�¼�
        GameRun();//���������¼�
    }

    virtual const ScenePtr& GetScene() const = 0;   //��ȡ��ǰ������ָ��

    virtual void OnKeyDown(KeyStatus key) = 0;      //�����¼�����
    virtual void OnMouseClickAndMove(MouseStatus mouse) = 0;//����¼�����
    virtual void CollisionHandle() = 0;//��ײ����
    virtual void GameRun() = 0; //��Ϸ�������仯���¼�������л���������

protected:
    //const SDLRendererPtr& renderer_;
};

using GameScenePtr = std::shared_ptr<GameSceneInterface>;//��GameScenePtr��ΪGameSceneInterface���ָ��

#endif // SG_SCENES_GAMESCENE_H_
