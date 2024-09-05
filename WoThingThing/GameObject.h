#pragma once
#include "header.h"

class BaseComponent;

class GameObject
{
	bool active{ true };

public:
	GameObject() = delete;
	GameObject(std::string _name);
	~GameObject();
private:
	int m_id;
public:
	void SetID(int id) { m_id = id; }
	int GetID() { return m_id; }
private:
	std::string m_sName;	
public:
	void SetName(const std::string& _name) { m_sName = _name; }
	const std::string& GetName()const { return m_sName; }
private:
	std::map<std::string, BaseComponent*> m_mapComp;
public:
	BaseComponent* AddComponent(const std::string& _name, BaseComponent* _comp);
	BaseComponent* FindComponent(const std::string& _name);	
	void DeleteComponent(const std::string& _name);

	void SetActive(bool sw);
	bool GetActive();

public:
	std::map<std::string, BaseComponent*> GetAllComp()
	{
		return m_mapComp;
	}

//Node Info
private:
	int m_nodeCost;
	int m_nodeID;
public:
	void SetNodeCost(int _cost) { m_nodeCost = _cost; }
	int GetNodeCost()const		{ return m_nodeCost; }
public:
	friend class BaseComponent;
};

