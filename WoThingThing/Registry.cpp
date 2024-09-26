#include "Registry.h"
#include "SpriteComponent.h"
#include "TransComponent.h"
#include "AnimationComponent.h"
#include "RigidBodyComponent.h"
#include "AiComponent.h"
#include "EnemyAnimationComponent.h"

Registry::Registry()
{
	{
		//Register All the functions
		rttiMap.insert({ "Transform",&TransComponent::CreateTransformComp });
		rttiMap.insert({ "Sprite",&SpriteComponent::CreateSpriteComponent });
		rttiMap.insert({ "EnemyAnimation",&EnemyAnimationComponent::CreateEnemyAnimationComponent });
		rttiMap.insert({ "RigidBody",&RigidBodyComponent::CreateRigidBodyComponent });
		rttiMap.insert({ "Ai",&AiComponent::CreateAiComponent });
	}
}

Registry::~Registry()
{

}

BaseRTTI* Registry::FindAndCreate(const std::string& type)
{
	std::map<std::string, BaseRTTI* (*)()>::iterator iter = rttiMap.find(type);
	if (iter != rttiMap.end())
	{
		if (iter->second == nullptr)
		{	
			return nullptr;
		}
		return iter->second();
	}
	if (iter->second == nullptr)
	{		
		return nullptr;
	}
}