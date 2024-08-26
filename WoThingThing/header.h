#pragma once
#define	SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							~type();

enum Sound
{
	MUSIC,
	SFX
};


#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "AEEngine.h"
#include "AEVec2.h"