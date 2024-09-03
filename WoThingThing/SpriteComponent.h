#pragma once
#include "BaseComponent.h"

class GameObject;

class SpriteComponent : public BaseComponent
{
public:
    SpriteComponent(GameObject* _owner);
    ~SpriteComponent();
public:
    virtual void Update() override;
public:
    struct Color
    {
        unsigned char red = 255;
        unsigned char green = 255;
        unsigned char blue = 255;
    };
    Color m_color;
    AEGfxVertexList* mesh;
public:
    Color& GetColor(){ return m_color; }    
public:
    static BaseRTTI* CreateSpriteComponent();
    static constexpr const char* SpriteTypeName = "Sprite";
public:
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};