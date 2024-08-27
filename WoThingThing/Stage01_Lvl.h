#pragma once
#include "BaseLevel.h"

class GameObject;
class MainMenu_Lvl;
namespace Level
{
    class Stage01_Lvl : public GSM::BaseLevel
    {
        GameObject* player;
        GameObject* mouseAim;
        GameObject* aimTrace;


    public:
        Stage01_Lvl();
        ~Stage01_Lvl();

        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;
    };
}


