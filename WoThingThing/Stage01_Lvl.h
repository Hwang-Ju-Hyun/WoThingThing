#pragma once
#include "BaseLevel.h"
#include <vector>
#include <array>

class GameObject;
class MainMenu_Lvl;
class Resource;
class AudioResource;

namespace Level
{
    class Stage01_Lvl : public GSM::BaseLevel
    {
        GameObject* background;
        GameObject* player;
        GameObject* playerAnim;
        GameObject* mouseAim;
        GameObject* aimTrace; 
        AEGfxTexture* pTex;
        AEGfxVertexList* pMesh;
        int musicPlay=0;
        bool gameOver;
                
        float AccTime = 0;
    public:
        Stage01_Lvl();
        ~Stage01_Lvl();

        virtual void Init() override;
        virtual void Update() override;
        virtual void Exit() override;
        bool IsVibration = false;
        float plusX = 0;
        float minusX = 0;
        float plusY = 0;
        float minusY = 0;
        bool changeCamDir=false;                
    private:
        std::vector<GameObject*> m_vecPlatforms;
        GameObject* Platform;
        std::array<GameObject*, 20> Enemy;
        std::array<GameObject*, 14> EnemySniper;
        GameObject* Boss1;
        GameObject* Enemy_TEST;
        Resource* bgm;
        AudioResource* bgm_res;
        bool bgm_flag = false;
        float bgm_pitch = 1.0f;
        float bgm_volume = 1.43f;
    public:       
        int counter = 0;
        
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);
        void Collision();
    };
}


