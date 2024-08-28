#pragma once
#include "BaseComponent.h"
#include"EnemyStateManager.h"
#include "AEVec2.h"

class GameObject;

class AiComponent : public BaseComponent
{
public:
    AiComponent(GameObject* _owner) : BaseComponent(_owner), e_state_name("E") {} 
    ~AiComponent();
private:
    std::string e_state_name;
    ESM::EnemyStateManager* esm = ESM::EnemyStateManager::GetInst();
public:
    virtual void Update() override;
    void SetState(const std::string& state_name);
public:
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};