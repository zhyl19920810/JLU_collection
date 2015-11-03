#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "DatabaseScene.h"
#include "XMLBuilder.h"
#include "databaseInit.h"
#include "databaseBase.h"
#include "portScene.h"
#include "GameScene.h"

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
    director->getOpenGLView()->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);
    glview->setFrameSize(800, 480);
    
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    //init db
    DBBase::init("/Volumes/opengl/kancolle_alpha/Resources/database/kancolle_2.sqlite3");
    DBInit init;
    auto player=Player::getInstance();
    player=init.initDB(1);
    
    if (DEBUG_MODE)
    {
        Fleet* allies=Player::getInstance()->fleetData[0];
        
        
        
        Fleet* enemy=Player::getInstance()->fleetData[0];
        auto battleModel=new BattleModel(allies,enemy,DanZong,DanZong);
        GameScene* scene=new GameScene(battleModel);
        director->runWithScene(scene);
        
    }
    
//    // create a scene. it's an autorelease object
//    auto scene = DatabaseLayer::createScene();
//    // run
//    director->runWithScene(scene);

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
