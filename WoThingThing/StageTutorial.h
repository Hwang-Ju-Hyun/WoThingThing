#pragma once
#include "BaseLevel.h"
#include "header.h"

class GameObject;
class Resource;
class AudioResource;

namespace Level
{
	class StageTutorial :public GSM::BaseLevel
	{
    public:
        StageTutorial();
        ~StageTutorial();
    private:
        GameObject* player;
        GameObject* mouseAim;
        GameObject* aimTrace;
        float AccTime = 0.f;
        float AttackDelayTime = 0.f;
        bool gameOver;
        Resource* bgm;
        AudioResource* bgm_res;    
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
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);
        void Collision();
    public:
        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;
	};

}