#pragma once
#include "Header.h"
namespace ESM 
{
	class BaseEnemyState;

	class EnemyStateManager 
	{
	public:
		//SINGLE(EnemyStateManager);
		EnemyStateManager();
		~EnemyStateManager();

	private:
		BaseEnemyState* e_CurrentState;
		BaseEnemyState* e_PreviousState;
	public:
		virtual void Init();
		virtual void Update();
		virtual void Exit();
	public:
		void ChangeState(BaseEnemyState* newState);
		bool ShouldExit();
	};
}
