#pragma once
#include"BaseEnemyState.h"

class GameObject;

namespace ESM
{
    class IDLE_Sniper : public BaseEnemyState
    {
    public:
        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;
    private:
        //필수 4요소
        GameObject* enemy;
        GameObject* player;
        bool dir;
        float dir_Time;

        //시간
        float m_fDt;
        float accumulatedTime;//시간 기록에 필요함
    public:
        IDLE_Sniper(GameObject* _enemy, GameObject* _player, bool dir_num, float Time);//여기서 총알 오브젝트 추가
        //오브젝트 2개와 dir_num은 방향 Time은 방향바꾸는데 걸리는 시간
    };
}
