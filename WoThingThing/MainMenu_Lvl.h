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
        virtual void Init() override;//override�� �����Ƕ��� ���� virtual�̶� ���� Init()�� ȣ��ȴ�.
        virtual void Update() override;
        virtual void Exit() override;

    };
}


