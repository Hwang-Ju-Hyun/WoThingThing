#include "GameStateManager.h"
#include "BaseLevel.h"
#include "MainMenu_Lvl.h"

GSM::GameStateManager::GameStateManager()
	:m_pPreviousLevel(nullptr)
	, m_pCurrentLevel(nullptr)
{

}

GSM::GameStateManager::~GameStateManager()
{
	if (m_pPreviousLevel)
		delete m_pPreviousLevel;
	if (m_pCurrentLevel)
		delete m_pCurrentLevel;
}

void GSM::GameStateManager::Init()	
{
	if (m_pCurrentLevel == nullptr)
	{
		#ifdef DEBUG
			std::cerr << "GSM Init Error! : CurrentLevel is nullptr" << std::endl;			
		#endif 		
		return;
	}
	m_pCurrentLevel->Init();
}

void GSM::GameStateManager::Update()
{
	if (m_pCurrentLevel == nullptr)
	{
		#ifdef DEBUG
			std::cerr << "GSM Update Error! : CurrentLevel is nullptr" << std::endl;			
		#endif 		
		return;
	}
	m_pCurrentLevel->Update();	
}

void GSM::GameStateManager::Exit()
{
	
		if (m_pCurrentLevel == nullptr)
		{		
			#ifdef DEBUG
				std::cerr << "GSM Exit Error! : CurrentLevel is nullptr" << std::endl;			
			#endif 	
			return;
		}
		m_pCurrentLevel->Exit();
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
	if (newLvl == nullptr)
	{
		#ifdef DEBUG
			std::cerr << "ChangeLevel Error! : new Level is nullptr" << std::endl;			
		#endif 	
		Exit();
		delete m_pCurrentLevel;
		m_pCurrentLevel = nullptr;
		return;
	}
	if (m_pPreviousLevel)
		delete m_pPreviousLevel;
	//���� ���� Exit
	Exit();

	//���� ������ ���������� ���ٰ�
	m_pPreviousLevel = m_pCurrentLevel;
	//���� ������ ���ο� ������ ����
	m_pCurrentLevel = newLvl;
	//����(���ο� ����) ����
	m_pCurrentLevel->Init();
}

bool GSM::GameStateManager::ShouldExit()
{
	return m_pCurrentLevel == nullptr;
}


