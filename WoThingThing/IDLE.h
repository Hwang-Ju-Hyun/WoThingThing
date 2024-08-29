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
        bool dir;
        float accumulatedTime;
        float dir_Time;
    public:
        IDLE(GameObject* _enemy, GameObject* _player, bool dir_num, float Time);
        //오브젝트 2개와 dir_num은 방향 Time은 방향바꾸는데 걸리는 시간
    };
}
