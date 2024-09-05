#pragma once
#include "BaseComponent.h"
#include"EnemyStateManager.h"
#include "AEVec2.h"

class GameObject;

class AiComponent : public BaseComponent
{
public:
    AiComponent(GameObject* _owner);
    ~AiComponent();
private:
    std::string e_state_name;
    std::string e_Categories;
    ESM::EnemyStateManager* esm;
    GameObject* Player;
    GameObject* PlatForm = nullptr;
    AEVec2 FirstPlacePos;
    float Time_dir = 0;//고개돌리는 시간
    bool set_dir;
public:
    virtual void Update() override;
    void SetState(const std::string& state_name, const std::string& enemyCategories);
    //이 부분 분석
    void SetTarget(GameObject* _player);
    void Setdir(bool dir);//dir위치값을 이걸 Player 오브젝트를 넘겨주는것 처럼 dir값도 포인터값으로
    //넘겨주고 세팅해주게 처음에 setdir로 보는 방향을 정할 수 있게 만든다.
    void Setdir_time(float Time);
    void Change_State(ESM::BaseEnemyState* newstate);
    void SetPlatform(GameObject* platform);
    void SetFirstPlace(AEVec2 _FirstPlacePos);

public:
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};