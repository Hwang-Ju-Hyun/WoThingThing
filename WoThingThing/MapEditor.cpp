#include "MapEditor.h"
#include "GameStateManager.h"
#include "Serializer.h"
#include "MainMenu_Lvl.h"
#include <fstream>
#include "GameObject.h"
#include "GoManager.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "json.hpp"
#include "CameraManager.h"
#include "BaseRTTI.h"
#include "BaseComponent.h"
#include "ColliderManager.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"

Level::MapEditor::MapEditor()
{

}

Level::MapEditor::~MapEditor()
{

}

void Level::MapEditor::Init()
{

	player = new GameObject("Player");
	GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
	player->AddComponent("Transform", new TransComponent(player));
	player->AddComponent("Sprite", new SpriteComponent(player));
	player->AddComponent("PlayerComp", new PlayerComponent(player));
	

	CameraManager::GetInst()->SetMouse(mouseAim);
	CameraManager::GetInst()->SetPlayer(player);
	CameraManager::GetInst()->SetAim(aimTrace);

	file.open("stage01.json", std::fstream::in);
	if (!file.is_open())
	{
		return;
	}
	Serializer::GetInst()->LoadLevel("stage01.json");	

		
	player->AddComponent("Transform", new TransComponent(player));
	player->AddComponent("Sprite", new SpriteComponent(player));
	player->AddComponent("PlayerComp", new PlayerComponent(player));
}


void Level::MapEditor::Update()
{
	AEInputGetCursorPosition(&mouseX, &mouseY);			

	TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
	SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
	RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
	PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");


	const int NumberofTile = 20;

	goTileW = 1600 / 20;
	goTileH = 900 / 20;

	
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();
	grid_X = (mouseX)/ goTileW;
	grid_Y = (mouseY)/ goTileH;

	goPosX = grid_X * goTileW;
	goPosY = grid_Y * goTileH;			

	int goScaleX = goTileW;
	int goScaleY = goTileH;

	for (auto obj : GoManager::GetInst()->Allobj())
	{
		if (obj->GetName() == "Platform")
		{
			if (ColliderManager::GetInst()->IsCollision(player, obj))
			{
				HandleCollision(player, obj);
			}
		}
	}
		
	/*if (AEInputCheckCurr(AEVK_RBUTTON))
	{
		auto vecObj = GoManager::GetInst()->Allobj();
		bool createObj = false;		
		go = new GameObject("Platform");
		GoManager::GetInst()->AddObject(go);
		go->AddComponent("Transform", new TransComponent(go));
		go->AddComponent("Sprite", new SpriteComponent(go));
		TransComponent* go_trs = static_cast<TransComponent*>(go->FindComponent("Transform"));
		SpriteComponent* go_spr = static_cast<SpriteComponent*>(go->FindComponent("Sprite"));		
		go_trs->SetPos({ float(goPosX + player_Cam.x),float(goPosY + player_Cam.y) });
		go_trs->SetScale({ float(goScaleX),float(goScaleY) });
		grid[grid_X][grid_Y] = true;

		std::cout << goPosX << "," << goPosY << std::endl;

		go_spr->m_color.red = 255;
		go_spr->m_color.blue = 0;
		go_spr->m_color.green = 0;
		else if (AEInputCheckCurr(AEVK_RBUTTON) && AEInputCheckCurr(AEVK_1))
		{			
		}
		else
		{
			std::cout << "이미 뒀음" << std::endl;
		}
	}*/
	/*auto b = GoManager::GetInst()->Allobj();
	b.size();
	for (auto obj : GoManager::GetInst()->Allobj())
	{
		if (obj->GetName() == "Platform")
		{
			if (ColliderManager::GetInst()->IsCollision(player, obj))
			{
				HandleCollision(player, obj);
			}
		}
	}*/
	
	
	if (AEInputCheckCurr(AEVK_RETURN))
	{
		json AllData;
		//Counter instead of name as I do not have one
		int i = 0;
		for (GameObject* go : GoManager::GetInst()->Allobj())
		{
			auto aa = GoManager::GetInst()->Allobj();
			aa.size();
			json components;
			if (go->GetName() == "Platform")
			{
				json obj;
				obj["Platform"] = i++;
				for (auto c : go->GetAllComp())//map
				{
					BaseComponent* comp = c.second;
					components.push_back(comp->SaveToJson());//Check in a moment			
				}
				obj["Components"] = components;
				AllData.push_back(obj);
			}
		}
		std::fstream file;
		file.open("stage01.json", std::fstream::out);//Open as write mode. Create it if it does not exist!

		if (!file.is_open())
		{
			int a = 0;
			//Print error
			//return
		}

		//file << AllData; //All in 1 line
		file << std::setw(2) << AllData;

		file.close();
	}
	CameraManager::GetInst()->Update();
	if (AEInputCheckCurr(AEVK_B))
	{		
		Serializer::GetInst()->SaveLevel("stage01.json");
		GSM::GameStateManager::GetInst()->ChangeLevel(new Level::MainMenu_Lvl);
	}

	
}

void Level::MapEditor::Exit()
{	
	GoManager::GetInst()->RemoveAllObj();
}

