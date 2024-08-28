#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"

class GameObejct;

class PlayerComp : public BaseComponent
{
    AEVec2  m_vVelocity;
    AEVec2  dashVelocity;
    AEVec2  dash_const;
    AEVec2  jumpVelocity;
    AEVec2  m_vGravity;
public:
    PlayerComp(GameObject* _owner);
    ~PlayerComp() {};

    void Jump(float jumpVal);
    void Dash(AEVec2 directVec);

    virtual void Update() override;

    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};