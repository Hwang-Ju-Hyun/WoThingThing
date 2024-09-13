#pragma once
#include "BaseLevel.h"
#include "AEEngine.h"
#include <vector>

class GameObject;
class MainMenu_Lvl;
class Stage01_Lvl;
class GameOver_Lvl;

namespace Level
{
	class GameStart_Lvl : public GSM::BaseLevel
	{
		GameObject* DigipenLogo;
		GameObject* TeamLogo;

		f32 preTime;
		f32 totallogoTime;

		f32 logoSec;
		f32 logoVec;


	public:
		GameStart_Lvl();
		~GameStart_Lvl();

		f32 lerp(f32 a, f32 b, f32 v);


		virtual void Init() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
}