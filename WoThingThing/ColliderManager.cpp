#include "ColliderManager.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransComponent.h"

ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{

}

bool ColliderManager::IsCollision(GameObject* _obj1, GameObject* _obj2)
{
	BaseComponent* obj_trs1 = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 obj1_Pos = static_cast<TransComponent*>(obj_trs1)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();
	
	AEVec2 obj1_Scale = static_cast<TransComponent*>(obj_trs1)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj1RightX = obj1_Pos.x + obj1_Scale.x/2.f;
	float obj1LeftX  = obj1_Pos.x - obj1_Scale.x /2.f;
	float obj1TopY   = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1BotY   = obj1_Pos.y + obj1_Scale.y / 2.f;
	
	float obj2RightX	= obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2LeftX 	= obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY  	= obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2BotY  	= obj2_Pos.y + obj2_Scale.y / 2.f;

	if (obj1RightX > obj2LeftX &&
		obj2RightX > obj1LeftX &&
		obj1TopY<obj2BotY &&
		obj2TopY<obj1BotY)
	{
		return true;
	}

	return false;
}