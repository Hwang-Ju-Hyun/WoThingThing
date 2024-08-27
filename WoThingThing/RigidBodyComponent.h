#pragma once
#include "BaseComponent.h"

class GameObject;

class RigidBodyComponent : public BaseComponent
{
    AEVec2  m_vVelocity;
    AEVec2  dashVelocity;
    AEVec2  dash_const;
    AEVec2  jumpVelocity;
    AEVec2  m_vGravity;

public:
    RigidBodyComponent(GameObject* _owner);
    ~RigidBodyComponent();
    void SetVelocityZero() { m_vVelocity = { 0.f,0.f }; }
    void SetVelocityXNegative(){m_vVelocity.x*=-1;}    
    void SetVelocityYNegative() { m_vVelocity.y *= -1; }
    void SetGravityNegative() { m_vGravity.y*=-1; }
    void SetVelocity(const AEVec2& _vel)    { m_vVelocity = _vel; }
    void AddVelocity(const AEVec2& _vel)    
    {
        m_vVelocity.x += _vel.x;
        m_vVelocity.y += _vel.y;
    }
    void AddVelocity(float _velX,float _velY)
    {
        m_vVelocity.x += _velX;
        m_vVelocity.y += _velY;
    }
    void Jump(float yPos);
    void Dash(AEVec2 directVec);
    void SetGravity(AEVec2 _g)               { m_vGravity = _g; }
    const AEVec2& GetVelocity()const        { return m_vVelocity; }
    const AEVec2& GetGravity()const          { return m_vGravity; }

    virtual void Update() override;

    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};

