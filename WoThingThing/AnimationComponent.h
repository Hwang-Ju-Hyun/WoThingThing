#pragma once
#include "BaseComponent.h"

class GameObject;

class AnimationComponent : public BaseComponent
{
    AEGfxVertexList* mesh;
    AEGfxTexture* pTex;
public:
    AnimationComponent(GameObject* _owner);
    ~AnimationComponent();

    virtual void Update() override;
};