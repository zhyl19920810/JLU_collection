//
//  BundleMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#ifndef BundleMgr_hpp
#define BundleMgr_hpp


#include "SystemHeader.h"
#include "base/CCEventKeyboard.h"

namespace cocos2d
{
    class Ref;
    class Event;
};


#define BUNDLE_MGR (BundleMgr::getInstance())


class BundleMgr
{
public:
    static BundleMgr* getInstance();
    static void destroy();
    
public:
    void onLaunchApp();
    void onEnterBackground();
    void onEnterForeground();
    void onDestroy();
    
public:
    /**	游戏内退出*/
    void logout();
    /*从Sdk内退出*/
    void logoutFromSdk();
    void logoutWithoutDestory();
    
    /**	重启APP*/
    void reLaunch();
    
    /**	初始化（配置、语言包、动画等）*/
    void initialization();
    
public:
    /**	更新音乐（音效）设置*/
    void updateMusicSetting(bool bgMusicSwitch, bool effMusicSwitch);
    bool isOfficialChannel();
    
private:
    void destroyMgrs();
    void readFromCache();
    void writeToCache();
    bool checkEnterForeground();
    //void setSearchPath();
    void resize();
    void initTinaConfig();
    std::string getWin32ResourcesPath();
    
private:
    void init();
    std::string createDownLoadUrl();
    
    
private:
    bool            m_relaunching = false;
    int				m_clickNum = 0;
    int64_t			m_dt = 0;
    int64_t			m_lastDt = 0;
    bool			m_sdkIconVisible = true;
    bool			m_needBackToSdkScene = false;
    
    
public:
    bool            bgMusicSwitch = true;
    bool            effMusicSwitch = true;
};

extern void exeLaunch();
#endif /* BundleMgr_hpp */
