#pragma once
#pragma once
#include"BaseEnemyState.h"
#include <iostream>
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
        GameObject* PlatForm;
        std::string e_state_name;

        //공격 딜레이 주기
        float m_fDt;
        float melee_DelayAtk;

    public:
        EnemyAttack(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _platform, std::string _state_name);
    };
}