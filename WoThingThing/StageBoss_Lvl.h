#pragma once
#include "BaseLevel.h"
#include "header.h"

class GameObject;

namespace Level
{
    class StageBoss_Lvl :public GSM::BaseLevel
    {
    private:
        GameObject* player;
        GameObject* mouseAim;
        GameObject* aimTrace;
        float AccTime = 0.f;
        float AttackDelayTime = 0.f;
        bool gameOver;
    public:
        StageBoss_Lvl();
        ~StageBoss_Lvl();
        
        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;

    private:        
        GameObject* Platform;        
        GameObject* Enemy_TEST;
        
        GameObject* Boss1;
    public:
        int counter = 0;
    private:             
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);
        void Collision();

    private:
        bool enemyDir;
        AEVec2 playerPos;
        AEVec2 enemyTestPos;
        AEVec2 chaseVec;
        float m_fDt;
        float melee_DelayAtk;
    };
}