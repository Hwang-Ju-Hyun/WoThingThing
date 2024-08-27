#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"

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
    const AEVec2& GetPos()        { return m_vPos; }
    const AEVec2& GetScale()      { return m_vScale; }
    const float& GetRot()         { return m_fRot; }
    const AEMtx33& GetMatrix()    { return m_matMatrix; }

    void AddPos(const AEVec2& _pos);
    void AddPos(float _posX, float _posY);
    void SetPos(const AEVec2& _pos);
    void SetPos(float _posX, float _posY);

    void SetScale(const AEVec2& _scale);
    void SetRot(const float& _rot);
    //void SetRot(AEVec2 _rot);
    
public:
    virtual void Update() override;
public:
    static BaseRTTI* CreateTransformComp();
    static constexpr const char* TransformTypeName = "Transform";
public:
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};

