//
//  Sound.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/4/16.
//
//

#ifndef Sound_hpp
#define Sound_hpp

#include "SimpleAudioEngine.h"
#include "SystemHeader.h"

NS_KCL_BEGIN

#define SND Sound::getInstance()

#define BGM_VOLUME     "bgm_volume"
#define SE_VOLUME      "se_volume"
#define VOICE_VOLUME   "voice_volume"

class Sound
{
public:
    static Sound* getInstance();
    static void destory();
    
private:
    Sound();
    
public:
    void preloadMusic(const std::string &name);
    void preloadMusic(const std::vector<std::string> &vecName);
    void preloadEffect(const std::string &name);
    void preloadEffect(const std::vector<std::string> &vecName);
    void unloadEffect(const std::string &name);
    
    void initVolume();

    void playMusic(const std::string &name, bool bLoop = true, float volume = 1.f);
    void playEffect(const std::string &name, float volume = 1.0f, float pan = 0.0f);
    void stopMusic(bool bReleaseData = false);
    void stopAllEffects();
    

    void pauseMusic();
    void resumeMusic();
    void pauseAllEffects();
    void resumeAllEffects();
    void rewindMusic();
    void setEffectVolume(float volume);
    void setBGVolume(float volume);
    
private:
    std::string strRelDir;//声音目录
    std::string	m_crtBg;
    
};

NS_KCL_END


#endif /* Sound_hpp */
