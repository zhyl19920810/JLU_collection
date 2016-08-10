//
//  portBattleLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portBattleLayer.h"
#include "Player.h"


NS_KCL_BEGIN

bool PortBattleLayer::init()
{
    bool bRet=false;
    do
    {
        if (!Panel::init()) {
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
    
    
    auto playactButton = MenuItemImage::create("interface/SallyMain/SallyMain_366.png", "interface/SallyMain/SallyMain_368.png", CC_CALLBACK_1(PortBattleLayer::callBack1, this));
    playactButton->setPosition(450, 240);
    
    
    auto expeditionButton = MenuItemImage::create("interface/SallyMain/SallyMain_371.png", "interface/SallyMain/SallyMain_373.png", CC_CALLBACK_1(PortBattleLayer::callBack2, this));
    expeditionButton->setPosition(670, 240);
    
    
    auto menu = Menu::create(strikeButton, playactButton, expeditionButton, NULL);
    //	menu->addChild(strikeDescription);
    //	menu->addChild(playactDescription);
    //	menu->addChild(expeditionDescription);
    menu->setPosition(0, 0);
    this->addChild(menu);
    
}

void PortBattleLayer::callBack1(Ref* pSender)
{}

void PortBattleLayer::callBack2(Ref* pSender)
{}

void PortBattleLayer::ShowMissionSelectPage(Ref* pSender)
{
    auto fleet=sPlayer.getFleetByFleetKey(1);
    for(int i=1;i<=6;++i)
    {
        auto kantai=fleet->getShip(i);
        if (kantai)
        {
            kantai->setCurrAmmo(kantai->getCurrAmmo()*0.9);
            kantai->setCurrFuel(kantai->getCurrFuel()*0.9);
            kantai->setCurrHp(kantai->getCurrHp()*0.9);
        }
        
    }

    
}

void PortBattleLayer::hideMissionPage()
{
    //this->missionPage->moveOut();
}


NS_KCL_END

