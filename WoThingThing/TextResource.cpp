#include "Resource.h"
#include "TextResource.h"
#include <fstream>
TextResource::TextResource(const std::string& _name) : Resource(_name)
{	
}

TextResource::~TextResource()
{	
}

void TextResource::Load(const std::string& _path)
{
	std::ifstream ifs(_path);
	if (!ifs.is_open())
	{
		//std::cout << "Can't Audio find Resource : AudioResource(Load)" << std::endl;
		return;
	}
	m_pFont = AEGfxCreateFont(_path.c_str(),72);
	AEGfxGetPrintSize(m_pFont, m_text.c_str(), 1.f, &m_width, &m_height);
}

void TextResource::UnLoad()
{
	AEGfxDestroyFont(m_pFont);
}
