#include "BaseComponent.h"

BaseComponent::BaseComponent(GameObject* _owner)
	:m_pOwner(_owner)
{
}

BaseComponent::~BaseComponent()
{
}

GameObject* BaseComponent::GetOwner()
{
	return m_pOwner;
}

void BaseComponent::LoadFromJson(const json& str)
{
}

json BaseComponent::SaveToJson(const json& str)
{
	return json();
}
