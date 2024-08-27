#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"


class GameObject;

class AiComponent : public BaseComponent
{
public:
    AiComponent(GameObject* _owner);
    ~AiComponent();
private:
    std::string e_state_name;

public:
    virtual void Update() override;

};