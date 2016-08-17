//
//  portFactoryLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portFactoryLayer.h"
#include "KantaiDestroyEntity.hpp"
#include "EventPauseGuard.hpp"
#include "Sound.hpp"
#include "LayerCover.hpp"

NS_KCL_BEGIN


PortFactoryLayer::PortFactoryLayer()
{
    container.resize(4);
    arsenalPosition=0;
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
        initDestroyShipEntity();
        
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
    
    auto pos=Vec2(1150, tmp.height);
    entity=BuildKantaiEntity::create(kantaiBuilding,-pos);
    entity->setPosition(pos);
    addChild(entity,3);
}


////////build
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
    arsenalPosition=position;
    entity->moveIn();
}


void PortFactoryLayer::startBuild(int fuel, int steel, int ammo, int al)
{
    if (arsenalPosition==0) return;
    
    sArsenal.buildNewKantai(arsenalPosition, fuel,steel,ammo,al, 10);
    container[arsenalPosition-1]->update();
    arsenalPosition=0;
    
    CallFunc* actionPre=CallFunc::create([=]()
    {
         EventPauseGuard::pause();
    });
    CallFunc* p1=CallFunc::create([=]()
    {
        entity->moveOut(this);
    });
    CallFunc* actionPost=CallFunc::create([=]()
    {
        EventPauseGuard::resume();
        entity->updateRes();
    });
    runAction(Sequence::create(actionPre,p1,DelayTime::create(0.26),actionPost, NULL));
}

///////destory
void PortFactoryLayer::initDestroyShipEntity()
{
    auto visible=Director::getInstance()->getVisibleSize();
    auto listPos=Vec2(visible.width, 200);
    destoryList=FactoryListEntity::create(listPos);
    addChild(destoryList,3);
    destoryList->setPosition(listPos);
    destoryList->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    
    auto pos=Vec2(695,200);
    kantaiDestroyEntity=KantaiDestroyEntity::create(pos);
    kantaiDestroyEntity->setPosition(pos);
    addChild(kantaiDestroyEntity,4);
}


void PortFactoryLayer::showDestroy(Ref* pSender)
{
    destoryList->moveIn();
}

void PortFactoryLayer::showSelect(kancolle::Kantai *kantai)
{
    kantaiDestroyEntity->moveIn();
    kantaiDestroyEntity->update(kantai);
}

void PortFactoryLayer::destroyCallback(Kantai* kantai,int fuel,int steel,int ammo,int al)
{
    SND->playEffect("soundSE/scrapShip.mp3");
    CallFunc* actionPre=CallFunc::create([=]()
                                 {
                                     EVENT_PAUSE;
                                 });
    CallFunc* f1=CallFunc::create([=]()
                                  {
                                      destroyKantai(kantai, fuel, steel, ammo, al);
                                      destoryList->destoryKantai(kantai);
                                  });
    CallFunc* f2=CallFunc::create([=]()
                                  {
                                      kantaiDestroyEntity->moveOut();
                                  });

    CallFunc* f3=CallFunc::create([=]()
                                  {
                                      destoryList->moveOut();
                                  });
    CallFunc* f4=CallFunc::create([=]()
                                  {
                                      destoryList->updateRows();
                                  });
    CallFunc* actionPost=CallFunc::create([=]()
                                  {
                                      EVENT_RESUME;
                                  });
    this->runAction(Sequence::create(actionPre,f1,f2,DelayTime::create(0.2),f3,DelayTime::create(0.5),f4,actionPost, NULL));
}

void PortFactoryLayer::destroyKantai(Kantai *kantai, int fuel, int steel, int ammo, int al)
{
    sPlayer.deleteKantai(kantai);
    sPlayer.addAluminium(al);
    sPlayer.addFuel(fuel);
    sPlayer.addSteel(steel);
    sPlayer.addAmmo(ammo);
}

void PortFactoryLayer::finishBuildingKantai(int position)
{
    auto kantai=sArsenal.finishBuildingKantai(position);
    destoryList->addKantai(kantai);
}


/////other
void PortFactoryLayer::NullCallback(cocos2d::Ref *pSender)
{
    
}



NS_KCL_END