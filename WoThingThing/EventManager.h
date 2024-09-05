#pragma once  

#include "header.h"
class GameObject;
namespace ESM 
{
	class Chase;
}

struct Event
{
public:
	Event() {}
	virtual ~Event() {}
private:
	std::string name;   //Event ID
	int LocalOrGlobal; // 0 : GlobalEvent   ||    1 : LocalEvent
public:
	void SetLocalOrGlobal(const int& i) { LocalOrGlobal = i; }
	int GetLocalOrGlobal()const { return LocalOrGlobal; }
public:
	void SetEventName(const std::string& str) { name = str; }
	std::string GetEventName()const { return name; }
};
struct Enemy_Platform_Collision_Event:public Event
{
public:
	Enemy_Platform_Collision_Event(GameObject* _platform, GameObject* _enemy);
	GameObject* platform;
	GameObject* enemy;
};


class Entity //handle the events
{
public:
	virtual void OnEvent(Event* ev) = 0;
};



class ChasePlatFormSettor :public Entity 
{
public:
	ESM::Chase* Enemy_Chase;
	virtual void OnEvent(Event* ev)override;
};


#include <list>
#include <map>

class EventManager
{
public:
	SINGLE(EventManager);
private:
	//이벤트들
	std::list<Event*> allEvents;	
	std::map<std::string /*event의 아이디*/, std::list<Entity*>/*구독자들*/> registeredEntities;
public:
	//Interface :
	//Add an event (event*) these are pointers to dynamic memory, called as thee following : AddEvent(new Event)
	void AddEvent(Event* ev);
	Event* FindEvent(std::string& str);
	// templated fn:
	//		Register entities to certain event Type
	//		Unregister entities to certain event Type
public:
	void AddEntity(const std::string& evt_name, Entity* et);
	void RemoveEntity(const std::string& evt_name, Entity* et);
public:
	void RemoveAllEvent();
public:	
	std::list<Entity*>* FindEntityList(std::string ev_Key);
	// Dispatch All Events		
	void DispatchEvent(Event* ev);
	// delete undispatched events if any on destructor
public:
	void Update();
};