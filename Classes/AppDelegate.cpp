#include "AppDelegate.h"
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

#define DB_IN_COMPUTER 1
#define DEBUG_MODE true

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

void battleModel(Director* director)
{
    //init db
    std::string filename = FileUtils::getInstance()->fullPathForFilename("database/kancolle_2.sqlite3");
    DBBase::init(filename);
    DBInit init;
    auto player=Player::getInstance();
    init.initDB(1);
    
    if (DEBUG_MODE)
    {
        Fleet* allies=sPlayer.fleetData[0];
        
        MissionNode node;
        Fleet* enemy=node.parseEnemyFleet("-2");
        
        
        auto battleModel=new BattleModel(allies,enemy,DanZong,DanZong);
        GameScene* scene=new GameScene(battleModel);
        director->runWithScene(scene);
    }
}



std::string AppDelegate::createDownLoadUrl()
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

#define GAME_DB_NAME "kancolle_2.sqlite3"



void AppDelegate::portModel(Director* director)
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
//    for (int j=0; j<2; ++j)
//    {
//        for (int i=1; i<25; ++i)
//        {
//            if (sPlayer.canBuildNewKantai(i)) {
//                sPlayer.buildNewKantai(i);
//            }
//        }
//    }

    
    
    
    auto scene=PortScene::createScene();
    director->runWithScene(scene);
    
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
    {
        glview=GLViewImpl::createWithRect("kancolle", Rect(0, 0, 800, 480));
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->getOpenGLView()->setDesignResolutionSize(800, 480, ResolutionPolicy::SHOW_ALL);
    glview->setFrameSize(800, 480);
    
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    
//    auto visibleSize=Director::getInstance()->getVisibleSize();
//    log("visibleSize: %f %f",visibleSize.width,visibleSize.height);
//    
//    auto visibleOrgin=Director::getInstance()->getVisibleOrigin();
//    log("visibleOrgin: %f  %f",visibleOrgin.x,visibleOrgin.y);
//    
//    auto winSize=Director::getInstance()->getWinSize();
//    log("winSize:  %f %f",winSize.width,winSize.height);
    
    register_all_packages();
    
    //battleModel(director);
    portModel(director);
    
    return true;
}




// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    
}







