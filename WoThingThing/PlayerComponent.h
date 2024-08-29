#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"

class GameObject;

class PlayerComponent : public BaseComponent
{
    AEVec2  m_vVelocity;
    AEVec2  dashVelocity;
    AEVec2  dash_const;
    AEVec2  jumpVelocity;
    AEVec2  m_vGravity;

    AEVec2 mousePos;
    GameObject* mouseAim;
    
    GameObject* melee;


    static int jumpCnt;
    static bool meleeActive, shotActive;
public:
    PlayerComponent(GameObject* _owner);
    ~PlayerComponent() {};



    //About Player's movement
    void Jump(float jumpVal);
    void Dash(AEVec2 directVec);
    void MoveMent();

    //About mouse
    void MouseAim();
    AEVec2 GetMousePos();

    //About Player's attack
    bool GetWeaponType(int n);
    void MeleeAttack();

    //Ȳ���� �ڵ��߰�
    void SetJumpCntZero();    
    void SetJumpVelocityZero();

    virtual void Update() override;
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};