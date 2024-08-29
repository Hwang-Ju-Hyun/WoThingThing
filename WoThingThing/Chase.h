#pragma once
#include"BaseEnemyState.h"
#include "AEVec2.h"

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
        //가져가야 할 게임오브젝트 2개 보는 방향, 보는 시간
        GameObject* Chase_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;
        
        //시야에서 사라진 후 지속시간
        float Chase_outTime;

        //chase임시
        AEVec2 playerPos;
        AEVec2 enemyPos;
        AEVec2 chaseVec;
        AEVec2 unitChaseVec;
    public:
        Chase(GameObject* _enemy, GameObject* _player, bool dir, float Time);
    };
}