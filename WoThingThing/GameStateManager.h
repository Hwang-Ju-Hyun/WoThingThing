#pragma once
#include "Header.h"
//Similiar SceneManager
namespace GSM
{
	class BaseLevel;

	class GameStateManager
	{
	public:
		SINGLE(GameStateManager);	

	private:
		BaseLevel* m_pPreviousLevel;
		BaseLevel* m_pCurrentLevel;
	public:
		virtual void Init();
		virtual void Update();
		virtual void Exit();
	public:
		void ChangeLevel(BaseLevel* newLvl);
		bool ShouldExit();

	};
}


