//
//  FleetButton.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/1/16.
//
//

#include "FleetButton.hpp"


NS_KCL_BEGIN

FleetButton::FleetButton()
{
    fleetToggle.resize(4);
    //fleetSprite.resize(4);
    fleetNumber=1;
}


bool FleetButton::init(ButtonUpdate buttonUpdate)
{
    bool bRet=false;
    do
    {
        if (!Node::init())
        {
            break;
        }
        
        this->buttonUpdate=buttonUpdate;
        fleetToggle[0]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(FleetButton::fleetCallback, this,1), MenuItemSprite::create(Sprite::createWithSpriteFrameName("one2.png"), Sprite::createWithSpriteFrameName("one2.png"),Sprite::createWithSpriteFrameName("one1.png")),
                                                          MenuItemSprite::create(Sprite::createWithSpriteFrameName("one3.png"), Sprite::createWithSpriteFrameName("one3.png")), NULL);
        fleetToggle[0]->setPosition(Vec2::ZERO);
        
        
        
        fleetToggle[1]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(FleetButton::fleetCallback, this,2), MenuItemSprite::create(Sprite::createWithSpriteFrameName("two2.png"), Sprite::createWithSpriteFrameName("two2.png"),Sprite::createWithSpriteFrameName("two1.png")),
                                                          MenuItemSprite::create(Sprite::createWithSpriteFrameName("two3.png"), Sprite::createWithSpriteFrameName("two3.png")), NULL);
        fleetToggle[1]->setPosition(fleetToggle[0]->getPosition()+Vec2(30, 0));
        
        
        
        
        fleetToggle[2]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(FleetButton::fleetCallback, this,3), MenuItemSprite::create(Sprite::createWithSpriteFrameName("three2.png"), Sprite::createWithSpriteFrameName("three2.png"),Sprite::createWithSpriteFrameName("three1.png")),
                                                          MenuItemSprite::create(Sprite::createWithSpriteFrameName("three3.png"), Sprite::createWithSpriteFrameName("three3.png")), NULL);
        fleetToggle[2]->setPosition(fleetToggle[1]->getPosition()+Vec2(30, 0));
        
        
        
        
        fleetToggle[3]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(FleetButton::fleetCallback, this,4), MenuItemSprite::create(Sprite::createWithSpriteFrameName("four2.png"), Sprite::createWithSpriteFrameName("four2.png"),Sprite::createWithSpriteFrameName("four1.png")),
                                                          MenuItemSprite::create(Sprite::createWithSpriteFrameName("four3.png"), Sprite::createWithSpriteFrameName("four3.png")), NULL);
        fleetToggle[3]->setPosition(fleetToggle[2]->getPosition()+Vec2(30, 0));
        
        auto mn=Menu::create(fleetToggle[0],fleetToggle[1],fleetToggle[2],fleetToggle[3], NULL);
        mn->setPosition(Vec2::ZERO);
        addChild(mn);
        
        fleetToggle[0]->setSelectedIndex(1);
        for (int i=1; i<=4; ++i)
        {
            if (sPlayer.getFleetByFleetKey(i)) fleetToggle[i-1]->setEnabled(true);
            else                              fleetToggle[i-1]->setEnabled(false);
        }
        bRet=true;
    }while(0);
    
    return bRet;
}

void FleetButton::fleetCallback(cocos2d::Ref *pSender, int layNumber)
{
    auto toggle=dynamic_cast<MenuItemToggle*>(pSender);
    if (toggle->getSelectedIndex())  //关到开
    {
        if (layNumber==fleetNumber)
        {
            toggle->setSelectedIndex(0);
            return;
        }
        fleetToggle[fleetNumber-1]->setSelectedIndex(0);
        
        changeFleet(layNumber);
    }
    else  //开到关
    {
        toggle->setSelectedIndex(1);
    }
}

void FleetButton::changeFleet(int fleetNumber)
{
    this->fleetNumber=fleetNumber;
    update(fleetNumber);
}

void FleetButton::update(int fleetNumber)
{
    buttonUpdate(fleetNumber);
}

void FleetButton::SetFleetButtonVisible(int fleetNumber, bool bVisible)
{
//    if (bVisible)
//    {
//        fleetToggle[fleetNumber-1]->setVisible(true);
//        fleetSprite[fleetNumber-1]->setVisible(false);
//    }
//    else
//    {
//        fleetToggle[fleetNumber-1]->setVisible(false);
//        fleetSprite[fleetNumber-1]->setVisible(true);
//    }
}

NS_KCL_END
