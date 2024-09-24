#pragma once
#include "BaseLevel.h"

class GameObject;

namespace Level
{
    class MainMenu_Lvl : public GSM::BaseLevel
    {
        GameObject* Screen;
        GameObject* StartBtn;
        GameObject* HowBtn;
        GameObject* ExitBtn;
    public:
        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;

    };
}


