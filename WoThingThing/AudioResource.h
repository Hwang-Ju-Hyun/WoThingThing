#pragma once
#include "Resource.h"
class AudioResource :
    public Resource
{
public:
    AudioResource(std::string _path);
    ~AudioResource();
private:
    int m_check;
    AEAudio m_Sound;    
    AEAudioGroup m_bgm;    
public:    
    AEAudio GetAudio() { return m_Sound; }
    AEAudioGroup GetAudioGroup(){return m_bgm;}
    void SetSFXorMusic(enum Sound _eType);
    virtual void Load(const std::string& _path)override;
    virtual void UnLoad()override;    
    void PlayMusicOrSFX(AudioResource* _res,enum Sound _type,float _volume,float _pitch,s32 _loops);
};

