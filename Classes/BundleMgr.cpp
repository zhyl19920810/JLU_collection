//
//  BundleMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#include "BundleMgr.hpp"
#include "TinaMgr.hpp"
#include "HelloWorldScene.h"
#include "DatabaseScene.h"
#include "XMLBuilder.h"
#include "databaseInit.h"
#include "databaseBase.h"
#include "portScene.h"
#include "GameScene.h"
#include "MissionNode.h"
#include "TestScene.h"
#include "GameManger.hpp"
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include "dock.hpp"
#include "arsenal.hpp"


NS_KCL_BEGIN

#define CACHE_BG_MUSIC_SWITCH ("cache_bg_music_switch")
#define CACHE_EFF_MUSIC_SWITCH ("cache_eff_music_switch")
#define CACHE_ENTER_BACKGROUND_TS ("cache_enter_background_ts")
#define CACHE_SCENE_ENTER_TIMES "cache_scene_enter_times_%lld_%d"
#define CACHE_PANEL_ENTER_TIMES "cache_panel_enter_times_%lld_%d"
#define CACHE_ACTIVITY_ENTER_TIMES "cache_panel_enter_times_%lld_%d_%d"
#define CACHE (UserDefault::getInstance())
#define FILE_UTIL FileUtils::getInstance()
#define GAME_DB_NAME "kancolle_2.sqlite3"

static BundleMgr* m_pInstance = NULL;

//从主界面再次回到游戏的最大过期时间（秒），超过这个时间游戏会重走APP启动流程
#define MAX_ENTER_BACKGROUND_SECONDS (6 * 60 * 60)


static bool g_bInit = false;

BundleMgr* BundleMgr::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new BundleMgr;
        m_pInstance->init();
    }
    return m_pInstance;
}

void BundleMgr::destroy()
{
    CC_SAFE_DELETE(m_pInstance);
}


void BundleMgr::onLaunchApp()
{
    initTinaConfig();
    //resize();
    readFromCache();
    //setSearchPath();
    initialization();
    exeLaunch();
}

void BundleMgr::onEnterBackground()
{
    writeToCache();
}

void BundleMgr::onEnterForeground()
{
    readFromCache();
    if (!checkEnterForeground())
        return;
}

void BundleMgr::onDestroy()
{
    tina::TinaMgr::destroy();
    //ViewMgr::destroy();
//    Lang::destroy();
//    DataMgr::destroy();
//    SocketComm::destroy();
//    CfgMgr::destroy();
//    DialogueMgr::destroy();
    
//    ArmatureCache::destroy();
//    ArmatureLoader::destroy();
//    NotifyMgr::destroy();
//    BuyMgr::destroy();
//    TaskMgr::destroy();
//    Http::destroy();
//    Socket::destory();
//    TimerMgr::destroy();
//    AttrItemNotifiMgr::destroy();
//    LocalNotifyMgr::destroy();
}

void BundleMgr::initialization()
{
    GameManger::newInstance();
    sGameManger.LoadConfig();
    sGameManger.LoadResource();
    Player::newInstance();
    Dock::newInstance();
    Arsenal::newInstance();
    
    
#if DB_IN_COMPUTER
    std::string writablePath = FileUtils::getInstance()->fullPathForFilename("/Volumes/opengl/kancolle_beta/Resources/database/kancolle_2.sqlite3");
    
#else
    std::string dbFilePath = FileUtils::getInstance()->fullPathForFilename("database/kancolle_2.sqlite3");
    std::string writablePath =createDownLoadUrl();
    writablePath+= GAME_DB_NAME;
    ssize_t dbSize=0;
    FileUtils::getInstance()->getFileData(writablePath.c_str(), "r", &dbSize);
    if(dbSize){
        fstream fsCopee( dbFilePath.c_str(), ios::binary | ios::in ) ;
        fstream fsCoper( writablePath.c_str(), ios::binary | ios::out ) ;
        fsCoper << fsCopee.rdbuf();
    }
#endif
    DBBase::init(writablePath);
    DBInit init;
    init.initDB(1);
    sDock.initDock(1);
    sArsenal.initArsenal(1);
    //    if (VIEW_MGR->getRuningSceneType() != SceneType::SDK)
    //    {
    //        return;
    //    }
    //    cocos2d::log("BundleMgr::initialization 1");
    //    IndicatorView::HideIndicator();
    //    destroyMgrs();
    //    cocos2d::log("BundleMgr::initialization 2");
    //    //解析配置文件
    //    CFG_MGR->parse();
    //    if (m_appConf.sdk == SdkType::MOBAGE)
    //    {
    //        cocos2d::log("BundleMgr::initialization 3");
    //        Director::getInstance()->getScheduler()->schedule([this](float)->void{
    //            VIEW_MGR->showScene(SceneType::LOGIN);
    //        }, this, 0, 0, 0.3f, false, "BundleMgr::initialization");
    //    }
    //    else
    //    {
    //        VIEW_MGR->showScene(SceneType::LOGIN);
    //    }
    //
    //    //开始消息推送
    //    LOCAL_NOTIFY_MGR->pushNotify();
    //    cocos2d::log("BundleMgr::initialization 4");
}


