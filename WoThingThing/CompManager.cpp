#include "CompManager.h"
#include "GameObject.h"
#include "BaseComponent.h"

CompManager::CompManager()
{

}

CompManager::~CompManager()
{
	
}

void CompManager::AddComponent(std::string _name, BaseComponent* _comp)
{
	if (_comp == nullptr)
	{
		std::cerr << "AddComponent Error!(CompManger) : new Component is nullptr" << std::endl;
		return;
	}
	//m_mapCompMgr.insert({ _name,_comp });
	_comp->SetName(_name);
	m_vecCompMgr.push_back(_comp );
	//vectorø° ¿˙¿Â
}

void CompManager::RemoveComponent()

{	
	bool IsCompExist = false;
	for (auto iter = m_vecCompMgr.begin(); iter != m_vecCompMgr.end(); iter++)
	{						
		m_vecCompMgr.erase(iter);						
		IsCompExist = true;						
		break;
	}	
	if (!IsCompExist)
	{
		//std::cout << "Can't find Component(RemoveComponent)" << std::endl;
		return;
	}
		
}

BaseComponent* CompManager::FindComponent(std::string name)
{
	/*for (auto iter = m_vecCompMgr.begin(); iter != m_vecCompMgr.end(); iter++)
	{
		if (iter->first == name)
		{
			return iter->second;
		}
	}*/
	std::cerr << "Can't FindComponent : BaseComponent::FindComponent" << std::endl;
	return nullptr;
}

void CompManager::Init()
{

}

void CompManager::Update()
{	
	
	for (auto iter : m_vecCompMgr)
	{
		if (iter)
		{
			iter->Update();
		}
	}
}

void CompManager::Exit()
{		
	m_vecCompMgr.clear();
}

void CompManager::RemoveComponent(const std::string& _objname)
{
	bool IsCompExist = false;
	for (auto iter = m_vecCompMgr.begin(); iter != m_vecCompMgr.end(); iter++)
	{
		if ((*iter)->m_pOwner->GetName() == _objname)
		{
			m_vecCompMgr.erase(iter);
			IsCompExist = true;
			break;
		}
		
	}
	if (!IsCompExist)
	{
		//std::cout << "Can't find Component(RemoveComponent)" << std::endl;
		return;
	}
}
