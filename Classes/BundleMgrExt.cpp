//
//  BundleMgrExt.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#include "portScene.h"

#define CACHE (UserDefault::getInstance())


void exeLaunch()
{
    Director::getInstance()->runWithScene(PortScene::createScene());
    //VIEW_MGR->showScene(SceneType::LOGO);
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