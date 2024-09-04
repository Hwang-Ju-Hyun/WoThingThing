#pragma once
#pragma once
#include"BaseEnemyState.h"
#include "AEVec2.h"
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
        //�������� �� ���ӿ�����Ʈ 2�� ���� ����, ���� �ð�
        GameObject* Attack_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;
        GameObject* PlatForm;
        std::string e_state_name;
        AEVec2 FirstPlacePos;

        //���� ������ �ֱ�
        float m_fDt;
        float melee_DelayAtk;

    public:
        EnemyAttack(GameObject* _enemy, GameObject* _player,
            bool dir, float Time, GameObject* _platform, std::string _state_name, AEVec2 _FirstPlacePos);
    };
}