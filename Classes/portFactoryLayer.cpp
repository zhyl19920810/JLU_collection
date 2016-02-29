//
//  portFactoryLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portFactoryLayer.h"

PortFactoryLayer::PortFactoryLayer()
{
    container.resize(sPlayer.getMaxDockSize());
}


bool PortFactoryLayer::init()
{
    bool bRet=false;
    do
    {
        if (!Layer::init())
        {
            break;
        }
        initLayer();
        initContainer();
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}


void PortFactoryLayer::initLayer()
{
    auto factoryBar=Sprite::create("ArsenalMain/titleBar.png");
    this->addChild(factoryBar);
    factoryBar->setPosition(400,395);
    
    auto factorTitle=Sprite::create("ArsenalMain/factoryTitle.png");
    this->addChild(factorTitle);
    factorTitle->setPosition(175,400);
    
    bgimg = Sprite::create("ArsenalMain/factoryBg.png");
    this->addChild(bgimg);
    bgimg->setOpacity(200);
    bgimg->setPosition(450, 195);
    
    auto tmp=bgimg->getContentSize()/2;
    arsenalBg = Sprite::create("ArsenalMain/arsenalBg.png");
    bgimg->addChild(arsenalBg);
    arsenalBg->setPosition(Vec2(tmp.width+125, tmp.height-10));
    
    log("%f %f",arsenalBg->getPosition().x-arsenalBg->getContentSize().width/2,arsenalBg->getPosition().y-arsenalBg->getContentSize().height/2);//arsenal左下角为253，2.5
    auto arsenalLB=arsenalBg->getPosition()-arsenalBg->getContentSize()/2;
    auto arsenalUpright1=Sprite::create("ArsenalMain/arsenalUpright.png");
    arsenalBg->addChild(arsenalUpright1);
    arsenalUpright1->setPosition(Vec2(30, 180));
    
    auto arsenalUpright2=Sprite::create("ArsenalMain/arsenalUpright.png");
    arsenalBg->addChild(arsenalUpright2);
    arsenalUpright2->setPosition(Vec2(150, 180));
    
    
    auto buildButton = MenuItemImage::create("ArsenalMain/buildBotton1.png", "ArsenalMain/buildBotton2.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    buildButton->setPosition(-225,115);
    auto disassembleButton = MenuItemImage::create("ArsenalMain/disassembleButton1.png", "ArsenalMain/disassembleButton2.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    disassembleButton->setPosition(-225, 40);
    auto developButton = MenuItemImage::create("ArsenalMain/developButton1.png", "ArsenalMain/developButton2.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    developButton->setPosition(-225, -45);
    auto discardButton = MenuItemImage::create("ArsenalMain/discardButton1.png", "ArsenalMain/discardButton2.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    discardButton->setPosition(-225, -125);
    
    menu = Menu::create(buildButton, disassembleButton, developButton, discardButton, NULL);
    menu->setPosition(tmp);
    bgimg->addChild(menu);
    
    entity=BuildKantaiEntity::create(kantaiBuilding);
    entity->setPosition(1150,tmp.height);
    addChild(entity);
    
    auto closeItem2 = Sprite::create("CommonAssets/image 451.png");
    closeItem2->setGlobalZOrder(10);
    closeItem2->setOpacity(0);
    hideListItem = MenuItemSprite::create(closeItem2, closeItem2, CC_CALLBACK_1(PortFactoryLayer::hideCallback, this));
    hideListItem->setPosition(Vec2(-600,0));
    hideListItem->setEnabled(false);
    menu->addChild(hideListItem);
    hideListItem->setGlobalZOrder(10);
    
}

void PortFactoryLayer::hideCallback(cocos2d::Ref *pSender)
{
    hideListItem->setEnabled(false);
    entity->hideEntity();
}

void PortFactoryLayer::initContainer()
{
    
}



void PortFactoryLayer::callBack(Ref* pSender)
{
    entity->showEntity();
    hideListItem->setEnabled(true);
}



