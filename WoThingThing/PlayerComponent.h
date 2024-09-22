#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"
#include <vector>

class GameObject;

class PlayerComponent : public BaseComponent
{
    //Player movement
    AEVec2  m_vVelocity;

    AEVec2  dashVelocity;
    AEVec2  dash_const;

    AEVec2  jumpVelocity;
    AEVec2  m_vGravity;

    //About mouse
    AEVec2 mousePos;
    GameObject* mouseAim;
    GameObject* aim_line;

    AEVec2 norVec;

    GameObject* melee;
    bool meleeState;
    f32 meleeCooldown;
    GameObject* gauge;

    int jumpCnt;
    bool meleeAction, shotAction, obtainGun;

    bool manipulActive;
    f32 timeManipul;
    int playerhealth;
    float maniCapacity;
    float AccTime=0.f;

    bool invincibility;
public:
    PlayerComponent(GameObject* _owner);
    ~PlayerComponent() {};

    //About Player's movement
    void Jump(float jumpVal);
    void Dash(AEVec2 directVec);
    void MoveMent();
    bool GetManiActive();

    bool GetInvincible();
    void SetInvincible(bool sw);
    ///////////////////////////

    //About mouse
    void MouseAim();
    void DrawAim();
    void MouseTraceLine();
    AEVec2 GetMousePos();
    ///////////////////////

    //About Player's attack
    void Attack();
    GameObject* GetMelee();
    bool GetObtain();
    void SetObtain();
    bool GetMeleeAction();
    bool GetMeleeState();
    bool GetShotAction();
    ////////////////////////

    void SetNorVec(AEVec2 norV);
    AEVec2 GetNorVec();


    //황주현 코드추가
    void SetJumpCntZero();    
    void SetJumpVelocityZero();
    int GetHealth();
    void SetHealth(float _health)
    {
        playerhealth = _health;
    }

    void TakeDamge();
    bool IsAlive();
    void Gauge();

    virtual void Update() override;
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;

};