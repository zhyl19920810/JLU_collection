//
//  Sound.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/4/16.
//
//

#include "Sound.hpp"
#include "BundleMgr.hpp"
#include "TinaMgr.hpp"

using namespace std;
using namespace CocosDenshion;

NS_KCL_BEGIN

Sound* Sound::getInstance()
{
    static Sound gSound;
    return &gSound;
}

void Sound::destory()
{
    SimpleAudioEngine::getInstance()->end();
}

Sound::Sound()
:strRelDir(tina::TINA_MGR->getSoundFullPath(""))
{
    
}

void Sound::preloadMusic(const std::string &name)
{
    string filePath(strRelDir + name);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filePath.c_str());
}

void Sound::preloadMusic(const std::vector<std::string> &vecName)
{
    for (auto filePath : vecName)
    {
        preloadMusic(filePath);
    }
}

void Sound::preloadEffect(const std::string &name)
{
    string filePath(strRelDir + name);
    SimpleAudioEngine::getInstance()->preloadEffect(filePath.c_str());
}

void Sound::preloadEffect(const std::vector<std::string> &vecName)
{
    for (auto filePath : vecName)
    {
        preloadEffect(filePath);
    }
}

void Sound::unloadEffect(const std::string &name)
{
    if (name.empty())
        return;
    
    string filePath(strRelDir + name);
    SimpleAudioEngine::getInstance()->unloadEffect(filePath.c_str());
}

void Sound::playMusic(const std::string &name, bool bLoop, float volume)
{
    if (name.empty())
        return;
    
    string filePath(strRelDir + name);
    
    if (!BUNDLE_MGR->bgMusicSwitch || m_crtBg == filePath)
        return;
    
    if ((volume-1.0)<0.0001||(volume-1.0)>-0.0001)
        volume=bgmVolume;
    
    m_crtBg = filePath;
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath.c_str(), bLoop);
}

void Sound::playEffect(const std::string &name, float volume, float pan)
{
    if (name.empty() || !BUNDLE_MGR->effMusicSwitch)
        return;
    string filePath(strRelDir + name);
    
    if ((volume-1.0)<0.0001||(volume-1.0)>-0.0001)
         volume=seVolume;
    
    SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
    SimpleAudioEngine::getInstance()->playEffect(filePath.c_str(), false, 1.0f, pan, 1.0f);
}

void Sound::stopMusic(bool bReleaseData)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(bReleaseData);
    m_crtBg = "";
}

void Sound::stopAllEffects()
{
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void Sound::pauseMusic()
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void Sound::resumeMusic()
{
    if (!BUNDLE_MGR->bgMusicSwitch)
        return;
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void Sound::pauseAllEffects()
{
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void Sound::resumeAllEffects()
{
    if (!BUNDLE_MGR->effMusicSwitch)
        return;
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void Sound::rewindMusic()
{
    SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
}

void Sound::setEffectVolume(float volume)
{
    if ((volume-seVolume)<0.0001&&(volume-seVolume)>-0.0001) return;
    seVolume=volume;
    SimpleAudioEngine::getInstance()->setEffectsVolume(seVolume);
    cocos2d::UserDefault::getInstance()->setFloatForKey(SE_VOLUME, seVolume);
}

void Sound::setBGVolume(float volume)
{
    if ((volume-bgmVolume)<0.0001&&(volume-bgmVolume)>-0.0001) return;
    bgmVolume=volume;
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(bgmVolume);
    cocos2d::UserDefault::getInstance()->setFloatForKey(BGM_VOLUME, bgmVolume);
}

void Sound::initVolume()
{
    bgmVolume=cocos2d::UserDefault::getInstance()->getFloatForKey(BGM_VOLUME, 0.5);
    seVolume=cocos2d::UserDefault::getInstance()->getFloatForKey(SE_VOLUME, 0.5);
    SND->setBGVolume(bgmVolume);
    SND->setEffectVolume(seVolume);
}


NS_KCL_END