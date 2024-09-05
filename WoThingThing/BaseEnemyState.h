#pragma once

namespace ESM
{
	class BaseEnemyState
	{
	public:
		BaseEnemyState();
		virtual ~BaseEnemyState();
	public:
		
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;
	};
}