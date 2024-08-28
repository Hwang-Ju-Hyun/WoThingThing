#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"

class GameObejct;

class PlayerComponent : public BaseComponent
{
    AEVec2  m_vVelocity;
    AEVec2  dashVelocity;
    AEVec2  dash_const;
    AEVec2  jumpVelocity;
    AEVec2  m_vGravity;

    GameObject* player;
public:
    PlayerComponent(GameObject* _owner);
    ~PlayerComponent() {};

    void Jump(float jumpVal);
    void Dash(AEVec2 directVec);

    virtual void Update() override;

    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};