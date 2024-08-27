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

	float obj1Right    = obj1_Pos.x + obj1_Scale.x/2.f;
	float obj1Left     = obj1_Pos.x - obj1_Scale.x /2.f;
	float obj1Top      = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1Bot      = obj1_Pos.y + obj1_Scale.y / 2.f;
	
	float obj2Right	   = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2Left 	   = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY     = obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2BotY     = obj2_Pos.y + obj2_Scale.y / 2.f;

	if (obj1Right<obj2Left || obj1Left>obj2Right || obj1Bot<obj2TopY || obj1Top>obj2BotY)
		return false;
	return true;
	/*if (obj1Right > obj2Left &&
		obj2Right > obj1Left &&
		obj1Top<obj2BotY &&
		obj2TopY<obj1Bot)
	{
		return true;
	}

	return false;*/
}