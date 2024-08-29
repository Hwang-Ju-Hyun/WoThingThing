#pragma once
#pragma once
#include"BaseEnemyState.h"

class GameObject;

namespace ESM
{
    class EnemyAttack : public BaseEnemyState
    {
    public:
        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;
    private:
        //�������� �� ���ӿ�����Ʈ 2�� ���� ����, ���� �ð�
        GameObject* Attack_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;


    public:
        EnemyAttack(GameObject* _enemy, GameObject* _player, bool dir, float Time);
    };
}