void DBtest()
{
    //    for (int h=0; h<2; ++h)
    //    {
    //        for (int i=1; i<=10; ++i)
    //        {
    //            if (sPlayer.canBuildNewKantai(i))
    //            {
    //                sPlayer.buildNewKantai(i);
    //            }
    //        }
    //    }
    
    
    //    for (int i=0; i<5; ++i)
    //    {
    //        auto kantai=sPlayer.findKantaiByKantaiKey(21+i);
    //        auto fleet=sPlayer.getFleetByFleetKey(1);
    //        if (sPlayer.canChangeKantaiPosition(fleet, i+2, kantai))
    //        {
    //            sPlayer.changeKantaiPosition(fleet, i+2, kantai);
    //        }
    //
    //    }
    
    
    
    //
    //    auto Lfleet=sPlayer.getFleetByFleetKey(2);
    //    auto Rfleet=sPlayer.getFleetByFleetKey(1);
    //
    //    for (int i=30; i<=40; ++i)
    //    {
    //        auto kantai=sPlayer.getKantaiByKantaiKey(i);
    //        sPlayer.removeEquip(kantai, 2);
    //    }
    
    //    Fleet* tmp=NULL;
    //    bool pointer=true;
    //    for (int i=0; i<20; ++i)
    //    {
    //        if (pointer) {tmp=Rfleet;}
    //        else    {tmp=Lfleet;}
    //        for (int i=0; i<5; ++i)
    //        {
    //            auto lKantai=sPlayer.getKantaiByKantaiKey(36+i);
    //            if (sPlayer.canModifyKantaiPosition(tmp, i+1, lKantai))
    //            {
    //                sPlayer.modifyKantaiPosition(tmp, i+1, lKantai);
    //            }
    //        }
    //        pointer=!pointer;
    //    }
    
    //    auto rKantai=sPlayer.getKantaiByKantaiKey(31+i);
    //    if (sPlayer.canModifyKantaiPosition(Rfleet, i+1, rKantai)) {
    //        sPlayer.modifyKantaiPosition(Rfleet, i+1,rKantai);
    //    }
    
    //    if (sPlayer.canChangeKantaiPosition(sPlayer.getFleetByFleetKey(1), 1, sPlayer.getKantaiByKantaiKey(30)))
    //    {
    //        sPlayer.changeKantaiPosition(sPlayer.getFleetByFleetKey(1), 1, sPlayer.getKantaiByKantaiKey(30));
    //    }
    
    
    //    for (int i=1; i<=4; ++i)
    //    {
    //        auto fleet=sPlayer.getFleetByFleetKey(i);
    //        if (sPlayer.canRemoveAllKantai(fleet))
    //        {
    //            sPlayer.removeAllKantai(fleet);
    //        }
    //    }
    
    //    int count=5;
    //    auto fleet=sPlayer.getFleetByFleetKey(4);
    //    for (int i=1; i<=6; ++i)
    //    {
    //        auto kantai=fleet->getShip(i);
    //        if (kantai)
    //        {
    //            if(sPlayer.canSwapKantai(kantai, sPlayer.kantaiData[count+10]))
    //                sPlayer.swapKantai(kantai, sPlayer.kantaiData[count+10]);
    //        }
    //        else
    //        {
    //            if (sPlayer.canChangeKantaiPosition(fleet, i,sPlayer.kantaiData[count+10])) {
    //                sPlayer.changeKantaiPosition(fleet, i,sPlayer.kantaiData[count+10]);
    //            }
    //        }
    //        ++count;
    //    }
    
    //    while (sPlayer.kantaiData.size()!=1)
    //    {
    //        int i=0;
    //        auto kantai=sPlayer.kantaiData[i];
    //        if (kantai==sPlayer.getFlagShip()) {
    //            ++i;
    //        }
    //        if (sPlayer.canDeleteKantai(sPlayer.kantaiData[i]))
    //        {
    //            log("%d",sPlayer.kantaiData[i]->getKantaiKey());
    //            sPlayer.deleteKantai(sPlayer.kantaiData[i]);
    //        }
    //    }
    
    
    //    if (sPlayer.canModifyKantaiPosition(sPlayer.getFleetByFleetKey(1), 1, sPlayer.getKantaiByKantaiKey(41))) {
    //        sPlayer.modifyKantaiPosition(sPlayer.getFleetByFleetKey(1), 1, sPlayer.getKantaiByKantaiKey(41));
    //    }
    
    
    
    
    //auto player=sPlayer;
    //    if (player.canMinusAluminium(10000))
    //    {
    //        player.minusAluminium(10000);
    //    }
    //    if (player.canMinusAmmo(10000)) {
    //        player.minusAmmo(10000);
    //    }
    //    if (player.canMinusFuel(10000)) {
    //        player.minusFuel(10000);
    //    }
    //    if (player.canMinusSteel(10000)) {
    //        player.minusSteel(10000);
    //    }
    
    
//    
//    player.addAmmo(10000);
//    player.addFuel(10000);
//    player.addSteel(10000);
//    player.addPlayerCurrExp(10000);
//    log("AL: %d",player.getAluminium());
//    log("ammo: %d",player.getAmmo());
//    log("fuel: %d",player.getFuel());
//    log("steel: %d",player.getSteel());
//    log("exp: %d",player.getCurrExp());
//    log("updateExp: %d",player.getUpdateExp());
//    log("currLV: %d",player.getCurrLV());
//    log("maxAL: %d",player.getMaxAluminium());
//    log("maxAmmo: %d",player.getMaxAmmo());
//    log("maxFuel: %d",player.getMaxFuel());
//    log("maxSteel: %d",player.getMaxSteel());
//    
    
}





