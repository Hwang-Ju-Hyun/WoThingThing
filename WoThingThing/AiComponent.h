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
    GameObject* Player;
public:
    virtual void Update() override;
    void SetState(const std::string& state_name);
    //이 부분 분석
    void SetTarget(GameObject* _player);
    void Setdir(int dir);//dir위치값을 이걸 Player 오브젝트를 넘겨주는것 처럼 dir값도 포인터값으로
    //넘겨주고 세팅해주게 처음에 setdir로 보는 방향을 정할 수 있게 만든다

public:
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};