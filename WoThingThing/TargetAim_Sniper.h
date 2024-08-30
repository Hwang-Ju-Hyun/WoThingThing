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
        GameObject* Chase_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;
        GameObject* bullet;


        //�þ߿��� ����� �� ���ӽð�
        float Search_outTime;
        //Attack�� ����
        float AttackDelay;
        float m_fDt;
        //����� ���� �÷��̾� Pos ���󰡴� aim ����� 
        AEVec2 playerPos;
        AEVec2 enemyPos;
        AEVec2 chaseVec;
        AEVec2 unitChaseVec;
    public:
        TargetAim_Sniper(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _bullet);
    };
}