#pragma once
#include "BaseLevel.h"

class GameObject;

namespace Level
{
    class MainMenu_Lvl :
        public GSM::BaseLevel
    {    
    public:        
    //    ~MainMenu_Lvl()override {};
    public:
        virtual void Init() override;//override�� �����Ƕ��� ���� virtual�̶� ���� Init()�� ȣ��ȴ�.
        virtual void Update() override;
        virtual void Exit() override;
    private:
        int a = 0;
        GameObject* StartButton;
        GameObject* ExitButton;
        
    };
}


