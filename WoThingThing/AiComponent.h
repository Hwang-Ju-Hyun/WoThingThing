#pragma once
#include "BaseComponent.h"
#include"EnemyStateManager.h"
#include "AEVec2.h"

class GameObject;

class AiComponent : public BaseComponent
{
public:
    AiComponent(GameObject* _owner) : BaseComponent(_owner), e_state_name("E"), Bullet(nullptr) {}
    ~AiComponent();
private:
    std::string e_state_name;
    std::string e_Categories;
    ESM::EnemyStateManager* esm = ESM::EnemyStateManager::GetInst();
    GameObject* Player;
    GameObject* Bullet;
    float Time_dir = 0;//�������� �ð�
    bool set_dir;
public:
    virtual void Update() override;
    void SetState(const std::string& state_name, const std::string& enemyCategories);
    //�� �κ� �м�
    void SetTarget(GameObject* _player);
    void Setdir(bool dir);//dir��ġ���� �̰� Player ������Ʈ�� �Ѱ��ִ°� ó�� dir���� �����Ͱ�����
    //�Ѱ��ְ� �������ְ� ó���� setdir�� ���� ������ ���� �� �ְ� �����.
    void Setdir_time(float Time);
    void SetSniper_bullet(GameObject* _bullet);

public:
    virtual void LoadFromJson(const json& str)override;
    virtual json SaveToJson()override;
};