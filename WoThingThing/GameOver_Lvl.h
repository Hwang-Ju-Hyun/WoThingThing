#pragma once
#include "BaseLevel.h"
#include <vector>

class GameObject;
class MainMenu_Lvl;
class Stage01_Lvl;

namespace Level
{
	class GameOver_Lvl : public GSM::BaseLevel
	{
	public:
		GameOver_Lvl();
		~GameOver_Lvl();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
}