#pragma once
#include "Resource.h"
class TextResource :
    public Resource
{
public:
    TextResource(std::string _name);
    ~TextResource();
private:
    std::string m_name;
private:
    s8 m_pFont;
    std::string m_text="Hello World!";
    f32 m_width, m_height;
public:
    void SetText(const std::string& _text="Hello World!")
    {
        m_text = _text;
    }
    const char* GetText()
    {
        return m_text.c_str();
    }
    const s8& GetFont()
    {
        return m_pFont;
    }
    f32& GetWidth()
    {
        return m_width;
    }
    f32& GetHeight()
    {
        return m_height;
    }
public:
    virtual void Load(const std::string& _path) override;
    virtual void UnLoad() override;

};

