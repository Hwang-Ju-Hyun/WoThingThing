#include "EventManager.h"
#include "header.h"
#include <cassert>
#include "GameObject.h"
#include "TransComponent.h"
#include "RigidBodyComponent.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
EventManager::EventManager()
{

}
EventManager::~EventManager()
{

}

void EventManager::AddEvent(Event* ev)
{
	allEvents.push_back(ev);
}


void EventManager::AddEntity(const std::string& evt_name, Entity* et)
{
	std::map<std::string /*event의 아이디*/, std::list<Entity*>/*구독자들*/>::iterator iter = registeredEntities.find(evt_name);
	if (iter != registeredEntities.end())
	{
		std::list<Entity*>& subscribers = iter->second;
		subscribers.push_back(et);
	}
	else
	{
		std::list<Entity*> newPerson;
		newPerson.push_back(et);
		registeredEntities.insert({ evt_name,newPerson });
	}
}

std::list<Entity*>* EventManager::FindEntityList(std::string ev_Key)
{
	auto listEntity = registeredEntities.find(ev_Key);
	if (listEntity == registeredEntities.end())
		return nullptr;
	return &(listEntity->second);		
}

void EventManager::DispatchEvent(Event* ev)
{	
	if (ev == nullptr)
		return;

	std::list<Entity*>* listEt = FindEntityList(ev->GetEventName());

	if (listEt == nullptr)
		return;

	for (auto iter = listEt->begin(); iter != listEt->end(); iter++)
	{
		(*iter)->OnEvent(ev);
	}
}

void EventManager::Update()
{
	//모든 이벤트를 DispatchEvent
	for (auto iter = allEvents.begin(); iter != allEvents.end(); iter++)
	{
		DispatchEvent(*iter);
		delete (*iter);
	}
	allEvents.clear();
}



void RePosition::HandleCollision(GameObject* obj1, GameObject* obj2)
{
	// Transform 및 RigidBody 컴포넌트 가져오기
	TransComponent* obj_trs1 = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
	TransComponent* obj_trs2 = static_cast<TransComponent*>(obj2->FindComponent("Transform"));
	RigidBodyComponent* obj_rb1 = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));

	AEVec2 obj1_Pos = obj_trs1->GetPos();
	AEVec2 obj2_Pos = obj_trs2->GetPos();

	AEVec2 obj1_Scale = obj_trs1->GetScale();
	AEVec2 obj2_Scale = obj_trs2->GetScale();

	float obj1RightX = obj1_Pos.x + obj1_Scale.x / 2.f;
	float obj1LeftX = obj1_Pos.x - obj1_Scale.x / 2.f;
	float obj1Bot = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1Top = obj1_Pos.y + obj1_Scale.y / 2.f;

	float obj2RightX = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2LeftX = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2Bot = obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2Top = obj2_Pos.y + obj2_Scale.y / 2.f;

	// 충돌 방향 플래그
	bool rightflag = false;
	bool leftflag = false;
	bool botflag = false;
	bool topflag = false;


	// 모서리 충돌 조건
	bool nearLeftEdge = obj1RightX < obj2LeftX + obj2_Scale.x * 0.01f;  // obj1이 obj2의 좌측 모서리 근처에 있는가?
	bool nearRightEdge = obj1LeftX > obj2RightX - obj2_Scale.x * 0.01f; // obj1이 obj2의 우측 모서리 근처에 있는가?
	bool nearTopEdge = obj1Bot > obj2Top - obj2_Scale.y * 0.1f;
	bool nearBotEdge = obj1Top < obj2Bot + obj2_Scale.y * 0.1f;


	// 윗면 충돌: obj1이 obj2의 윗면에 부딪힘
	if (obj1Bot < obj2Top && obj1Top > obj2Top && obj1Bot > obj2Bot && !nearLeftEdge && !nearRightEdge)
	{
		float ReposY = obj2Top + obj1_Scale.y / 2.f;
		obj_trs1->SetPos({ obj1_Pos.x, ReposY });				
		// 속도 0으로 설정하여 멈추게 함				
	}	
	// 아랫면 충돌: obj1이 obj2의 아랫면에 부딪힘
	if (obj1Top > obj2Bot && obj1Bot < obj2Bot && obj1Top < obj2Top && !nearLeftEdge && !nearRightEdge)
	{
		float ReposY = obj2Bot - obj1_Scale.y / 2.f;
		obj_trs1->SetPos({ obj1_Pos.x, ReposY });	
		// 속도를 중력 방향으로 설정할 수 있음		
	}
	// 오른쪽 충돌: obj1이 obj2의 오른쪽에 부딪힘
	if (obj1LeftX < obj2RightX && obj1RightX > obj2RightX && obj1LeftX > obj2LeftX)
	{
		rightflag = true;
		float ReposX = obj2RightX + obj1_Scale.x / 2.f + 1.f;		
		obj_trs1->SetPos({ ReposX, obj1_Pos.y });				
	}
	// 왼쪽 충돌: obj1이 obj2의 왼쪽에 부딪힘
	if (obj1RightX > obj2LeftX && obj1LeftX < obj2LeftX && obj1RightX < obj2RightX)
	{
		leftflag = true;
		float ReposX = obj2LeftX - obj1_Scale.x / 2.f - 1.f;
		obj_trs1->SetPos({ ReposX, obj1_Pos.y});				
	}
	

	
}

void RePosition::OnEvent(Event* ev)
{
	Collision* colEvent = static_cast<Collision*>(ev);

	GameObject* obj1 = colEvent->GetObject1();
	GameObject* obj2 = colEvent->GetObject2();

	TransComponent* obj1_trs = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
	TransComponent* obj2_trs = static_cast<TransComponent*>(obj2->FindComponent("Transform"));

	if (obj1->GetName() == "Player" && obj2->GetName() == "Platform")
	{
		HandleCollision(obj1, obj2);
	}

	//if (obj1->GetName() == "Platform" || obj2->GetName() == "Platform")
	//{
	//	if (obj1->GetName() == "Player" || obj2->GetName() == "Player")
	//	{

	//		
	//		TransComponent* Platform_trs = obj1->GetName() == "Platform" ? obj1_trs : obj2_trs;
	//		TransComponent* player_trs = obj1->GetName() == "Player" ? obj1_trs : obj2_trs;
	//		
	//		Platform_trs->SetPos(player_trs->GetPos().x + Platform_trs->GetScale().x + Platform_trs->GetScale().x / 2.f, Platform_trs->GetPos().y);		
	//	}		
	//}
}