#pragma once  

#include "header.h"
class GameObject;

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

struct Collision : public Event
{
public:
	Collision() = delete;
	Collision(GameObject* obj1 = nullptr, GameObject* obj2 = nullptr)
		:m_obj1(obj1)
		,m_obj2(obj2)
	{

	}
	~Collision()
	{

	}
public:
	GameObject* GetObject1() const {return m_obj1;}
	GameObject* GetObject2() const {return m_obj2;}

private:
	GameObject* m_obj1;
	GameObject* m_obj2;
};

class Entity //handle the events
{
public:
	virtual void OnEvent(Event* ev) = 0;
};

class RePosition :public Entity
{
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
	std::list<Entity*> m_listEntity;
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
	void AddEntity(Entity* et);
	Entity* FindEntity(std::string& str);
public:
	void AddEntityList(const std::string& ev_Key, std::list<Entity*>listEntity);
	std::list<Entity*>* FindEntityList(std::string ev_Key);
	// Dispatch All Events		
	void DispatchEvent(std::string ev_Key);

	// delete undispatched events if any on destructor
public:
	std::list<Entity*> GetEntityList();
public:
	void Update();
};