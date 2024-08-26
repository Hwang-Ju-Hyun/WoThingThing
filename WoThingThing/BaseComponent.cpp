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
