#pragma once
#include "header.h"

class GameObject;

class Serializer
{
public:
	SINGLE(Serializer);
public:
	void LoadLevel(const std::string& s);	
	void SaveLevel(const std::string& s);
public:
	GameObject* LoadEnemy(const std::string& s);
	void SaveEnemy(const std::string& s);

	GameObject* LoadEnemySniper(const std::string& s);
	void SaveEnemySniper(const std::string& s);
};

