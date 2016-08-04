//
//  TitlePic.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/3/16.
//
//

#include "TitlePic.hpp"


NS_KCL_BEGIN

USING_NS_CC;

#define FADE_TIME 0.8


TitlePic* TitlePic::create()
{
    TitlePic* pRet=new TitlePic;
    if (pRet&&pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}



void TitlePic::changeTitlePic(kancolle::PanelType type,float delayTime)
{
    
    if (currType==type)  return;
    
    currType=type;
    float rotateAngle=getRotation();
    std::string titleName;
    
    switch (type) {
        case PanelType::PORT_MAINLAYER:
            titleName="porttitle.png";
            break;
        case PanelType::PORT_SUPPLY:
            titleName="supplytitle.png";
            break;
        case PanelType::PORT_FACTORY:
            titleName="factorytitle.png";
            break;
        case PanelType::PORT_ORGANIZE:
            titleName="organizetitle.png";
            break;
        case PanelType::PORT_REMODE:
            titleName="remodeltitle.png";
            break;
        case PanelType::PORT_REPAIR:
            titleName="repairtitle.png";
            break;
        case PanelType::PORT_BATTLE:
            titleName="battletitle.png";
            break;
        default:
            title->setVisible(false);
            break;
    }
    
    preTitle->setSpriteFrame(titleName);

    changeAction(delayTime);
    
}

void TitlePic::changeAction(float delayTime)
{
    ActionInterval* p1;
    {
        CallFunc* callBefore=CallFunc::create([=]()
        {
            title->setOpacity(255);
            title->setVisible(true);
            preTitle->setOpacity(0);
            preTitle->setVisible(true);
       });
        CallFunc* fadeAction=CallFunc::create([=]()
       {
           title->runAction(FadeTo::create(delayTime, 0));
           preTitle->runAction(FadeTo::create(delayTime, 255));
       });
        CallFunc* callAfter=CallFunc::create([=]()
        {
            auto spriteTemp=preTitle->getSpriteFrame();
            preTitle->setSpriteFrame(title->getSpriteFrame());
            title->setSpriteFrame(spriteTemp);
            title->setOpacity(255);
            preTitle->setOpacity(0);
            preTitle->setVisible(false);
            title->setVisible(true);
       });
        p1=Sequence::create(callBefore,fadeAction,DelayTime::create(delayTime+0.1),callAfter, NULL);
    }
    runAction(p1);
}



bool TitlePic::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::create());
        
        currType=PanelType::PORT_MAINLAYER;
        RotateBy* circleAction1=RotateBy::create(1, 13);
        RepeatForever* repeat1=RepeatForever::create((ActionInterval*)circleAction1);
        title=Sprite::createWithSpriteFrameName("porttitle.png");
        title->setPosition(Vec2::ZERO);
        title->runAction(repeat1);
        addChild(title);
        
        RotateBy* circleAction2=RotateBy::create(1, 13);
        RepeatForever* repeat2=RepeatForever::create((ActionInterval*)circleAction2);
        preTitle=Sprite::createWithSpriteFrameName("remodeltitle.png");
        preTitle->setPosition(Vec2::ZERO);
        preTitle->runAction(repeat2);
        preTitle->setVisible(false);
        addChild(preTitle);
        
        fadeCover=Sprite::createWithSpriteFrameName("shader.png");
        fadeCover->setPosition(Vec2::ZERO);
        fadeCover->setOpacity(10);
        fadeCover->runAction(RepeatForever::create((ActionInterval*)Sequence::create(FadeTo::create(1.5, 170),FadeTo::create(1.5, 10), NULL)));
        addChild(fadeCover);
        
        bRet=true;
    }while (0);
    return bRet;
}






NS_KCL_END