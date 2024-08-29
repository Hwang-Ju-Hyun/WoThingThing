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
        GameObject* player;
        bool dir;
        float accumulatedTime;
        float dir_Time;
    public:
        IDLE(GameObject* _enemy, GameObject* _player, bool dir_num, float Time);
        //������Ʈ 2���� dir_num�� ���� Time�� ����ٲٴµ� �ɸ��� �ð�
    };
}
