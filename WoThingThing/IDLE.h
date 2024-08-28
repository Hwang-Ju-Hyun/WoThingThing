#pragma once
#include"BaseEnemyState.h"

class GameObject;

namespace ESM
{
    class IDLE: public BaseEnemyState
    {
    public:
        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;
    private:
        GameObject* enemy;
        GameObject* player;
        float accumulatedTime;
    public:
        IDLE(GameObject* _enemy, GameObject* _player);
    };
}
