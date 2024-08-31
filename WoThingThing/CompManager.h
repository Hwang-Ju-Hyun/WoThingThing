#pragma once
#include "header.h"

class BaseComponent;

using std::pair;

class CompManager
{
	SINGLE(CompManager);
private:
	//std::map<std::string, BaseComponent*> m_mapCompMgr;
	//std::vector<pair<std::string, BaseComponent*>> m_vecCompMgr;

	//I'm using the container vector now, but Is it good choice? 
	//vector? list? queue?
	std::vector<BaseComponent*> m_vecCompMgr;
public:
	void AddComponent(std::string _name,BaseComponent* _comp);
	void RemoveComponent();
	BaseComponent* FindComponent(std::string name);
	const std::vector<BaseComponent*>& AllComp()
	{
		m_vecCompMgr;
		return m_vecCompMgr; 
	}
public:
	void Init();
	void Update();
	void Exit();
public:
	void RemoveComponent(const std::string& _objname);
};

