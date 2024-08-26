#pragma once
#include "BaseLevel.h"
#include <vector>

class GameObject;
class MainMenu_Lvl;


namespace Level
{
    class Stage01_Lvl :
        public GSM::BaseLevel
    {    
    public:
        Stage01_Lvl();
        ~Stage01_Lvl();
    public:
        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;
    private:
        GameObject* player1;
        std::vector<GameObject*> m_vecPlatforms;
        GameObject* Platform;
    public:       
        int counter = 0;
    };
}


