#pragma once
#include "BaseLevel.h"
#include "header.h"

class GameObject;
class Resource;
class AudioResource;

namespace Level
{
    class StageBoss_Lvl :public GSM::BaseLevel
    {
    private:
        GameObject* background;
        GameObject* player;
        GameObject* playerAnim;
        GameObject* mouseAim;
        GameObject* aimTrace;
        float AccTime = 0.f;
        float AttackDelayTime = 0.f;
        bool gameOver;
        Resource* bgm;
        AudioResource* bgm_res;
    public:
        StageBoss_Lvl();
        ~StageBoss_Lvl();
        
        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;

    private:        
        GameObject* Platform;        
        GameObject* Enemy_TEST;
        GameObject* Boss_drone;
        
        GameObject* Boss1;
    public:
        int counter = 0;
    private:             
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);
        void Collision();
        static bool Stage2;
    private:
        bool enemyDir;
        AEVec2 playerPos;
        AEVec2 enemyTestPos;
        AEVec2 chaseVec;
        float m_fDt;
        float melee_DelayAtk;
    public:
        bool IsVibration = false;
        float plusX = 0;
        float minusX = 0;
        float plusY = 0;
        float minusY = 0;
        bool changeCamDir = false;
        float VibrationAccTime = 0.f;
        bool Boss_drone_dir = true;
        bool Boss_bullet_pattern1;
    };
}