#include "GameObject.h"
#include "BaseComponent.h"
#include "CompManager.h"
#include "GoManager.h"

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

}

BaseComponent* GameObject::AddComponent(const std::string& _name, BaseComponent* _comp)
{
    if (_comp == nullptr)
    {
        std::cerr << "AddComponent Error! : component is nullptr" << std::endl;
        return nullptr;
    }
    _comp->m_pOwner = this;
    
    m_mapComp.insert({ _name, _comp });
    
    
    CompManager::GetInst()->AddComponent(_name,_comp);
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
