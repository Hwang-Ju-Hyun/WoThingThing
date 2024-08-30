#pragma once
#include"BaseEnemyState.h"

class GameObject;

namespace ESM
{
    class IDLE_Sniper : public BaseEnemyState
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
        GameObject* bullet;

        float accumulatedTime;//�ð� ��Ͽ� �ʿ���
    public:
        IDLE_Sniper(GameObject* _enemy, GameObject* _player, bool dir_num, float Time, GameObject* _bullet);//���⼭ �Ѿ� ������Ʈ �߰�
        //������Ʈ 2���� dir_num�� ���� Time�� ����ٲٴµ� �ɸ��� �ð�
    };
}
