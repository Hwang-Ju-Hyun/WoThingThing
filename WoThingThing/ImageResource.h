#pragma once
#include "Resource.h"

class ImageResource : public Resource
{
	std::string m_name;

public:
	ImageResource(const std::string& _name);
	~ImageResource();

	AEGfxTexture* GetImage();	

	virtual void Load(const std::string& _path) override;
	virtual void UnLoad() override;
};