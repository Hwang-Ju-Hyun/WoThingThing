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
	void HandleCollision(GameObject* obj1, GameObject* obj2);
	virtual void OnEvent(Event* ev)override;
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
	//�̺�Ʈ��
	std::list<Event*> allEvents;	
	std::map<std::string /*event�� ���̵�*/, std::list<Entity*>/*�����ڵ�*/> registeredEntities;
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