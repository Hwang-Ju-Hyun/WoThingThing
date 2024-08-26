#include "EventManager.h"
#include "header.h"
#include <cassert>
#include "GameObject.h"
#include "TransComponent.h"
#include "RigidBodyComponent.h"

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

void EventManager::AddEntity(Entity* et)
{
	m_listEntity.push_back(et);
}

Entity* EventManager::FindEntity(std::string& str)
{	
	return nullptr;
}

void EventManager::AddEntityList(const std::string& ev_Key, std::list<Entity*>listEntity)
{
	registeredEntities.insert({ ev_Key,listEntity });
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

std::list<Entity*> EventManager::GetEntityList()
{
	return m_listEntity;
}

void EventManager::Update()
{
	//모든 이벤트를 DispatchEvent
	for (auto iter = allEvents.begin(); iter != allEvents.end(); iter++)
	{
		DispatchEvent((*iter)->GetEventName());
	}
	allEvents.clear();
}

void RePosition::OnEvent(Event* ev)
{
	Collision* colEvent = static_cast<Collision*>(ev);

	GameObject* obj1 = colEvent->GetObject1();
	GameObject* obj2 = colEvent->GetObject2();

	TransComponent* obj1_trs = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
	TransComponent* obj2_trs = static_cast<TransComponent*>(obj2->FindComponent("Transform"));

	if (obj1->GetName() == "Ball" || obj2->GetName() == "Ball")
	{
		if (obj1->GetName() == "Player1" || obj2->GetName() == "Player1")
		{
			TransComponent* ball_trs = obj1->GetName() == "Ball" ? obj1_trs : obj2_trs;
			TransComponent* player1_trs = obj1->GetName() == "Player1" ? obj1_trs : obj2_trs;
			
			ball_trs->SetPos(player1_trs->GetPos().x + player1_trs->GetScale().x + ball_trs->GetScale().x / 2.f,ball_trs->GetPos().y);
			RigidBodyComponent* ball_rb = dynamic_cast<RigidBodyComponent*>(ball_trs->GetOwner()->FindComponent("RigidBody"));
			
			if(ball_rb!=nullptr)
				ball_rb->SetVelocityXNegative();
		}
		else if (obj1->GetName() == "Player2" || obj2->GetName() == "Player2")
		{
			TransComponent* ball_trs = obj1->GetName() == "Ball" ? obj1_trs : obj2_trs;
			TransComponent* player2_trs = obj1->GetName() == "Player2" ? obj1_trs : obj2_trs;
			
			ball_trs->SetPos(player2_trs->GetPos().x - player2_trs->GetScale().x - ball_trs->GetScale().x / 2.f,ball_trs->GetPos().y);

			RigidBodyComponent* ball_rb = dynamic_cast<RigidBodyComponent*>(ball_trs->GetOwner()->FindComponent("RigidBody"));
			
			if (ball_rb != nullptr)
				ball_rb->SetVelocityXNegative();
		}
		else if (obj1->GetName() == "UpperPost" || obj2->GetName() == "UpperPost")
		{			
			TransComponent* ball_trs = obj1->GetName() == "Ball" ? obj1_trs : obj2_trs;
			TransComponent* upperPost_trs = obj1->GetName() == "UpperPost" ? obj1_trs : obj2_trs;
			
			ball_trs->SetPos(ball_trs->GetPos().x,upperPost_trs->GetPos().y - upperPost_trs->GetScale().y - 20.f);

			RigidBodyComponent* ball_rb = dynamic_cast<RigidBodyComponent*>(ball_trs->GetOwner()->FindComponent("RigidBody"));
			
			if (ball_rb != nullptr)
				ball_rb->SetVelocityYNegative();
		}		
		else if (obj1->GetName() == "DownPost" || obj2->GetName() == "DownPost")
		{
			TransComponent* ball_trs = obj1->GetName() == "Ball" ? obj1_trs : obj2_trs;
			TransComponent* downPost_trs = obj1->GetName() == "DownPost" ? obj1_trs : obj2_trs;
			
			ball_trs->SetPos(ball_trs->GetPos().x,downPost_trs->GetPos().y + downPost_trs->GetScale().y + 20.f);
			
			RigidBodyComponent* ball_rb = dynamic_cast<RigidBodyComponent*>(ball_trs->GetOwner()->FindComponent("RigidBody"));
			
			if (ball_rb != nullptr)
				ball_rb->SetVelocityYNegative();
		}
		else if (obj1->GetName() == "GoalPost1" || obj2->GetName() == "GoalPost1")
		{
			TransComponent* ball_trs = obj1->GetName() == "Ball" ? obj1_trs : obj2_trs;
			TransComponent* downPost_trs = obj1->GetName() == "GoalPost1" ? obj1_trs : obj2_trs;
			
			ball_trs->SetPos({0.f,0.f});

			RigidBodyComponent* ball_rb = dynamic_cast<RigidBodyComponent*>(ball_trs->GetOwner()->FindComponent("RigidBody"));

			if (ball_rb != nullptr)
				ball_rb->SetVelocityXNegative();
		}
		else if (obj1->GetName() == "GoalPost2" || obj2->GetName() == "GoalPost2")
		{
			TransComponent* ball_trs = obj1->GetName() == "Ball" ? obj1_trs : obj2_trs;
			TransComponent* downPost_trs = obj1->GetName() == "GoalPost2" ? obj1_trs : obj2_trs;

			ball_trs->SetPos({ 0.f,0.f });

			RigidBodyComponent* ball_rb = dynamic_cast<RigidBodyComponent*>(ball_trs->GetOwner()->FindComponent("RigidBody"));

			if (ball_rb != nullptr)
			{
				ball_rb->SetVelocityXNegative();
				ball_rb->SetVelocityYNegative();
			}
		}
	}
}
