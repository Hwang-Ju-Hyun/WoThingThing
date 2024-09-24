#include "Resource.h"
#include "AudioResource.h"
#include "ResourceManager.h"
#include <fstream>

AudioResource::AudioResource(std::string _name)
	:Resource(_name)
{
}

AudioResource::~AudioResource()
{
	UnLoad();
}

void AudioResource::SetSFXorMusic(Sound _eType)
{
	switch (_eType)
	{
	case MUSIC:
		m_check = 0;
		break;
	case SFX:
		m_check = 1;
		break;
	default:
		m_check = 0;
		break;
	}
}

void AudioResource::Load(const std::string& _path)
{
	std::ifstream ifs(_path);
	if (!ifs.is_open())
	{
		//std::cout<< "Can't Audio find Resource : AudioResource(Load)" << std::endl;
		return;
	}
	if (m_check == Sound::MUSIC)
	{
		m_Sound = AEAudioLoadMusic(_path.c_str());
		m_bgm = AEAudioCreateGroup();				
	}
	else if (m_check == Sound::SFX)
	{
		m_Sound = AEAudioLoadSound(_path.c_str());
		m_bgm = AEAudioCreateGroup();				
	}
	
}

void AudioResource::UnLoad()
{
	AEAudioUnloadAudio(m_Sound);
	AEAudioUnloadAudioGroup(m_bgm);
}

void AudioResource::PlayMusicOrSFX(AudioResource* _res, Sound _type, float _volume, float _pitch, s32 _loops)
{
	_res->SetSFXorMusic(_type);
	auto audio = _res->GetAudio();
	m_bgm = _res->GetAudioGroup();
	AEAudioPlay(audio, m_bgm, _volume, _pitch, _loops);
}