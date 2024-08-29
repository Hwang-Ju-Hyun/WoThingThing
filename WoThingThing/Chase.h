#pragma once
#include"BaseEnemyState.h"
#include "AEVec2.h"

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
        //�������� �� ���ӿ�����Ʈ 2�� ���� ����, ���� �ð�
        GameObject* Chase_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;
        
        //�þ߿��� ����� �� ���ӽð�
        float Chase_outTime;

        //chase�ӽ�
        AEVec2 playerPos;
        AEVec2 enemyPos;
        AEVec2 chaseVec;
        AEVec2 unitChaseVec;
    public:
        Chase(GameObject* _enemy, GameObject* _player, bool dir, float Time);
    };
}