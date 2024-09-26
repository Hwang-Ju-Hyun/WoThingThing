#pragma once
#include "header.h"

class Resource
{
public:
	Resource(std::string _name);
	virtual ~Resource();//Otherwise you would Not be deleting the specialized classes
private:
	std::string m_resPath;	
public:	
	void* data;

	virtual void Load(const std::string& _name) = 0;	
	virtual void UnLoad()=0;

public:	
	void SetName(const std::string& _name) 
	{
		m_resPath = _name;
	}
	const std::string&  GetName()
	{
		return m_resPath;
	}
};