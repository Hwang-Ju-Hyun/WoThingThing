#pragma once
#include "header.h"

class Serializer
{
public:
	SINGLE(Serializer);
public:
	void LoadLevel(const std::string& s);
	void SaveLevel(const std::string& s);
};

