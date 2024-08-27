#include "ColliderManager.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include"TestLevel.h"//일단 테스트용

ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{

}
//나중에 여기 부분 건들기
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

bool ColliderManager::PlayerSearch(GameObject* _obj1, GameObject* _obj2)
{
	BaseComponent* enemy_trs = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 enemy_Pos = static_cast<TransComponent*>(enemy_trs)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 enemy_Scale = static_cast<TransComponent*>(enemy_trs)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj2RightX = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2LeftX = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y + obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y - obj2_Scale.y / 2.f;

	//영역의 좌표(정사각형 기준)
	if (Level::TestLevel::enemy_dir == 0) //보는 방향에 따른 영역 변환
	{
		float Search_LeftArea_X = enemy_Pos.x - enemy_Scale.x; //왼쪽 방향으로 가고 있을 때
		float L_SearchPlayer_RightX = Search_LeftArea_X + enemy_Scale.x / 2.f;
		float L_SearchPlayer_LeftX = Search_LeftArea_X - 16.f * (enemy_Scale.x / 2.f);//x축 범위
		float L_SearchPlayer_TopY = enemy_Pos.y + 8.f * (enemy_Scale.y / 2.f);//y축 범위
		float L_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;

		if (L_SearchPlayer_LeftX < obj2_Pos.x &&
			L_SearchPlayer_RightX > obj2_Pos.x &&
			L_SearchPlayer_BotY < obj2_Pos.y &&
			L_SearchPlayer_TopY > obj2_Pos.y)
		{
			std::cout << "SearchPlayerLeft" << std::endl;
			return true;
		}

	}
	else if (Level::TestLevel::enemy_dir == 1)
	{
		float Search_RightArea_X = enemy_Pos.x + enemy_Scale.x;//오른쪽 방향으로 가고 있을 때
		float R_SearchPlayer_LeftX = Search_RightArea_X - enemy_Scale.x / 2.f;
		float R_SearchPlayer_RightX = Search_RightArea_X + 10.f * (enemy_Scale.x / 2.f);
		float R_SearchPlayer_TopY = enemy_Pos.y + 10.f * (enemy_Scale.y / 2.f);
		float R_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;

		if (R_SearchPlayer_LeftX < obj2_Pos.x &&
			R_SearchPlayer_RightX > obj2_Pos.x &&
			R_SearchPlayer_BotY < obj2_Pos.y &&
			R_SearchPlayer_TopY > obj2_Pos.y)
		{
			std::cout << "SearchPlayerRight" << std::endl;
			return true;
		}
	}
	return false;
}
