#pragma once
#include "BaseLevel.h"
namespace Level
{
	class Congratulation :public GSM::BaseLevel
	{
	public:
		Congratulation();
		~Congratulation();
	public:
		virtual void Init() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
}


