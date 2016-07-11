//
//  signBoardGirl.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/8/16.
//
//

#include "signBoardGirl.hpp"
#include "player.h"

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


bool SignBoardGirl::init()
{
    bool bRet=false;
    do
    {
        girl=Sprite::create();
        girl->runAction(RepeatForever::create((ActionInterval*)Sequence::create(ScaleTo::create(4,1.02),ScaleTo::create(4, 1), NULL)));
        girl->setPosition(Vec2::ZERO);
        addChild(girl);
        
        updateGirl();
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}



NS_KCL_END