#pragma once
#include "BaseLevel.h"
#include "header.h"
#include <array>

class GameObject;
class Resource;
class AudioResource;

namespace Level
{
	class StageTutorial_Lvl :public GSM::BaseLevel
	{
    public:
        StageTutorial_Lvl();
        ~StageTutorial_Lvl();
    private:
        std::array<GameObject*, 3> Enemy;
        std::array<GameObject*, 2> EnemySniper;
        GameObject* background;
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
    private:
        float MoveAccTime = 0.f;
    public:
        void SetMoveAccTime(float _time) { MoveAccTime = _time; }
        void AddMoveAccTime(float _time) { MoveAccTime += _time; }
        const float GetMoveAccTime() { return MoveAccTime; }
    public:
        bool IsVibration = false;
        float plusX = 0;
        float minusX = 0;
        float plusY = 0;
        float minusY = 0;
        bool changeCamDir = false;
        float VibrationAccTime = 0.f;
    public:
        void SetVibration(bool _vib) { IsVibration = _vib; }
        const bool GetVibration() { return IsVibration; }
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);
        void Collision();
    private:
        int EnemyDeathCnt = 3;
        int EnemySniperDeathCnt = 2;
    public:
        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;
	};

}