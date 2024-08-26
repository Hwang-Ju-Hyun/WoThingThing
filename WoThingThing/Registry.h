#pragma once
#include "BaseRTTI.h"
#include <map>
#include <string>
#include "header.h"
//RTTI 
//save to json
//Load to json
class Registry
{
public:
	//Singleton
	SINGLE(Registry);
public:
	//map with names/fucntion_pointers
	std::map<std::string, BaseRTTI* (*)()> rttiMap;

	//typedef BaseRTTI* (*fnPtr)();
	//some interface to find inside me
	//TODO 
	BaseRTTI* FindAndCreate(const std::string& type);
};