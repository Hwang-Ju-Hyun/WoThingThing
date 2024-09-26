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
    bool IsTriggeredButton=false;
    bool invincibility;

    bool IsTutorialStage = false;
    bool IsMovementTutorial = false;
    bool IsTimeManipulateTutorial = false;
    bool IsAttackTutorial = false;    
    bool DoNotMove = false;
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
    void SetHealth(int _health)
    {
        playerhealth = _health;
    }
    void SetTriggeredButton(bool _tri) { IsTriggeredButton = _tri; }
    bool GetTriggeredButton() { return IsTriggeredButton; }

    void TakeDamge();
    bool IsAlive();
    void Gauge();
public:
    void SetIsTutorialStage(bool _IsTutorialStage) { IsTutorialStage = _IsTutorialStage; }
    const bool GetIsTutorialStage() { return IsMovementTutorial; }

    void SetIsMovementTutorial(bool _MoveTutorial) { IsMovementTutorial = _MoveTutorial; }
    const bool GetIsMovementTutorial() { return IsMovementTutorial; }

    void SetIsTimeManipulateTutorial(bool _timeTutorial) { IsTimeManipulateTutorial = _timeTutorial; }
    const bool GetIsTimeManipulateTutoria() { return IsTimeManipulateTutorial; }

    void SetIsAttackTutorial(bool _atkTutorial) { IsAttackTutorial = _atkTutorial; }
    const bool GetIsAttackTutorial() { return IsAttackTutorial; }

    void SetDoNotMove(bool _move) { DoNotMove = _move; }
    const bool GetDoNotMove() { return DoNotMove; }

    void SetManipulate(bool _mani) { manipulActive=_mani; }
    const bool GetManipulate() { return manipulActive; }
public:
    virtual void Update() override;
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson(const json& str)override;

};