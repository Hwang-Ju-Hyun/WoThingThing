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
			//std::cerr << "AddComponent Error!(CompManger) : new Component is nullptr" << std::endl;
			return;
		}
		//m_mapCompMgr.insert({ _name,_comp });
		_comp->SetName(_name);
		m_vecCompMgr.push_back(_comp );
	//vectorø° ¿˙¿Â
}

//void CompManager::RemoveComponent()
//
//{	
//	bool IsCompExist = false;
//	for (auto iter = m_vecCompMgr.begin(); iter != m_vecCompMgr.end(); iter++)
//	{						
//		m_vecCompMgr.erase(iter);						
//		IsCompExist = true;						
//		break;
//	}	
//	if (!IsCompExist)
//	{
//		//std::
// << "Can't find Component(RemoveComponent)" << std::endl;
//		return;
//	}
//		
//}

void CompManager::RemoveComponent(BaseComponent* _comp)
{	
	bool IsCompExist = false;
	for (auto iter = m_vecCompMgr.begin(); iter != m_vecCompMgr.end(); iter++)
	{
		if (*iter == _comp)
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
	std::vector<BaseComponent*> m_vecCopyCompMgr = m_vecCompMgr;

	for (auto iter : m_vecCopyCompMgr)
	{
		//std::cout << m_vecCompMgr.size() << std::endl;
		if (iter)
		{
			iter->Update();
		}
		//std::cout << m_vecCompMgr.size() << std::endl;
	}
	
}

void CompManager::Exit()
{		
	m_vecCompMgr.clear();
}

