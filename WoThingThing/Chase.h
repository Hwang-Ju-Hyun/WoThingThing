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
        
        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;
        GameObject* PlatForm;
    private:
        //가져가야 할 게임오브젝트 2개 보는 방향, 보는 시간
        GameObject* Chase_enemy;
        GameObject* Player;
        bool dir_state;
        float dir_Time;
        std::string e_state_name;
        AEVec2 FirstPlacePos;

        //시야에서 사라진 후 지속시간
        //float Chase_time;
        float m_fDt;
        float Chase_outTime;

        //chase임시
        AEVec2 playerPos;
        AEVec2 enemyPos;
        AEVec2 chaseVec;
        AEVec2 unitChaseVec;
        AEVec2 slowChase;
        AEVec2 const_chaseVec;
        AEVec2 ChaseVecAdd;

        AEVec2 StopVec;
        ChasePlatFormSettor Subscriber;


        bool mainpulActice;
        f32 timeManipul;
    public:
        ChasePlatFormSettor GetSubscriber() {return Subscriber;}
    public:
        Chase(GameObject* _enemy, GameObject* _player,
            bool dir, float Time, GameObject* _platform, std::string state_name, AEVec2 _FirstPlacePos);
        ~Chase()override;
    };
}