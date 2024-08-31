#include "GameObject.h"
#include "BaseComponent.h"
#include "MainMenu_Lvl.h"
#include "CompManager.h"
#include "GoManager.h"
#include "GameStateManager.h"

GameObject::GameObject(std::string _name)
    :m_sName(_name)
{
}

GameObject::~GameObject()
{    
    //delete ALL my components
    for (auto iter = m_mapComp.begin(); iter != m_mapComp.end();)
    {
        if (iter->second != nullptr)
        {
            DeleteComponent((iter++)->first);
        }        
        else
        {
            iter++;
        }
    }
    m_mapComp.clear();    
    
    //delete All Object
    GoManager::GetInst()->RemoveDeathObj(); 
}

BaseComponent* GameObject::AddComponent(const std::string& _name, BaseComponent* _comp)
{
    if (_comp == nullptr)
    {
        std::cerr << "AddComponent Error! : component is nullptr" << std::endl;
        return nullptr;
    }
    _comp->m_pOwner = this;
    //들어온 BaseComponent* [Component]의 매개변수는 BaseComponent가 가지고 있는 m_pOwner에 들어온 매개변수를 대입한다.
    
    m_mapComp.insert({ _name, _comp });
    //맵에 저장한다 이름, 컴포넌트의 종류(해당하는 게임 오브젝트)
    //GameObject에 있는 map에도 저장해준다.

    
    CompManager::GetInst()->AddComponent(_name,_comp);
    //컴포넌트 매니저에도 저장해준다
    return _comp;
}

BaseComponent* GameObject::FindComponent(const std::string& _name)
{
    const auto iter = m_mapComp.find(_name);
    if (iter == m_mapComp.end())
    {
        //std::cout << "Can't find Component : GameObject" << std::endl;
        return nullptr;
    }
    return iter->second;
}

//동적으로 component를 추가할 시 지워줘야지
void GameObject::DeleteComponent(const std::string& _name)
{
    auto iter = m_mapComp.find(_name);

    if (iter == m_mapComp.end())
    {
        //std::cout << "DeleteComponent Error(GameObject) : Can't Find BaseComponent in m_mapComp" << std::endl;
        return;
    }
    CompManager::GetInst()->RemoveComponent();
    
    delete iter->second;
    m_mapComp.erase(iter);
}

void GameObject::SetActive(bool sw)
{
    active = sw;
}

bool GameObject::GetActive()
{
    return active;
}
