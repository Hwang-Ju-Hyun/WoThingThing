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

Event* EventManager::FindEvent(std::string& str)
{
	std::list<Event*>::iterator iter;
	for (iter = allEvents.begin(); iter != allEvents.end(); iter++)
	{
		if ((*iter)->GetEventName() == str)
		{
			return (*iter);
		}
	}
	return nullptr;
}

void EventManager::AddEntity(const std::string& evt_name,Entity* et)
{
	std::map<std::string /*event의 아이디*/, std::list<Entity*>/*구독자들*/>::iterator iter= registeredEntities.find(evt_name);
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
	for (auto iter = registeredEntities.begin(); iter != registeredEntities.end(); iter++)
	{
		if ((*iter).first == ev_Key)
		{
			return &(*iter).second;
		}
	}
	return nullptr;
}

void EventManager::DispatchEvent(std::string ev_Key)
{
	Event* ev = FindEvent(ev_Key);
	if (ev == nullptr)
		return;

	std::list<Entity*>* listEt = FindEntityList(ev_Key);

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
		DispatchEvent((*iter)->GetEventName());
		delete (*iter);
	}	
	allEvents.clear();
}



void RePosition::HandleCollision(GameObject* obj1, GameObject* obj2)
{

	TransComponent* obj_trs1 = static_cast<TransComponent*>(obj1->FindComponent("Transform"));//Player
	TransComponent* obj_trs2 = static_cast<TransComponent*>(obj2->FindComponent("Transform"));//Platform
	RigidBodyComponent* obj_rb1 = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));
	AEVec2 obj1_Pos = static_cast<TransComponent*>(obj_trs1)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 obj1_Scale = static_cast<TransComponent*>(obj_trs1)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj1RightX = obj1_Pos.x + obj1_Scale.x / 2.f;
	float obj1LeftX = obj1_Pos.x - obj1_Scale.x / 2.f;
	float obj1Bot = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1Top = obj1_Pos.y + obj1_Scale.y / 2.f;

	float obj2RightX = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2LeftX = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2Bot = obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2Top = obj2_Pos.y + obj2_Scale.y / 2.f;


	bool rightflag = false;
	bool leftflag = false;
	bool botflag = false;
	bool topflag = false;
	//플레이어가 플랫폼의 오른쪽을 충돌 
	if (obj1LeftX < obj2RightX&&
		obj1RightX>obj2RightX&&
		obj1LeftX>obj2LeftX)
	{		
		rightflag = true;
		float ReposX = obj2RightX+obj_trs1->GetScale().x/2.f+1.f ;
		//float ReposX = obj2RightX  + obj_trs1->GetScale().x / 2.f;
		obj_trs1->SetPos({ ReposX,obj_trs1->GetPos().y});		
	}

	//플레이어가 플랫폼의 윗면을 충돌
 	else if (obj1Bot < obj2Top&&
		obj1Top>obj2Top&&
		obj1Bot>obj2Bot)
	{
		topflag = true;
		float ReposY = obj2Top + obj_trs1->GetScale().y / 2.f;		
		obj_trs1->SetPos({obj_trs1->GetPos().x,ReposY});
		obj_rb1->SetVelocity({ 0.f, 0.f });		
	}
		

	//플레이어가 플랫폼의 아랫면을 충돌
	else if (obj1Top > obj2Top&&
			obj1Bot<obj2Bot)
	{
		botflag = true;
		float ReposY = obj2Bot - obj_trs1->GetScale().y / 2.f;		
		obj_trs1->SetPosY(ReposY);				
	}

	//플레이어가 플랫폼의 Left을 충돌 <-Hangul Andem tlqk
	else if (obj1RightX > obj2LeftX&&
		obj1LeftX<obj2LeftX&&
		obj1RightX<obj2RightX)
	{
		leftflag = true;
		float ReposX =obj2LeftX - obj_trs1->GetScale().x / 2.f;		
		obj_trs1->SetPos({ ReposX,obj_trs1->GetPos().y });		
	}
	
	if()
}

void RePosition::OnEvent(Event* ev)
{
	Collision* colEvent = static_cast<Collision*>(ev);

	GameObject* obj1 = colEvent->GetObject1();
	GameObject* obj2 = colEvent->GetObject2();

	TransComponent* obj1_trs = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
	TransComponent* obj2_trs = static_cast<TransComponent*>(obj2->FindComponent("Transform"));

	if (obj1->GetName() == "Player"&&obj2->GetName()=="Platform")
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

