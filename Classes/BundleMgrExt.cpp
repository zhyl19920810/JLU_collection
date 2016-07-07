//
//  BundleMgrExt.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#include "portScene.h"
#include "ViewMgr.hpp"
#define CACHE (UserDefault::getInstance())

NS_KCL_BEGIN

void exeLaunch()
{
    kancolle::ViewMgr::getInstance()->showScene(kancolle::SceneType::HOME);
    //Director::getInstance()->runWithScene(PortScene::createScene());
    //Director::getInstance()->runWithScene(RegexTest::create());
    //cocos2d::Director::getInstance()->runWithScene(AnimTest::create());
    //cocos2d::Director::getInstance()->runWithScene(UITest::create());
    //cocos2d::Director::getInstance()->runWithScene(BattleDisplayTest::scene());
    //cocos2d::Director::getInstance()->runWithScene(DialogueTest::scene());
    //cocos2d::Director::getInstance()->runWithScene(RegexTest::create());
    //cocos2d::Director::getInstance()->runWithScene(GridViewTest::scene());
    //cocos2d::Director::getInstance()->runWithScene(HotpotTest::create());
    //cocos2d::Director::getInstance()->runWithScene(LabelTextTest::create());
    //cocos2d::Director::getInstance()->runWithScene(HomeRoleTest::scene());
    //cocos2d::Director::getInstance()->runWithScene(LuaTest::scene());
}


NS_KCL_END
