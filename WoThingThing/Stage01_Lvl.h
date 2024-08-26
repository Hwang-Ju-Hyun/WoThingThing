#pragma once
#include "BaseLevel.h"

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
        GameObject* player2;
        GameObject* ball;
        GameObject* goalPost1;
        GameObject* goalPost2;
        GameObject* UpperPost;
        GameObject* DownPost;
    private:
        //0번째 인덱스 player1 스코어
        //1번째 인덱스 player2 스코아
        int score[2];
        bool m_bWin = false;
    public:       
        int counter = 0;
    };
}


