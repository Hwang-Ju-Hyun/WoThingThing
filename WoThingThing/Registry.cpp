#include "Registry.h"
#include "SpriteComponent.h"
#include "TransComponent.h"

Registry::Registry()
{
	{
		//Register All the functions
		rttiMap.insert({ "Transform",&TransComponent::CreateTransformComp });
		rttiMap.insert({ "Sprite",&SpriteComponent::CreateSpriteComponent });
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
			std::cout << "Registry Error : MemberFunction can't found!" << std::endl;
			return nullptr;
		}
		return iter->second();
	}
	if (iter->second == nullptr)
	{
		std::cout << "Registry Error : Constructor can't found!" << std::endl;
		return nullptr;
	}
}