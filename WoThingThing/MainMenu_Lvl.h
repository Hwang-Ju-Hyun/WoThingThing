#pragma once
#include "BaseLevel.h"
#include "Resource.h"
#include "AudioResource.h"

class GameObject;

namespace Level
{
    class MainMenu_Lvl : public GSM::BaseLevel
    {
        GameObject* Screen;
        GameObject* StartBtn;
        GameObject* HowBtn;
        GameObject* ExitBtn;

        Resource* btnSfx;
        AudioResource* btn_res;

        Resource* mainmenuBGM;
        AudioResource* BGM_res;

        float bgm_pitch = 1.0f;
        float bgm_volume = 1.43f;
    public:

        virtual void Init() override;//override�� �����Ƕ��� ���� virtual�̶� ���� Init()�� ȣ��ȴ�.
        virtual void Update() override;
        virtual void Exit() override;

    };
}


