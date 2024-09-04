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
    public:
        StageBoss_Lvl();
        ~StageBoss_Lvl();

        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;

    private:
        std::vector<GameObject*> m_vecPlatforms;
        GameObject* Platform;
        GameObject* Enemy;
        GameObject* Enemy_TEST;
    public:
        int counter = 0;
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);

    };
}