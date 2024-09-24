#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"

class GameObject;

#include <list>
class TransComponent :
    public BaseComponent
{
public:
    TransComponent(GameObject* _owner);
    ~TransComponent();
private:
    AEVec2 m_vPos = { 0.f,0.f };
    AEVec2 m_vScale = { 0.f,0.f };
    float  m_fRot=0.f;
    AEMtx33 m_matMatrix; 
public:       
    struct Node
    {
        int node_id=0;
        AEVec2 node_pos = {};         
    };    

private:
    void CalculateMatrix();
public:
    const AEVec2& GetPos()        { return m_vPos; }
    AEVec2& TempGetPos() { return m_vPos; }

    const AEVec2& GetScale()      { return m_vScale; }
    const float& GetRot()         { return m_fRot; }
    const AEMtx33& GetMatrix()    { return m_matMatrix; }
    void AddPos(const AEVec2& _pos);
    void AddPos(float _posX, float _posY);

    void MovePos(float _posX, float _posY, bool active, f32 m_fDt);

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

