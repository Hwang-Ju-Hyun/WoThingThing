#include "Resource.h"
#include "ImageResource.h"
#include <fstream>

ImageResource::ImageResource(const std::string& _name) : Resource(_name)
{

}

ImageResource::~ImageResource()
{
	UnLoad();
}

AEGfxTexture* ImageResource::GetImage()
{
	return (AEGfxTexture*)data;
}

void ImageResource::Load(const std::string& _path)
{
	std::ifstream ifs(_path);
	if (!ifs.is_open())
		return;

	//Load Image Asset
	AEGfxTexture* pTex = AEGfxTextureLoad(_path.c_str());

	data = pTex;
}

void ImageResource::UnLoad()
{
	//Destroy Image Asset
	AEGfxTextureUnload((AEGfxTexture*)data);
}
