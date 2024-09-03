#pragma once
#include "header.h"

class GameObject;

class ColliderManager
{
public:
	SINGLE(ColliderManager);
public:
	bool IsCollision(GameObject* _obj1, GameObject* _obj2);
	bool PlayerSearch(GameObject* _obj1, GameObject* _obj2, bool enemy_dir, float x_range, float y_range, float bottom_y_range);
	bool MeleeEnemyAttack(GameObject* _obj1, GameObject* _obj2, bool enemy_dir);
	//bool isFacingtheSameDirection(AEVec2 e_pos, AEVec2 player_pos, bool enemy_dir);
	bool isFacingtheSameDirection(AEVec2 chase_pos, bool enemy_dir);
	float Dot(const AEVec2& vec1, const AEVec2& vec2);
	void DrawRect(float bottomleft_x, float bottomleft_y, float topRight_x, float topRight_y, float r, float g, float b);
	
};

