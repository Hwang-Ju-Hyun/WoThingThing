#pragma once
#include "BaseLevel.h"
#include <vector>

class GameObject;
class MainMenu_Lvl;


namespace Level
{
    class Stage01_Lvl : public GSM::BaseLevel
    {
        GameObject* player;
        GameObject* mouseAim;
        GameObject* aimTrace;

        bool gameOver;
    public:
        Stage01_Lvl();
        ~Stage01_Lvl();

        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;

    private:
        std::vector<GameObject*> m_vecPlatforms;
        GameObject* Platform;
        GameObject* Enemy;
        GameObject* EnemySniper;
        GameObject* Boss1;
    public:       
        int counter = 0;
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);
        void Collision();
    };
}


