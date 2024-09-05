#include "EventManager.h"
#include "header.h"
#include <cassert>
#include "GameObject.h"
#include "TransComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"
#include"Chase.h"


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
	std::map<std::string /*event�� ���̵�*/, std::list<Entity*>/*�����ڵ�*/>::iterator iter = registeredEntities.find(evt_name);
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

void EventManager::RemoveEntity(const std::string& evt_name, Entity* et)
{
	std::list<Entity*>* list_name = FindEntityList(evt_name);
	if (list_name) 
	{
		//�����ڵ� �߿� et�� ã�Ƽ� ����
		auto it = std::find(list_name->begin(), list_name->end(), et);
		if (it != list_name->end()) {
			// ��� ����
			list_name->erase(it);
		}
	}
}


void EventManager::RemoveAllEvent()
{	
	auto iter = allEvents.begin();
	for (iter; iter != allEvents.end(); iter++)
	{		
		delete *iter;
		*iter = nullptr;
	}	
	allEvents.clear();
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
	if (allEvents.size()<=0)
	{		
		return;
	}
	else
	{
		for (auto iter = listEt->begin(); iter != listEt->end(); iter++)
		{
			(*iter)->OnEvent(ev);
		
		}
	}
}

void EventManager::Update()
{
	//��� �̺�Ʈ�� DispatchEvent
	for (auto iter = allEvents.begin(); iter != allEvents.end(); iter++)
	{
		DispatchEvent(*iter);
		delete (*iter);
	}
	allEvents.clear();
}





void ChasePlatFormSettor::OnEvent(Event* ev)
{
	Enemy_Platform_Collision_Event* e_p_c_e = static_cast<Enemy_Platform_Collision_Event*>(ev);
	if (e_p_c_e->enemy == Enemy_Chase->GetOwner())
	{
		Enemy_Chase->PlatForm = e_p_c_e->platform;
		//EventManager::GetInst()->RemoveEntity("EnemyPlatformCollisionEvent", this);
	}
}

Enemy_Platform_Collision_Event::Enemy_Platform_Collision_Event(GameObject* _platform, GameObject* _enemy)
{
	platform = _platform;
	enemy = _enemy;
	SetEventName("EnemyPlatformCollisionEvent");
}
