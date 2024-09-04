#pragma once
#include "BaseLevel.h"
#include "header.h"
#include <fstream>

class GameObject;

namespace Level
{
    class MapEditor :
        public GSM::BaseLevel
    {
    public:
        MapEditor();
        ~MapEditor();
    public:
        virtual void Init() override;//override는 재정의땜에 같은 virtual이라도 여기 Init()이 호출된다.
        virtual void Update() override;
        virtual void Exit() override;        
    public:
        GameObject* go;
        GameObject* player;
        GameObject* mouseAim;
        GameObject* aimTrace;
        std::fstream file;
        s32 mouseX, mouseY;        
        struct Vec2
        {
            AEVec2 pos = {};
            AEVec2 scale = {};
        };
        bool start = true;
        
    public:
        int goPosX;
        int goPosY;
        int grid_X;
        int grid_Y;
        int goTileW;
        int goTileH;
    public:
        bool grid[10000][10000];
    public:
        void HandleCollision(GameObject* obj1, GameObject* obj2);
        int GameObject_MouseIn(GameObject* obj);
    };
};

