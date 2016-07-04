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



#define SND Sound::getInstance()

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
    
    /*
     * 播放音效
     * 参数 1：音效文件名
     * 参数 2：是否循环
     * 参数 3：音效音量（取值范围[0,1]：0最小，1最大）
     */
    void playMusic(const std::string &name, bool bLoop = true, float volume = 1.f);
    
    /*
     * 播放音效
     * 参数 1：音效文件名
     * 参数 2：音效音量（取值范围[0,1]：0最小，1最大）
     * 参数 3：立体声效果（取值范围[-1,1]：-1为左声道，1为右声道）
     
     @note Full support is under development, now there are limitations:
     - no pitch effect on Samsung Galaxy S2 with OpenSL backend enabled;
     - no pitch/pan/gain on emscrippten, win32, marmalade.
     */
    void playEffect(const std::string &name, float volume = 1.0f, float pan = 0.0f);
    
    /*
     * 停止播放背景音乐
     * 参数 1：是否释放数据
     */
    void stopMusic(bool bReleaseData = false);
    void stopAllEffects();
    
    /*
     * 暂停、恢复音乐、音效
     */
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




#endif /* Sound_hpp */
