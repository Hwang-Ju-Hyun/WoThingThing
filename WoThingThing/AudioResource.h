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
    float m_volume = 1.f;
    float m_pitch = 1.f;
public:
    void SetVolume(float _vol) { m_volume = _vol; }
    const float GetVolume() { return m_volume; }
    void SetPitch(float _pitch) { m_pitch = _pitch; }
    const float GetPitch() { return m_pitch; }
public:    
    AEAudio GetAudio() { return m_Sound; }
    AEAudioGroup GetAudioGroup(){return m_bgm;}
    void SetSFXorMusic(enum Sound _eType);
    virtual void Load(const std::string& _path)override;
    virtual void UnLoad()override;    
    void PlayMusicOrSFX(AudioResource* _res,enum Sound _type,float _volume,float _pitch,s32 _loops);
};

