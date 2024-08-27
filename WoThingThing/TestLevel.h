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
	public:
		static int enemy_dir;//0이면 왼쪽 방향으로 가고 있다는 뜻, 1이면 오른쪽 방향 (일단 예비용)
	};
}


