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

        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;

    };
}


