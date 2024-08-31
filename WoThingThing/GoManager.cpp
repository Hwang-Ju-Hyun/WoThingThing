#include "GoManager.h"
#include "GameObject.h"

GoManager::GoManager()
{

}

GoManager::~GoManager()
{

}

GameObject* GoManager::AddObject(GameObject* _obj)
{       
    m_vecObj.push_back(_obj);
    return _obj;
}

void GoManager::RemoveDeathObj()
{
    for (int i=0; i < m_vecObj.size(); i++)
    {
        if (m_vecObj[i]->GetActive() == false)
        {
            //delete m_vecObj[i];
            m_vecObj.erase(std::find(m_vecObj.begin(), m_vecObj.end(), m_vecObj[i]));
            i--;
        }
    }
}

void GoManager::RemoveAllObj()
{   
    for (auto iter = m_vecObj.begin(); iter != m_vecObj.end();)
    {              
        if (*iter != nullptr)
        {            
            delete *iter;
            iter=m_vecObj.erase(iter);
        }                        
        else
        {
            ++iter;
        }
    }
    m_vecObj.clear();
    //m_vecObj.erase(remove(m_vecObj.begin(), m_vecObj.end(), _obj), m_vecObj.end());
}

//임시코드
void GoManager::RemoveObj(const std::string& _name)
{
    for (int i = 0; i < m_vecObj.size(); i++)
    {
        if (m_vecObj[i]->GetName() == _name)
        {
            delete m_vecObj[i];
            m_vecObj.erase(std::find(m_vecObj.begin(), m_vecObj.end(), m_vecObj[i]));
            i--;
            break;
        }
    }
}

GameObject* GoManager::GetLastObj()
{
    int size = m_vecObj.size();
    if (size == 0)
    {
        std::cerr << "GetLastObj Error! : m_vecObj size is Zero!" << std::endl;
        return nullptr;
    }
    return m_vecObj[size - 1];
}
