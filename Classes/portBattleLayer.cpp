//
//  portBattleLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portBattleLayer.h"
#include "MissionSelectPage.h"


NS_KCL_BEGIN

bool PortBattleLayer::init()
{
    bool bRet=false;
    do
    {
        if (!Layer::init()) {
            break;
        }
        initLayer();
        
        
        bRet=true;
    }while(0);
    return bRet;
}


void PortBattleLayer::initLayer()
{
    auto bgimg = Sprite::create("interface/PortMain/image 350.jpg");
    this->addChild(bgimg);
    bgimg->setOpacity(255);
    bgimg->setZOrder(-4);
    bgimg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    
//    auto top_bar = Sprite::create("interface/SallyMain/SallyMain_235.png");
//    this->addChild(top_bar);
//    top_bar->setPosition(450, 397);
    
    auto top_label = Sprite::create("interface/SallyMain/SallyMain_359.png");
    this->addChild(top_label);
    top_label->setPosition(160, 397);
    
    auto strikeButton = MenuItemImage::create("interface/SallyMain/SallyMain_361.png", "interface/SallyMain/SallyMain_363.png", CC_CALLBACK_1(PortBattleLayer::ShowMissionSelectPage, this));
    strikeButton->setPosition(230, 240);
//    auto strikeDescription = Sprite::create("SallyMain/image 388.png");
//    strikeDescription->setPosition(230, 80);
    
    auto playactButton = MenuItemImage::create("interface/SallyMain/SallyMain_366.png", "interface/SallyMain/SallyMain_368.png", CC_CALLBACK_1(PortBattleLayer::callBack1, this));
    playactButton->setPosition(450, 240);
//    auto playactDescription = Sprite::create("Resources/interface/SallyMain/image 386.png");
//    playactDescription->setPosition(450, 80);
    
    auto expeditionButton = MenuItemImage::create("interface/SallyMain/SallyMain_371.png", "interface/SallyMain/SallyMain_373.png", CC_CALLBACK_1(PortBattleLayer::callBack2, this));
    expeditionButton->setPosition(670, 240);
//    auto expeditionDescription = Sprite::create("Resources/interface/SallyMain/image 387.png");
//    expeditionDescription->setPosition(670, 80);
    
    
    auto menu = Menu::create(strikeButton, playactButton, expeditionButton, NULL);
    //	menu->addChild(strikeDescription);
    //	menu->addChild(playactDescription);
    //	menu->addChild(expeditionDescription);
    menu->setPosition(0, 0);
    this->addChild(menu);
    
    //Sub Pages
    missionPage = new MissionSelectPage(this);
    missionPage->setPosition(800, 0);
    this->addChild(missionPage);
}

void PortBattleLayer::callBack1(Ref* pSender)
{}

void PortBattleLayer::callBack2(Ref* pSender)
{}

void PortBattleLayer::ShowMissionSelectPage(Ref* pSender)
{
    if (missionPage->isHidden())
    {
        missionPage->moveIn();
    }
    
}

void PortBattleLayer::hideMissionPage()
{
    //this->missionPage->moveOut();
}


NS_KCL_END

