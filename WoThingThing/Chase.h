#pragma once
#include"BaseEnemyState.h"

class GameObject;

namespace ESM
{
    class Chase : public BaseEnemyState
    {
    public:
        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;
    private:
        GameObject* Chase_enemy;
        GameObject* Player;
        float accumulatedTime;
        bool dir_state;
    public:
        Chase(GameObject* _enemy, GameObject* _player, bool dir);
    };
}