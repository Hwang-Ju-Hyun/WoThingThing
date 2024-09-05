#pragma once
#include "BaseComponent.h"
#include<iostream>
class GameObject;

class AnimationComponent : public BaseComponent
{
    AEGfxVertexList* mesh;
    AEGfxTexture* pTex;
    char* file;
public:
    AnimationComponent(GameObject* _owner);
    ~AnimationComponent();

    virtual void Update() override;
};