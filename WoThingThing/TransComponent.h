#pragma once
#include "BaseComponent.h"

class GameObject;

class TransComponent :
    public BaseComponent
{
public:
    TransComponent(GameObject* _owner);
    ~TransComponent();
private:
    AEVec2 m_vPos;
    AEVec2 m_vScale;
    float  m_fRot;
    AEMtx33 m_matMatrix; 
private:
    void CalculateMatrix();
public:
    const AEVec2& GetPos() const        { return m_vPos; };
    const AEVec2& GetScale() const      { return m_vScale; };
    const float& GetRot() const         { return m_fRot; }
    const AEMtx33& GetMatrix() const    { return m_matMatrix; }

    void AddPos(const AEVec2& _pos)
    {
        m_vPos.x += _pos.x;
        m_vPos.y += _pos.y;
    }
    void AddPos(float _posX,float _posY)
    {
        m_vPos.x += _posX;
        m_vPos.y += _posY;
    }
    void SetPos(const AEVec2& _pos)     
    {
        m_vPos = _pos; 
        int a = 0;
    }
    void SetPos(float _posX, float _posY)
    {
        m_vPos.x = _posX;
        m_vPos.y = _posY;
    }
    void SetScale(const AEVec2& _scale) { m_vScale = _scale; }
    void SetRot(const float& _rot)      { m_fRot = _rot; }
public:
    virtual void Update() override;
public:
    static BaseRTTI* CreateTransformComp();
    static constexpr const char* TransformTypeName = "Transform";
public:
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};