void Level::MapEditor::HandleCollision(GameObject* obj1, GameObject* obj2)
{
	// Transform 및 RigidBody 컴포넌트 가져오기
	TransComponent* obj_trs1 = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
	TransComponent* obj_trs2 = static_cast<TransComponent*>(obj2->FindComponent("Transform"));


	AEVec2 obj1_Pos = obj_trs1->GetPos();
	AEVec2 obj2_Pos = obj_trs2->GetPos();

	AEVec2 obj1_Scale = obj_trs1->GetScale();
	AEVec2 obj2_Scale = obj_trs2->GetScale();

	//RigidBodyComponent* obj_rb1 = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));
	if (obj1->GetName() == "Enemy" || obj1->GetName() == "Enemy_TEST")
	{
		RigidBodyComponent* obj_rb1 = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));
		//check 4 distance
		float distanceUpper = std::fabs(obj2_Pos.y + (obj2_Scale.y / 2.f) - (obj1_Pos.y - obj1_Scale.y / 2.f));
		float distanceDown = std::fabs(obj2_Pos.y - (obj2_Scale.y / 2.f) - (obj1_Pos.y + obj1_Scale.y / 2.f));
		float distanceRight = std::fabs(obj2_Pos.x + (obj2_Scale.x / 2.f) - (obj1_Pos.x - obj1_Scale.x / 2.f));
		float distanceLeft = std::fabs(obj2_Pos.x - (obj2_Scale.x / 2.f) - (obj1_Pos.x + obj1_Scale.x / 2.f));


		float distArr[4] = { distanceUpper,distanceRight,distanceLeft,distanceDown };
		float minDistance = distArr[0];
		int direct = 0;
		for (int i = 1; i < 4; i++)
		{
			if (minDistance > distArr[i])
			{
				minDistance = distArr[i];
				direct = i;
			}
		}


		switch (direct)
		{
		case 0://Upper
			obj_trs1->AddPos({ 0,minDistance });
			obj_rb1->SetJumpVelocityZero();
			//obj_rb1->SetJumpCntZero();
			break;
		case 1://Right
			obj_trs1->AddPos({ minDistance , 0 });
			break;
		case 2://Left		
			obj_trs1->AddPos({ -minDistance, 0 });
			break;
		case 3://Down
			obj_trs1->AddPos({ 0,-minDistance });
			obj_rb1->SetJumpVelocityZero();
			break;
		}
	}
	else
	{
		PlayerComponent* obj_player = static_cast<PlayerComponent*>(obj1->FindComponent("PlayerComp"));

		//check 4 distance
		float distanceUpper = std::fabs(obj2_Pos.y + (obj2_Scale.y / 2.f) - (obj1_Pos.y - obj1_Scale.y / 2.f));
		float distanceDown = std::fabs(obj2_Pos.y - (obj2_Scale.y / 2.f) - (obj1_Pos.y + obj1_Scale.y / 2.f));
		float distanceRight = std::fabs(obj2_Pos.x + (obj2_Scale.x / 2.f) - (obj1_Pos.x - obj1_Scale.x / 2.f));
		float distanceLeft = std::fabs(obj2_Pos.x - (obj2_Scale.x / 2.f) - (obj1_Pos.x + obj1_Scale.x / 2.f));


		float distArr[4] = { distanceUpper,distanceRight,distanceLeft,distanceDown };
		float minDistance = distArr[0];
		int direct = 0;
		for (int i = 1; i < 4; i++)
		{
			if (minDistance > distArr[i])
			{
				minDistance = distArr[i];
				direct = i;
			}
		}

		switch (direct)
		{
		case 0://Upper
			obj_trs1->AddPos({ 0,minDistance });
			obj_player->SetJumpVelocityZero();
			obj_player->SetJumpCntZero();
			break;
		case 1://Right
			obj_trs1->AddPos({ minDistance , 0 });
			break;
		case 2://Left		
			obj_trs1->AddPos({ -minDistance, 0 });
			break;
		case 3://Down
			obj_trs1->AddPos({ 0,-minDistance });
			obj_player->SetJumpVelocityZero();
			break;
		}

	}

}

int Level::MapEditor::GameObject_MouseIn(GameObject* obj)
{
	{
		// 현재 카메라 위치를 가져옵니다.
		AEVec2 cameraPos = CameraManager::GetInst()->GetLookAt();

		// 월드 좌표에서 마우스 위치를 가져옵니다.		

		// 카메라 위치를 고려하여 월드 좌표에서 마우스 위치를 조정합니다.
		float adjustedMouseX = mouseX - cameraPos.x;
		float adjustedMouseY = mouseY - cameraPos.y;

		// 게임 객체의 위치와 크기를 가져옵니다.
		TransComponent* objTrans = static_cast<TransComponent*>(obj->FindComponent("Transform"));
		AEVec2 objPos = objTrans->GetPos();
		AEVec2 objScale = objTrans->GetScale();

		// 객체의 경계를 계산합니다.
		float minX = objPos.x - objScale.x / 2;
		float maxX = objPos.x + objScale.x / 2;
		float minY = objPos.y - objScale.y / 2;
		float maxY = objPos.y + objScale.y / 2;

		// 마우스가 객체의 경계 내에 있는지 확인합니다.
		if (adjustedMouseX < minX || adjustedMouseX > maxX || adjustedMouseY < minY || adjustedMouseY > maxY)
		{
			return 0; // 마우스가 객체 밖에 있음
		}

		return 1; // 마우스가 객체 안에 있음
	}
}
