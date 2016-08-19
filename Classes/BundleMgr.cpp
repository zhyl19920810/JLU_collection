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
#include "TestScene.h"
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include "dock.hpp"
#include "arsenal.hpp"
#include "Sound.hpp"
#include "KantaiMgr.hpp"
#include "EquipMgr.hpp"
#include "ExpMgr.hpp"
#include "EquipPicMgr.hpp"
#include "RepairFactorMgr.hpp"
#include "TimerMgr.hpp"

#include "DataBaseMgr.hpp"


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
#define DB_IN_COMPUTER 0



static BundleMgr* m_pInstance = NULL;


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
    LoadConfig();
    initialization();
    readFromCache();
    onEnterForeground();
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
    TimerMgr::getInstance()->enterForeGround();
    EventCustom event("updateTimestamp");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void BundleMgr::onDestroy()
{
    TimerMgr::getInstance()->delInstance();
    Arsenal::delInstance();
    Dock::delInstance();
    Player::delInstance();
    RepairFactorMgr::delInstance();
    EquipPicMgr::delInstance();
    ExpMgr::delInstance();
    EquipMgr::delInstance();
    KantaiMgr::delInstance();
    tina::TinaMgr::destroy();
}

void BundleMgr::LoadConfig()
{
    KantaiMgr::newInstance();
    EquipMgr::newInstance();
    ExpMgr::newInstance();
    EquipPicMgr::newInstance();
    RepairFactorMgr::newInstance();
    sKantaiMgr.loadConf();
    sEquipMgr.loadConf();
    sExpMgr.loadConf();
    sEquipPicMgr.loadConf();
    sRepairFactorMgr.loadConf();
}




void BundleMgr::initialization()
{
    Player::newInstance();

    
#if DB_IN_COMPUTER
    std::string writablePath = FileUtils::getInstance()->fullPathForFilename("/Volumes/opengl/kancolle_beta/Resources/database/kancolle_2.sqlite3");
    
#else
    std::string dbFilePath = FileUtils::getInstance()->fullPathForFilename("database/kancolle_2.sqlite3");
    std::string writablePath =createDownLoadUrl();
    writablePath+= GAME_DB_NAME;
    ssize_t dbSize=0;
    FileUtils::getInstance()->getFileData(writablePath.c_str(), "r", &dbSize);
    if(!dbSize){
        fstream fsCopee( dbFilePath.c_str(), ios::binary | ios::in ) ;
        fstream fsCoper( writablePath.c_str(), ios::binary | ios::out ) ;
        fsCoper << fsCopee.rdbuf();
    }
#endif
    DB_MGR->initDB(writablePath, 1);
    Dock::newInstance();
    Arsenal::newInstance();
    sDock.initDock(1);
    sArsenal.initArsenal(1);
    
    
    TimerMgr::getInstance()->startTimer();
    Sound::getInstance()->initVolume();
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


void BundleMgr::updateMusicSetting(bool _bgMusicSwitch, bool _effMusicSwitch)
{
    bgMusicSwitch = _bgMusicSwitch;
    effMusicSwitch = _effMusicSwitch;
    writeToCache();
}



void BundleMgr::destroyMgrs()
{

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
    CACHE->flush();
}

bool BundleMgr::checkEnterForeground()
{
    return true;
}



void BundleMgr::initTinaConfig()
{
    auto _cfg = tina::TINA_MGR->getConfig();
    _cfg->setImageDir("image/");
    _cfg->setResDir("image/res/");
    _cfg->setXmlDir("config/");
    _cfg->setTxmlDir("txml/");
    _cfg->setFontDir("font/");
    _cfg->setFontDir("font/");
    _cfg->setShaderDir("shader/");
    _cfg->setSoundDir("sound/");
}



#define TRIPLE_CLICK_DURATION 2
#define TRIPLE_CLICK_NUM 5


void BundleMgr::init()
{

}


NS_KCL_END