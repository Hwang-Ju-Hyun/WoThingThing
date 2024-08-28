#pragma once
#include"BaseEnemyState.h"

class GameObject;

namespace ESM
{
    class IDLE: public BaseEnemyState
    {
    public:
        virtual void Init() override;//override�� �����Ƕ��� ���� virtual�̶� ���� Init()�� ȣ��ȴ�.
        virtual void Update() override;
        virtual void Exit() override;
    private:
    public:
        IDLE(GameObject* _owner);

    };
}
