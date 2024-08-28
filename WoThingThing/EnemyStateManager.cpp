#include "EnemyStateManager.h"
#include"BaseEnemyState.h"

ESM::EnemyStateManager::EnemyStateManager() :e_CurrentState(nullptr), e_PreviousState(nullptr)
{

}

ESM::EnemyStateManager::~EnemyStateManager()
{
	if (e_CurrentState) 
	{
		delete(e_CurrentState);
	}
}

void ESM::EnemyStateManager::Init()
{
	if (e_CurrentState == nullptr)
	{
#ifdef DEBUG
		std::cerr << "ESM Init Error! : CurrentLevel is nullptr" << std::endl;
#endif 		
		return;
	}
	e_CurrentState->Init();
}

void ESM::EnemyStateManager::Update()
{
	if (e_CurrentState == nullptr)
	{
#ifdef DEBUG
		std::cerr << "ESM Update Error! : CurrentLevel is nullptr" << std::endl;
#endif 		
		return;
	}
	e_CurrentState->Update();
}

void ESM::EnemyStateManager::Exit()
{
	if (e_CurrentState == nullptr)
	{
#ifdef DEBUG
		std::cerr << "ESM Exit Error! : CurrentLevel is nullptr" << std::endl;
#endif 		
		return;
	}
	e_CurrentState->Exit();
}

void ESM::EnemyStateManager::ChangeState(BaseEnemyState* newState)
{
	if (newState == nullptr)
	{
#ifdef DEBUG
		std::cerr << "ChangeLevel Error! : new Level is nullptr" << std::endl;
#endif 	
		e_CurrentState = nullptr;
		return;
	}
	if (e_PreviousState)
		delete e_PreviousState;
	//현재 레벨 Exit
	Exit();

	//현재 상태를 이전상태로 바꾸고
	e_PreviousState = e_CurrentState;
	//현재 상태를 새로운 상태로 갱신
	e_CurrentState = newState;
	//현재(새로운 상태) 진입
	e_CurrentState->Init();
}

bool ESM::EnemyStateManager::ShouldExit()
{
	return e_CurrentState == nullptr;
}
