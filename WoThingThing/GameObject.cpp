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
    
}

void GameObject::AddHP(int _hp)
{
    m_hp += _hp;
}

void GameObject::SetHP(int hp)
{
    m_hp = hp;
}

int GameObject::GetHP()
{
    return m_hp;
}

BaseComponent* GameObject::AddComponent(const std::string& _name, BaseComponent* _comp)
{
    if (_comp == nullptr)
    {
        std::cerr << "AddComponent Error! : component is nullptr" << std::endl;
        return nullptr;
    }
    _comp->m_pOwner = this;
    //���� BaseComponent* [Component]�� �Ű������� BaseComponent�� ������ �ִ� m_pOwner�� ���� �Ű������� �����Ѵ�.
    
    m_mapComp.insert({ _name, _comp });
    //�ʿ� �����Ѵ� �̸�, ������Ʈ�� ����(�ش��ϴ� ���� ������Ʈ)
    //GameObject�� �ִ� map���� �������ش�.

    
    CompManager::GetInst()->AddComponent(_name,_comp);
    //������Ʈ �Ŵ������� �������ش�
    return _comp;
}

BaseComponent* GameObject::FindComponent(const std::string& _name)
{
    const auto iter = m_mapComp.find(_name);
    if (iter == m_mapComp.end())
    {
        //
        // << "Can't find Component : GameObject" << std::endl;
        return nullptr;
    }
    return iter->second;
}

//�������� component�� �߰��� �� ���������
void GameObject::DeleteComponent(const std::string& _name)
{
    auto iter = m_mapComp.find(_name);

    if (iter == m_mapComp.end())
    {
        //std::cout << "DeleteComponent Error(GameObject) : Can't Find BaseComponent in m_mapComp" << std::endl;
        return;
    }
    CompManager::GetInst()->RemoveComponent(iter->second);
    
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
