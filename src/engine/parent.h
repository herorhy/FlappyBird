#ifndef SG_ENGINE_PARENT_H_
#define SG_ENGINE_PARENT_H_

class ParentInterface {
public:
    virtual ~ParentInterface() = default;
    virtual void RemoveObject(void *id) = 0;
};

using ParentPtr = ParentInterface *;//��ParentPtr��ParentInterface���ָ��

#endif // SG_ENGINE_PARENT_H_
