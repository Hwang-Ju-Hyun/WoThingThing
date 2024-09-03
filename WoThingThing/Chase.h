#pragma once
#include"BaseEnemyState.h"
#include <iostream>
#include "AEVec2.h"
#include"EventManager.h"
class GameObject;


namespace ESM
{
    class Chase : public BaseEnemyState
    {
    public:
        virtual void Init() override;//override�� �����Ƕ��� ���� virtual�̶� ���� Init()�� ȣ��ȴ�.
        virtual void Update() override;
        virtual void Exit() override;
        GameObject* PlatForm;
    private:
        //�������� �� ���ӿ�����Ʈ 2�� ���� ����, ���� �ð�
        GameObject* Chase_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;
        std::string e_state_name;

        //�þ߿��� ����� �� ���ӽð�
        //float Chase_time;
        float m_fDt;
        float Chase_outTime;

        //chase�ӽ�
        AEVec2 playerPos;
        AEVec2 enemyPos;
        AEVec2 chaseVec;
        AEVec2 unitChaseVec;
        AEVec2 slowChase;

        AEVec2 StopVec;
        ChasePlatFormSettor Subscriber;


        bool mainpulActice;
        f32 timeManipul;

    public:
        Chase(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _platform, std::string state_name);
    };
}