#pragma once
#include"BaseEnemyState.h"

class GameObject;

namespace ESM
{
    class Chase : public BaseEnemyState
    {
    public:
        virtual void Init() override;//override�� �����Ƕ��� ���� virtual�̶� ���� Init()�� ȣ��ȴ�.
        virtual void Update() override;
        virtual void Exit() override;
    private:
        GameObject* Chase_enemy;
        GameObject* Player;
        float accumulatedTime;

    public:
        Chase(GameObject* _enemy, GameObject* _player);
    };
}