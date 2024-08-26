#pragma once
namespace GSM
{
	class BaseLevel
	{
	public:
		BaseLevel();
		virtual ~BaseLevel();
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;
	};
}