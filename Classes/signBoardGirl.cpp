//
//  signBoardGirl.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/8/16.
//
//

#include "signBoardGirl.hpp"
#include "player.h"
#include "Sound.hpp"

NS_KCL_BEGIN




SignBoardGirl::SignBoardGirl():
girl(NULL)
{
    
}



void SignBoardGirl::updateGirl(cocos2d::Sprite* sprite)
{
    char resource[50];
    bzero(resource, sizeof(resource));
    auto fleet1=sPlayer.fleetData;
    int num=sPlayer.fleetData[0]->ship[0]->getKantaiNumber();
    sprintf(resource, "kantai/%d/image 17.png",num);


    girl->setTexture(resource);

    int height=girl->getContentSize().height;
    if (height>799)
    {
        girl->setAnchorPoint(Vec2(0.5, 0.45));
    }
    else if(height>699)
    {
        girl->setAnchorPoint(Vec2(0.5, 0.25));
    }
}

SignBoardGirl* SignBoardGirl::create()
{
    SignBoardGirl* p_Ret=new SignBoardGirl;
    if (p_Ret&&p_Ret->init())
    {
        p_Ret->autorelease();
        return p_Ret;
    }
    delete p_Ret;
    p_Ret=NULL;
    return p_Ret;
}
#define INITSIZE 0.75

bool SignBoardGirl::init()
{
    bool bRet=false;
    do
    {
        girl=Sprite::create();
        girl->setScale(INITSIZE);
        girl->runAction(RepeatForever::create((ActionInterval*)Sequence::create(ScaleTo::create(4,1.04*INITSIZE),ScaleTo::create(4, 1*INITSIZE), NULL)));
        girl->runAction(RepeatForever::create((ActionInterval*)Sequence::create(MoveBy::create(4,Vec2(6, 10)),MoveBy::create(4,Vec2(-6, -10)), NULL)));
        auto winSize=Director::getInstance()->getWinSize();
        girl->setPosition(Vec2::ZERO);
        addChild(girl);

        
        updateGirl();
        
        _eventListner=EventListenerTouchOneByOne::create();
        _eventListner->onTouchBegan=CC_CALLBACK_2(SignBoardGirl::onTouchBegan, this);
        _eventListner->onTouchMoved=CC_CALLBACK_2(SignBoardGirl::onTouchMoved, this);
        _eventListner->onTouchEnded=CC_CALLBACK_2(SignBoardGirl::onTouchEnded, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_eventListner, girl);
        
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}

bool SignBoardGirl::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void SignBoardGirl::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    
}


void SignBoardGirl::onTouchEnded(Touch* touch, Event* event)
{
    auto pos=touch->getLocation();
    auto rect=Rect(30, 30, girl->getContentSize().width-30, girl->getContentSize().height-30);
    auto loc=girl->convertToNodeSpace(pos);
    if (rect.containsPoint(loc))
    {
        int num=sPlayer.fleetData[0]->ship[0]->getKantaiNumber();
        srand((unsigned)time(NULL));
        
        char resource[50];
        bzero(resource, sizeof(resource));
        sprintf(resource, "kantaiVoice/%d/%d.mp3",num,rand()%5);
        SND->stopAllEffects();
        SND->playEffect(resource);
    }

}

void SignBoardGirl::setEnable()
{
    _eventListner->setEnabled(true);
}

void SignBoardGirl::setDisable()
{
    _eventListner->setEnabled(false);
}

NS_KCL_END