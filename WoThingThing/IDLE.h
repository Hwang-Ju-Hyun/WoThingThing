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
        GameObject* enemy;
        float accumulatedTime;
    public:
        IDLE(GameObject* _owner);
        static bool SearchPlayer;//�� ������ �����ϱ� ����

    };
}
