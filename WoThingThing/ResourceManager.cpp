#include "ResourceManager.h"
#include "AudioResource.h"
#include "TextResource.h"
#include "ImageResource.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager::Select_Extension ResourceManager::Get_Extension(const std::string& _extension)
{
	if (_extension == "ttf")
	{
		return ttf;
	}
	if (_extension == "png")
	{
		return png;
	}

	if (_extension == "jpg")
	{
		return jpg;
	}

	if (_extension == "wav")
	{
		return wav;
	}
	if (_extension == "mp3")
	{
		return mp3;
	}
}

Resource* ResourceManager::FindRes(const std::string& _name)
{
	for (auto iter = m_mapRes.begin(); iter != m_mapRes.end(); iter++)
	{
		if (iter->first == _name)
		{
			return iter->second;			
		}
	}
	std::cerr << "Can't find Resource Path : ResourceManager FindRes" << std::endl;
	return nullptr;
}



const std::map<std::string, Resource*> ResourceManager::GetReource()
{
	return m_mapRes;
}

Resource* ResourceManager::Get(const std::string& _resName,const std::string& _path)
{		
	auto iter=m_mapRes.find(_resName);

	if (iter == m_mapRes.end())
	{
		std::string ext = _path.substr(_path.find_last_of(".") + 1);

		//Helper function which uses the code above and some string comparisons to extension type in an enum value
		// , so we can use it in a switch statement
		Select_Extension extension = Get_Extension(ext);

		Resource* resource = nullptr;

		switch (extension)
		{
		case ResourceManager::ttf:
			resource = new TextResource(_resName);
			resource = static_cast<TextResource*>(resource);
			m_mapRes.insert({ _resName,resource });
			break;
		case ResourceManager::png:
			resource = new ImageResource(_resName);
			resource = static_cast<ImageResource*>(resource);
			m_mapRes.insert({ _resName,resource });
		case ResourceManager::jpg:			
			break;
		case ResourceManager::wav:
		case ResourceManager::mp3:
			resource = new AudioResource(_resName);
			resource = static_cast<AudioResource*>(resource);										
			m_mapRes.insert({ _resName,resource });
			break;
		default:
			return nullptr;
			break;
		}
		resource->Load(_path);
		return resource;
		//return resource;
		//In case this a texture (png, jpg, ...)
			//create a new textureResource and load it	
		//In case t is a music (mp3, wav, ...)
			//create a net musicResource and load it
	}
	else
	{				
		return iter->second;
	}
}

void ResourceManager::RemoveAllRes()
{
	for (auto iter = m_mapRes.begin(); iter != m_mapRes.end();)
	{
		if (iter->second != nullptr)
		{
			iter->second->UnLoad();
			delete iter->second;
			iter = m_mapRes.erase(iter++);
		}
		else
		{
			iter++;
		}
	}

}