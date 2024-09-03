#pragma once
#include"BaseEnemyState.h"
#include "AEVec2.h"

class GameObject;

namespace ESM
{
    class TargetAim_Sniper : public BaseEnemyState
    {
    public:
        virtual void Init() override;//override�� �����Ƕ��� ���� virtual�̶� ���� Init()�� ȣ��ȴ�.
        virtual void Update() override;
        virtual void Exit() override;
    private:
        //�������� �� ���ӿ�����Ʈ 2�� ���� ����, ���� �ð�
        GameObject* TargetAim_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;

        //Attack�� ����
        float AttackDelay;
        float m_fDt;
        //TargetOn�� �ð�
        float Search_outTime;
        float m_fDt_Target;


        //����� ���� �÷��̾� Pos ���󰡴� aim ����� 
        AEVec2 playerPos;
        AEVec2 enemyPos;
        AEVec2 chaseVec;
        AEVec2 unitChaseVec;
        AEVec2 nor_dVec;

        AEVec2 nor_dVec_bullet{ 0,0 };
        AEVec2 bulletPos;
        AEVec2 bullet_Vec;
        AEVec2 bullet_const;
        AEVec2 bullet_enemy_sub;


    public:
        TargetAim_Sniper(GameObject* _enemy, GameObject* _player, bool dir, float Time);
        AEVec2 GetEnemyDvec();
    };
}