#pragma once
#include "BaseComponent.h"

class GameObject;

class SpriteComponent : public BaseComponent
{
    //AEGfxTexture* pTex;
public:
    SpriteComponent(GameObject* _owner);
    ~SpriteComponent();

    virtual void Update() override;

    struct Color
    {
        unsigned char red = 255;
        unsigned char green = 255;
        unsigned char blue = 255;
    };
    Color m_color;
    AEGfxVertexList* mesh;
    Color& GetColor(){ return m_color; }    

    static BaseRTTI* CreateSpriteComponent();
    static constexpr const char* SpriteTypeName = "Sprite";

    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};