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
        //가져가야 할 게임오브젝트 2개 보는 방향, 보는 시간
        GameObject* Attack_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;

        //공격 딜레이 주기
        float melee_DelayAtk;

    public:
        EnemyAttack(GameObject* _enemy, GameObject* _player, bool dir, float Time);
    };
}