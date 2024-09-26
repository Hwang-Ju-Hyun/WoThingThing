#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;

class BaseRTTI
{
public:
	virtual void LoadFromJson(const json& str) = 0;
	virtual json SaveToJson(const json& str) = 0;
	virtual ~BaseRTTI() {}
};