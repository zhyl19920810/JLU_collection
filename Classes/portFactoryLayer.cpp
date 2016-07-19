//
//  portFactoryLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portFactoryLayer.h"

NS_KCL_BEGIN


PortFactoryLayer::PortFactoryLayer()
{
    //container.resize(sPlayer.getMaxDockSize());
    container.resize(4);
}


bool PortFactoryLayer::init()
{
    bool bRet=false;
    do
    {
        if (!Panel::init())
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
    
    
    auto buildButton = MenuItemImage::create("ArsenalMain/buildBotton1.png", "ArsenalMain/buildBotton1.png");
    buildButton->setPosition(-225,115);
    auto disassembleButton = MenuItemImage::create("ArsenalMain/disassembleButton1.png", "ArsenalMain/disassembleButton2.png", CC_CALLBACK_1(PortFactoryLayer::showDestroy, this));
    disassembleButton->setPosition(-225, 40);
    auto developButton = MenuItemImage::create("ArsenalMain/developButton1.png", "ArsenalMain/developButton2.png", CC_CALLBACK_1(PortFactoryLayer::NullCallback, this));
    developButton->setPosition(-225, -45);
    auto discardButton = MenuItemImage::create("ArsenalMain/discardButton1.png", "ArsenalMain/discardButton2.png", CC_CALLBACK_1(PortFactoryLayer::NullCallback, this));
    discardButton->setPosition(-225, -125);
    
    menu = Menu::create(buildButton, disassembleButton, developButton, discardButton, NULL);
    menu->setPosition(tmp);
    bgimg->addChild(menu);
    
    
    destoryCover=LayerCover::create(CC_CALLBACK_1(PortFactoryLayer::hideDestroy, this));
    destoryCover->setPosition(0,0);
    addChild(destoryCover,2);
    
    listCover=LayerCover::create(CC_CALLBACK_1(PortFactoryLayer::hideList, this));
    listCover->setPosition(0,0);
    addChild(listCover,2);
    
    
    entity=BuildKantaiEntity::create(kantaiBuilding);
    entity->setPosition(1150,tmp.height);
    addChild(entity,3);
    
    
    auto visible=Director::getInstance()->getVisibleSize();
    destoryList=FactoryListEntity::create();
    addChild(destoryList,3);
    destoryList->setPosition(visible.width,0);
    
}

void PortFactoryLayer::hideDestroy(Ref* pSender)
{
    destoryList->moveOut();
    destoryCover->setCoverEnable(false);
    //destoryHideItem->setEnabled(false);
}

void PortFactoryLayer::hideList(cocos2d::Ref *pSender)
{
    //hideListItem->setEnabled(false);
    listCover->setCoverEnable(false);
    entity->hideEntity();
}

void PortFactoryLayer::initContainer()
{
    for (int i=0; i<4; ++i)
    {
        container[i]=FactoryContainer::create(i+1);
        container[i]->setPosition(390,275-i*78);
        addChild(container[i]);
    }
}

void PortFactoryLayer::showList(int position)
{
    UserDefault::getInstance()->setIntegerForKey("arsenalPosition", position);
    entity->showEntity();
    listCover->setCoverEnable(true);
}

void PortFactoryLayer::showDestroy(Ref* pSender)
{
    destoryList->moveIn();
    destoryCover->setCoverEnable(true);
}



//void PortFactoryLayer::callBack(Ref* pSender)
//{
//    entity->showEntity();
//    listCover->setCoverEnable(true);
//}

void PortFactoryLayer::startBuild(int fuel, int steel, int ammo, int al)
{
    int position=UserDefault::getInstance()->getIntegerForKey("arsenalPosition");
    UserDefault::getInstance()->setIntegerForKey("arsenalPosition",0);
    if (position==0) {
        return;
    }
    sArsenal.buildNewKantai(position, fuel,steel,ammo,al, 10);
    container[position-1]->update();
    hideList(this);
}


void PortFactoryLayer::destroyKantai(Kantai *kantai, int fuel, int steel, int ammo, int al)
{
    sPlayer.deleteKantai(kantai);
    sPlayer.addAluminium(al);
    sPlayer.addFuel(fuel);
    sPlayer.addSteel(steel);
    sPlayer.addAmmo(ammo);
}


void PortFactoryLayer::NullCallback(cocos2d::Ref *pSender)
{
    
}


NS_KCL_END