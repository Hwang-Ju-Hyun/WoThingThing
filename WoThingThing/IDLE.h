#pragma once
#include"BaseEnemyState.h"
#include "AEVec2.h"
#include <iostream>

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
        //�ʼ� 4���
        GameObject* enemy;
        GameObject* player;
        bool dir;
        float dir_Time;
        GameObject* platform;
        std::string e_state_name;
        AEVec2 FirstPlacePos;

        //Attack�� ����
        float idle_time;
        float m_fDt;

        float accumulatedTime;//�ð� ��Ͽ� �ʿ���

        //�ӵ�����
        AEVec2 const_chaseVec;
        AEVec2 Return_Vec;
        AEVec2 slow_Vec;

        AEVec2 enemyPos;
        AEVec2 returnVec;
        AEVec2 unitReturnVec;

        bool mainpulActice;
        f32 timeManipul;

    public:
        IDLE(GameObject* _enemy, GameObject* _player, 
            bool dir_num, float Time, GameObject* _platform, std::string state_name, AEVec2 _FirstPlacePos);
        //������Ʈ 2���� dir_num�� ���� Time�� ����ٲٴµ� �ɸ��� �ð�
    };
}
