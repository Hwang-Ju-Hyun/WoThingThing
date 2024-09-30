#pragma once
#include "header.h"

class Resource;

class ResourceManager
{
public:
	SINGLE(ResourceManager);
private:
	std::map<std::string, Resource*>m_mapRes;
	
	enum Select_Extension
	{
		png,
		jpg,
		wav,
		mp3,
		ttf,
		nothing
	};
	Select_Extension Get_Extension(const std::string& _extension);
public:	
	void RemoveAllRes();
	const std::map<std::string, Resource*> GetReource();
	Resource* Get(const std::string& _resName,const std::string& _path);
	Resource* FindRes(const std::string& _name);
};