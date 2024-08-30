#include "EventManager.h"
#include "header.h"
#include <cassert>
#include "GameObject.h"
#include "TransComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"

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
	PlayerComponent* obj_player = static_cast<PlayerComponent*>(obj1->FindComponent("PlayerComp"));

	AEVec2 obj1_Pos = obj_trs1->GetPos();
	AEVec2 obj2_Pos = obj_trs2->GetPos();

	AEVec2 obj1_Scale = obj_trs1->GetScale();
	AEVec2 obj2_Scale = obj_trs2->GetScale();
	

	//check 4 distance
	float distanceUpper = std::fabs(obj2_Pos.y+(obj2_Scale.y/2.f) - (obj1_Pos.y-obj1_Scale.y  / 2.f));
	float distanceDown = std::fabs(obj2_Pos.y -(obj2_Scale.y/2.f) - (obj1_Pos.y+ obj1_Scale.y / 2.f));
	//float distanceRight = std::fabs(obj2_Pos.x+(obj2_Scale.x/2.f) - (obj1_Pos.x - obj1_Scale.x / 2.f));
	//float distanceLeft = std::fabs(obj2_Pos.x -(obj2_Scale.x/2.f) - (obj1_Pos.x + obj1_Scale.x / 2.f));	
	
	float distanceRight = FLT_MAX;
	float distanceLeft= FLT_MAX;
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
	std::cout << "FrameCnt: " << AEFrameRateControllerGetFrameCount() << std::endl;
	std::cout << "Player : " <<obj_trs1->GetPos().x << "\t" << obj_trs1->GetPos().y << std::endl;
	std::cout << "Plat   : " << obj_trs2->GetPos().x << "\t" << obj_trs2->GetPos().y << std::endl;
	std::cout << "Dis    : " << minDistance<<"  "<<distArr[0]<< "  " << distArr[1] << std::endl;
	std::cout << "Direct : " << direct << std::endl;
	std::cout << std::endl;

	switch (direct)
	{
	case 0://Upper
		obj_trs1->AddPos({ 0,minDistance});		
		obj_player->SetJumpVelocityZero();
		break;
	case 1://Right
		obj_trs1->AddPos({ minDistance , 0});
		break;
	case 2://Left		
		obj_trs1->AddPos({ -minDistance, 0 });
		break;
	case 3://Down
		obj_trs1->AddPos({ 0,-minDistance});		
		obj_player->SetJumpVelocityZero();		
		break;
	}	

	////Platform UpperCollision
	//if (obj1Bot < obj2Top && obj1Top > obj2Top && obj1Bot > obj2Bot )
	//{
	//	float ReposY = obj2Top + obj1_Scale.y / 2.f;							
	//}	
	//
	////Platform BottomCollision
	//if (obj1Top > obj2Bot && obj1Bot < obj2Bot && obj1Top < obj2Top )
	//{
	//	float ReposY = obj2Bot - obj1_Scale.y / 2.f;					
	//}
	//
	////Platform Right Collision
	//if (obj1Left < obj2Right && obj1Right > obj2Right && obj1Left > obj2Left)
	//{		
	//	float ReposX = obj2Right + obj1_Scale.x / 2.f;			
	//}

	////Platform Left Collision
	//if (obj1Right > obj2Left && obj1Left < obj2Left && obj1Right < obj2Right)
	//{	
	//	float ReposX = obj2Left - obj1_Scale.x / 2.f - 1.f;			
	//}		
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

	
}