std::string BundleMgr::createDownLoadUrl()
{
    std::string pathToSave;
    pathToSave = FileUtils::getInstance()->getWritablePath();
    //pathToSave += DOWNLOAD_PATH;
    
    // Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *pDir = NULL;
    pDir = opendir (pathToSave.c_str());
    if (!pDir)
    {
        mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
#else
    if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
    {
        CreateDirectoryA(pathToSave.c_str(), 0);
    }
#endif
    return pathToSave;
}

//====================
//void BundleMgr::logout()
//{
//    cocos2d::log("BundleMgr::logout");
//    if(m_relaunching)
//        return;
//    IndicatorView::HideIndicator();
//    destroyMgrs();
//    VIEW_MGR->showScene(SceneType::LOGIN);
//}
//
//void BundleMgr::logoutFromSdk()
//{
//    cocos2d::log("BundleMgr::logoutFromSdk");
//    if (Director::getInstance()->isPaused())
//    {
//        m_needBackToSdkScene = true;
//        return;
//    }
//    
//    destroyMgrs();
//    VIEW_MGR->showScene(SceneType::SDK);
//    
//    m_needBackToSdkScene = false;
//}

//void  BundleMgr::logoutWithoutDestory()
//{
//    cocos2d::log("BundleMgr::logoutWithoutDestory");
//    SocketComm::destroy();
//    Socket::destory();
//    MOBAGE_DELEGATE->clear();
//    VIEW_MGR->showScene(SceneType::LOGIN);
//}

//void BundleMgr::reLaunch()
//{
//    cocos2d::log("BundleMgr::reLaunch");
//    m_relaunching = true;
//    destroyMgrs();
//    VIEW_MGR->showScene(SceneType::LOGO);
//    m_relaunching = false;
//}




void BundleMgr::updateMusicSetting(bool _bgMusicSwitch, bool _effMusicSwitch)
{
    bgMusicSwitch = _bgMusicSwitch;
    effMusicSwitch = _effMusicSwitch;
    writeToCache();
}



void BundleMgr::destroyMgrs()
{
//    TimerMgr::destroy();
//    DataMgr::destroy();
//    SocketComm::destroy();
//    Socket::destory();
//    DialogueMgr::destroy();
//    NewbieMgr::destroy();
//    NotifyMgr::destroy();
//    AttrItemNotifiMgr::destroy();
//    LocalNotifyMgr::destroy();
    //ArmatureCache::destroy();
    //ArmatureLoader::destroy();
}

void BundleMgr::readFromCache()
{
    bgMusicSwitch = CACHE->getBoolForKey(CACHE_BG_MUSIC_SWITCH, true);
    effMusicSwitch = CACHE->getBoolForKey(CACHE_EFF_MUSIC_SWITCH, true);
}

void BundleMgr::writeToCache()
{
    CACHE->setBoolForKey(CACHE_BG_MUSIC_SWITCH, bgMusicSwitch);
    CACHE->setBoolForKey(CACHE_EFF_MUSIC_SWITCH, effMusicSwitch);
    //->setIntegerForKey(CACHE_ENTER_BACKGROUND_TS, tina::TimeUtil::getTimestamp());
    CACHE->flush();
}

bool BundleMgr::checkEnterForeground()
{
    return true;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//    return true;
//#endif
//    
//    uint32_t _lastEnterBackgroundTs = CACHE->getIntegerForKey(CACHE_ENTER_BACKGROUND_TS, 0);
//    /*
//     如果再次回到游戏的时间超过MAX_ENTER_BACKGROUND_SECONDS（秒）
//     则重走APP启动流程
//     */
//    if (tina::TimeUtil::getTimestamp() - _lastEnterBackgroundTs > MAX_ENTER_BACKGROUND_SECONDS)
//    {
//        reLaunch();
//        return false;
//    }
//    else
//    {
//        SOCKET_COMM->send(MsgID::PING, false);
//    }
//    return true;
}

//void BundleMgr::setSearchPath()
//{
//    std::vector<std::string> _searchPath = FILE_UTIL->getSearchPaths();
//    std::string _packResourcePath = _searchPath.front();
//    
//    if(!_packResourcePath.empty() && _packResourcePath.back() != '/')
//        _packResourcePath.push_back('/');
//    std::string _updateResourcePath = getUpdateResDir();
//    _searchPath.clear();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//    _searchPath.push_back(getWin32ResourcesPath());
//#endif
//    _searchPath.push_back("assets/");
//    _searchPath.push_back(_updateResourcePath + "/");
//    _searchPath.push_back(_updateResourcePath + "/zh-cn/");
//    _searchPath.push_back(_updateResourcePath + "/common/");
//    _searchPath.push_back(_packResourcePath + "zh-cn/");
//    _searchPath.push_back(_packResourcePath + "common/");
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    _searchPath.insert(_searchPath.begin(), "/mnt/sdcard/gintama/zh-cn/");
//#endif
//    FILE_UTIL->setSearchPaths(_searchPath);
//}
//
//void BundleMgr::resize()
//{
//    int _minHeight = 640;
//    Size _originalSize = Director::getInstance()->getWinSize();
//    Size _newSize;
//    bool _portrait = false;
//    
//    //如果是PAD，假设PAD分辨率 <= 3/4
//    if (_originalSize.height / _originalSize.width >= 0.75f && _originalSize.height >= 768)
//    {
//        _minHeight = 768;
//    }
//    
//    _newSize.height = _minHeight;
//    _newSize.width = _originalSize.width / (_originalSize.height / _newSize.height);
//    
//    auto _pView = Director::getInstance()->getOpenGLView();
//    _pView->setDesignResolutionSize(_newSize.width, _newSize.height, ResolutionPolicy::NO_BORDER);
//}

void BundleMgr::initTinaConfig()
{
    auto _cfg = tina::TINA_MGR->getConfig();
    //_cfg->setCustomWidgetCreator(new WidgetCreator());
    _cfg->setImageDir("image/");
    _cfg->setResDir("image/res/");
    _cfg->setXmlDir("config/");
    _cfg->setTxmlDir("txml/");
    _cfg->setFontDir("font/");
    _cfg->setFontDir("font/");
    _cfg->setShaderDir("shader/");
    _cfg->setSoundDir("sound/");
}

//std::string BundleMgr::getWin32ResourcesPath()
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//    WCHAR utf16Path[MAX_PATH] = { 0 };
//    GetCurrentDirectoryW(sizeof(utf16Path) - 1, utf16Path);
//    
//    char utf8Path[MAX_PATH] = { 0 };
//    int nNum = WideCharToMultiByte(CP_UTF8, 0, utf16Path, -1, utf8Path, sizeof(utf8Path), nullptr, nullptr);
//    
//    std::string _path(utf8Path);
//    _path.append("/");
//    _path.append(m_appConf.language);
//    _path.append("/");
//    return _path;
//#else
//    return "";
//#endif
//}

#define TRIPLE_CLICK_DURATION 2
#define TRIPLE_CLICK_NUM 5


void BundleMgr::init()
{

}


NS_KCL_END