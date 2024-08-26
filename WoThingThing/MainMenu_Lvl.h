#pragma once
#include "BaseLevel.h"

class GameObject;

namespace Level
{
    class MainMenu_Lvl :
        public GSM::BaseLevel
    {    
    public:
        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;
    private:
        GameObject* StartButton;
        GameObject* ExitButton;
        
    };
}


