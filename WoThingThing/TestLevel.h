#pragma once
#include "BaseLevel.h"

class GameObject;
class MainMenu_Lvl;
namespace Level
{
	class TestLevel :public GSM::BaseLevel
	{
	public:
		TestLevel();
		~TestLevel();
	public:
		virtual void Init() override;
		virtual void Update() override;
		virtual void Exit() override;
	private:
		GameObject* Test_player;
		GameObject* Enemy;
	};
}

