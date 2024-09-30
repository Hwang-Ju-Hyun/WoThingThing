#pragma once
#include "BaseComponent.h"

class GameObject;

class SpriteComponent : public BaseComponent
{
    f32 alpha;
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

    void SetTexture(AEGfxTexture* inputTex);
    AEGfxTexture* pTex;

    Color& GetColor() { return m_color; };
    void SetAlpha(f32 value);

    static BaseRTTI* CreateSpriteComponent();
    static constexpr const char* SpriteTypeName = "Sprite";    

    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson(const json& str)override;
};