#pragma once
#include"BaseEnemyState.h"
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

        //Attack�� ����
        float idle_time;
        float m_fDt;

        float accumulatedTime;//�ð� ��Ͽ� �ʿ���
    public:
        IDLE(GameObject* _enemy, GameObject* _player, bool dir_num, float Time, GameObject* _platform, std::string state_name);
        //������Ʈ 2���� dir_num�� ���� Time�� ����ٲٴµ� �ɸ��� �ð�
    };
}
