#pragma once
#include"BaseEnemyState.h"
#include "AEVec2.h"

class GameObject;

namespace ESM
{
    class TargetAim_Sniper : public BaseEnemyState
    {
    public:
        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;
    private:
        //가져가야 할 게임오브젝트 2개 보는 방향, 보는 시간
        GameObject* TargetAim_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;
        GameObject* bullet;

        //Attack용 따로
        float AttackDelay;
        float m_fDt;
        //TargetOn용 시간
        float Search_outTime;
        float m_fDt_Target;


        //여기는 이제 플레이어 Pos 따라가는 aim 만들기 
        AEVec2 playerPos;
        AEVec2 enemyPos;
        AEVec2 chaseVec;
        AEVec2 unitChaseVec;


        AEVec2 nor_dVec_bullet{ 0,0 };
        AEVec2 bulletPos;
        AEVec2 bullet_Vec;
        AEVec2 bullet_const;
        AEVec2 bullet_enemy_sub;


    public:
        TargetAim_Sniper(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _bullet);
    };
}