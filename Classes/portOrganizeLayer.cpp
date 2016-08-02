//
//  portOrganizeLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portOrganizeLayer.h"
#include "PortScene.h"
#include "GameManger.hpp"
#include "Sound.hpp"
#include "EventPauseGuard.hpp"
#include <map>

NS_KCL_BEGIN

PortOrganizeLayer::PortOrganizeLayer()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CommonAssets/commonAssets.plist", "CommonAssets/commonAssets.pvr.ccz");
    containers.resize(6);
    for(int i=0;i<6;++i)
        containers[i]=NULL;
}

PortOrganizeLayer::~PortOrganizeLayer()
{
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("CommonAssets/commonAssets.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("CommonAssets/commonAssets.pvr.ccz");
}

bool PortOrganizeLayer::init()
{
    bool bRet=false;
    
    do
    {
        if (!Panel::init()) {
            break;
        }
        
        initLayer();
        initFleetButton();
        initContainers();
        bRet=true;
    }while(0);
    
    
    return bRet;
}


void PortOrganizeLayer::initLayer()
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    
    auto menu = Menu::create(NULL);
    menu->setPosition(Point::ZERO);
    fleet=sPlayer.getFleetByFleetKey(1);
    
    bgimg = Sprite::create("OrganizeMain/organizeBg.png");
    addChild(bgimg);
    bgimg->setOpacity(250);
    bgimg->setPosition(450, 200);
    
    
    auto top_label = Sprite::create("OrganizeMain/topLabel.png");
    addChild(top_label);
    top_label->setPosition(bgimg->getPosition()+Vec2(0, 197)+Vec2(-290, 4));
    
    auto clearFleetButton = MenuItemImage::create("OrganizeMain/closeFleet1.png", "OrganizeMain/closeFleet2.png", CC_CALLBACK_1(PortOrganizeLayer::clearFleetCallback, this));
    
    
    clearFleetButton->setPosition(415, 365);
    menu->addChild(clearFleetButton);
    addChild(menu);
    
    auto fleet_name_text_box = Sprite::create("OrganizeMain/inputFleetName.png");
    fleet_name_text_box->setPosition(clearFleetButton->getPosition()+Vec2(185, 5));
    addChild(fleet_name_text_box);
    
    auto editFleetNameButton = Sprite::create("OrganizeMain/editFleetNameButton.png");
    addChild(editFleetNameButton);
    editFleetNameButton->setAnchorPoint(Vec2(0, 0.5));
    editFleetNameButton->setPosition(fleet_name_text_box->getPosition()+Vec2(fleet_name_text_box->getContentSize().width/2, 0));
    

    listCover=LayerCover::create(CC_CALLBACK_1(PortOrganizeLayer::hideList, this));
    listCover->setPosition(0,0);
    addChild(listCover,2);
    
    detailEntity=KantaiDetailEntity::create();
    addChild(detailEntity,3);
    detailEntity->setPosition(visibleSize.width,0);
    detailEntity->setKantai(fleet->getShip(1));
    
    listEntity=KantaiListEntity::create();
    addChild(listEntity,3);
    listEntity->setPosition(visibleSize.width,0);
    
    organSelectEntity=OrganSelectEntity::create();
    organSelectEntity->setPosition(238,0);
    addChild(organSelectEntity,4);
    
}

void PortOrganizeLayer::initContainers()
{
    for (int i = 0; i < 6; i++)
    {
        containers[i]=OrganizeContainer::create(i+1);
        if (i == 0)
            containers[i]->setPosition(290, 300);
        else if (i == 1)
            containers[i]->setPosition(628, 300);
        else if (i == 2)
            containers[i]->setPosition(290, 190);
        else if (i == 3)
            containers[i]->setPosition(628, 190);
        else if (i == 4)
            containers[i]->setPosition(290, 80);
        else if (i == 5)
            containers[i]->setPosition(628, 80);
        addChild(containers[i]);
    }
    updateContainer();
    
    ///找到第一个没有船的位置，然后设其changeButton为visible
}


bool PortOrganizeLayer::canChangeKantai(Kantai* kantai)
{
    if (!kantai) return false;
    auto _fleet=static_cast<Fleet*>(kantai->getFleet());
    
    if (_fleet&&_fleet->getShip(selectedShipIndex))
    {
        if (getContainer(selectedShipIndex)->getKantai()&&getContainer(selectedShipIndex)->getContainerKantaiNumber()==kantai->getKantaiNumber())
        {
            return false;
        }
        return true;
    }
    
    for (int i=0; i<containers.size(); ++i)
    {
        if (containers[i]->haveKantai()&&(getContainer(i+1)->getContainerKantaiNumber()==kantai->getKantaiNumber()))
        {
            return false;
        }
    }
    return true;
}


OrganizeContainer* PortOrganizeLayer::getContainer(int index)
{
    return containers[index-1];
}


void PortOrganizeLayer::hideList(Ref* pSender)
{
    listEntity->moveOut();
    listCover->setCoverEnable(false);

}

void PortOrganizeLayer::showList(int index)
{
    if (listEntity->isHidden())
    {
        listEntity->moveIn();
    }
    listCover->setCoverEnable(true);
}


void PortOrganizeLayer::updateContainer()
{
    for (int i = 1; i <=6; i++)
    {
        updateContainer(i);
    }
    
    for (int i=1; i<=6; ++i)
    {
        if (!hasKantai(i))
        {
            kantaiSize=i-1;
            containers[kantaiSize-1+1]->setChangeButtonVisible(true);
            //containers[i-1]->setCoverVisble(true,false);
            return;
        }
    }
    kantaiSize=6;
}

void PortOrganizeLayer::updateContainer(int position)
{
    CCASSERT(position>=1&&position<=6, "position is not exist");
    auto kantai=fleet->getShip(position);
    containers[position-1]->updateCharacterInfo(kantai);
}


void PortOrganizeLayer::showDetail(int index)
{
    if (detailEntity->isHidden())
    {
        detailEntity->setKantai(fleet->getShip(index));
        detailEntity->moveIn();
    }
}



void PortOrganizeLayer::updateFleet(int _fleetNumber)
{
    if (fleetNumber!=_fleetNumber)
    {
        this->fleetNumber=_fleetNumber;
        fleet=sPlayer.getFleetByFleetKey(_fleetNumber);
        updateContainer();
    }
}

void PortOrganizeLayer::initFleetButton()
{
    fleetNumber=1;
    fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    fleetButton=FleetButton::create(std::bind(&PortOrganizeLayer::updateFleet, this,std::placeholders::_1));
    fleetButton->setPosition(47, bgimg->getContentSize().height-27);
    bgimg->addChild(fleetButton);
}


void PortOrganizeLayer::clearFleetCallback(Ref* ref)
{
    modifyContainer(kantaiChangeType::CLEAR_FLEET);
}


//void PortOrganizeLayer::clearFleet(cocos2d::Ref *pSender)
//{
//    for (int i=2; i<=kantaiSize; ++i)
//    {
//        sPlayer.removeKantai(fleet, i);
//    }
//    if (kantaiSize!=6) containers[kantaiSize]->setChangeButtonVisible(false);
//    
//    CallFunc* f1=CallFunc::create([=]()
//                                  {
//                                      for (int i=2; i<=kantaiSize; ++i)
//                                      {
//                                          containers[i-1]->changeContainer(fleet->getShip(i));
//                                      }
//                                  });
//    CallFunc* f2=CallFunc::create(CC_CALLBACK_0(KantaiListEntity::updateRows, listEntity));
//    CallFunc* f3=CallFunc::create([=]()
//                                  {
//                                      kantaiSize=1;
//                                      containers[kantaiSize-1+1]->setChangeButtonVisible(true);
//                                  });
//    
//    runAction(Sequence::create(f1,f2,DelayTime::create(0.7),f3, NULL));
//}
//
//
//
//void PortOrganizeLayer::changeContainer(Kantai* kantai)
//{
//    SND->playEffect("soundSE/changeShip.mp3");
//    
//    auto fleet=sPlayer.getFleetByFleetKey(fleetNumber);
//    if (fleet&&fleet->getShip(selectedShipIndex))
//    {
//        sPlayer.modifyKantaiPosition(fleet, selectedShipIndex, kantai);
//        CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganSelectEntity::moveOut,organSelectEntity));
//        CallFunc* f2=CallFunc::create(CC_CALLBACK_0(PortOrganizeLayer::hideList,this,this));
//        CallFunc* f3=CallFunc::create(CC_CALLBACK_0(OrganizeContainer::changeContainer, containers[selectedShipIndex-1],kantai));
//        CallFunc* f4=CallFunc::create(CC_CALLBACK_0(KantaiListEntity::updateRows, listEntity));
//        runAction(Sequence::create(f1,DelayTime::create(0.15),f2,DelayTime::create(0.1),f3,f4, NULL));
//    }
//    else
//    {
//        auto preFleet=dynamic_cast<Fleet*>(kantai->getFleet());
//        int prePosition=1;
//        if (preFleet)
//        {
//            for (; prePosition<=6; ++prePosition)
//            {
//                if (kantai==preFleet->getShip(prePosition)) {
//                    break;
//                }
//            }
//        }
//        sPlayer.modifyKantaiPosition(fleet, selectedShipIndex, kantai);
//        if (preFleet)
//        {
//            for (int i=prePosition+1; i<=6; ++i)
//            {
//                if (preFleet->getShip(i))
//                {
//                    sPlayer.modifyKantaiPosition(preFleet, i-1, preFleet->getShip(i));
//                }
//            }
//        }
//        
//        CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganSelectEntity::moveOut,organSelectEntity));
//        CallFunc* f2=CallFunc::create(CC_CALLBACK_0(PortOrganizeLayer::hideList,this,this));
//        CallFunc* f3=CallFunc::create(CC_CALLBACK_0(OrganizeContainer::openNewContainer, containers[selectedShipIndex-1],kantai));
//        CallFunc* f4=CallFunc::create(CC_CALLBACK_0(KantaiListEntity::updateRows, listEntity));
//        runAction(Sequence::create(f1,DelayTime::create(0.15),f2,DelayTime::create(0.1),f3,f4, NULL));
//        if (selectedShipIndex<6)
//        {
//            containers[selectedShipIndex]->setChangeButtonVisible(true);
//        }
//    }
//    
//    //containers[position-1]->changeContainer(kantai);
//}
//
//void PortOrganizeLayer::removeContainer()
//{
//    auto fleet=sPlayer.getFleetByFleetKey(fleetNumber);
//    if ((fleetNumber==1&&!fleet->getShip(2))||(!fleet->getShip(selectedShipIndex)))
//    {
//        return;
//    }
//    sPlayer.removeKantai(fleet, selectedShipIndex);
//    
//    for (int i=selectedShipIndex+1; i<=kantaiSize; ++i)
//    {
//        sPlayer.modifyKantaiPosition(fleet, i-1, fleet->getShip(i));
//    }
//    if (kantaiSize!=6)
//    {
//        containers[kantaiSize]->setChangeButtonVisible(false);
//    }
//    
//    CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganSelectEntity::moveOut, organSelectEntity));
//    CallFunc* f2=CallFunc::create(CC_CALLBACK_0(PortOrganizeLayer::hideList,this,this));
//    CallFunc* f3=CallFunc::create([=]()
//                                  {
//                                      for (int i=selectedShipIndex; i<=kantaiSize; ++i)
//                                      {
//                                          containers[i-1]->changeContainer(fleet->getShip(i));
//                                      }
//                                  });
//    CallFunc* f4=CallFunc::create(CC_CALLBACK_0(KantaiListEntity::updateRows, listEntity));
//    CallFunc* f5=CallFunc::create([=]()
//                                  {
//                                      kantaiSize=kantaiSize-1;
//                                      containers[kantaiSize]->setChangeButtonVisible(true);
//                                  });
//    runAction(Sequence::create(f1,DelayTime::create(0.15),f2,DelayTime::create(0.1),f3,f4,DelayTime::create(0.65),f5, NULL));
//    
//    //把maxIndex位置的changeButton设为Visible
//}


void PortOrganizeLayer::clearFleet(cocos2d::Ref *pSender)
{
    if (kantaiSize!=6) containers[kantaiSize]->setChangeButtonVisible(false);
    for (int i=2; i<=kantaiSize; ++i)
    {
        sPlayer.removeKantai(fleet, i);
    }
    kantaiSize=1;
}



void PortOrganizeLayer::changeContainer(Kantai* kantai)
{
    if (!kantai) CC_ASSERT("PortOrganizeLayer::changeContainer");
    
    SND->playEffect("soundSE/changeShip.mp3");
    auto fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    
    sPlayer.modifyKantaiPosition(fleet, selectedShipIndex, kantai);
    
    //移过来的kantai之前在fleet中,需要修改preFleet的container
    if (getContainer(selectedShipIndex)&&!getContainer(selectedShipIndex)->getKantai())
    {
        auto preFleet=dynamic_cast<Fleet*>(kantai->getFleet());
        int prePosition=1;
        if (preFleet)
        {
            for (; prePosition<=6; ++prePosition)
            {
                if (kantai==preFleet->getShip(prePosition)) {
                    break;
                }
            }
        }
        if (preFleet)
        {
            for (int i=prePosition+1; i<=6; ++i)
            {
                if (preFleet->getShip(i))
                {
                    sPlayer.modifyKantaiPosition(preFleet, i-1, preFleet->getShip(i));
                }
            }
        }
        ++kantaiSize;
    }
}

void PortOrganizeLayer::removeContainer()
{
    auto fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    if ((fleetNumber==1&&!fleet->getShip(2))||(!fleet->getShip(selectedShipIndex)))
    {
        return;
    }
    
    if (kantaiSize!=6) containers[kantaiSize]->setChangeButtonVisible(false);
    sPlayer.removeKantai(fleet, selectedShipIndex);
    
    for (int i=selectedShipIndex+1; i<=kantaiSize; ++i)
    {
            sPlayer.modifyKantaiPosition(fleet, i-1, fleet->getShip(i));
    }
    kantaiSize=kantaiSize-1;
}

void PortOrganizeLayer::modifyContainer(kantaiChangeType type,kancolle::Kantai *_kantai)
{
    controlGroup.clear();
    controlGroup.resize(6);
    
    for (int i=0; i<6; ++i)
    {
        if (getContainer(i+1))
            controlGroup[i]=getContainer(i+1)->getKantai();
        else
            controlGroup[i]=NULL;
    }
    
    switch (type)
    {
        case CHANGE_CONTAINER:
            changeContainer(_kantai);
            break;
        case REMOVE_CONTAINER:
            removeContainer();
            break;
        case CLEAR_FLEET:
            clearFleet(this);
            break;
        default:
            break;
    }
    
    containerActionStart(type);
}

#define HIDE_SELECT_TIME 0.15
#define HIDE_LIST_TIME   0.1
#define CONTAINER_ACTION_TIME 0.6

void PortOrganizeLayer::containerActionStart(kantaiChangeType type)
{
    EventPauseGuard::pause();
    
    FiniteTimeAction* _hideSelect;
    {
        CallFunc* p1=CallFunc::create(CC_CALLBACK_0(OrganSelectEntity::moveOut,organSelectEntity));
        _hideSelect=Sequence::create(p1,DelayTime::create(HIDE_SELECT_TIME), NULL);
    }
    
    
    FiniteTimeAction* _hideList;
    {
        CallFunc* p1=CallFunc::create(CC_CALLBACK_0(PortOrganizeLayer::hideList,this,this));
        _hideList=Sequence::create(p1,DelayTime::create(HIDE_LIST_TIME), NULL);
    }
    
    FiniteTimeAction* _changeContainer;
    {
        CallFunc* p1=CallFunc::create([=]()
        {
            for (int i=1; i<=6; ++i)
            {
                if(fleet->getShip(i)!=controlGroup[i-1])
                    getContainer(i)->changeContainer(controlGroup[i-1],fleet->getShip(i));
            }
        });
        _changeContainer=Sequence::create(p1,DelayTime::create(CHANGE_CONTAINER), NULL);
    }
    
    FiniteTimeAction* _updateRow;
    {
        CallFunc* p1=CallFunc::create(CC_CALLBACK_0(KantaiListEntity::updateRows, listEntity));
        _updateRow=Sequence::create(p1, NULL);
    }
    
    FiniteTimeAction* _setChangeButton;
    {
        CallFunc* p1=CallFunc::create(CC_CALLBACK_0(PortOrganizeLayer::setChangeButtonVisdible,this));
        _setChangeButton=Sequence::create(DelayTime::create(0.4),p1, NULL);
    }
    
    switch (type)
    {
        case CHANGE_CONTAINER:
            runAction(Sequence::create(_hideSelect,_hideList,_changeContainer,_updateRow,_setChangeButton, NULL));
            break;
        case REMOVE_CONTAINER:
            runAction(Sequence::create(_hideList,_changeContainer,_updateRow,_setChangeButton, NULL));
            break;
        case CLEAR_FLEET:
            runAction(Sequence::create(_changeContainer,_updateRow,_setChangeButton, NULL));
            break;
        default:
            break;
    }
    
    EventPauseGuard::resume();
}


void PortOrganizeLayer::setChangeButtonVisdible()
{
    if (kantaiSize==6)  return;
    
    getContainer(kantaiSize+1)->setChangeButtonVisible(true);
}

int PortOrganizeLayer::findFirstPosNoKantai()
{
    for (int i=1; i<=6; ++i)
    {
        if (!hasKantai(i))
        {
            return i;
        }
    }
    return -1;
}

bool PortOrganizeLayer::hasKantai(int position)
{
    if (position<=0&&position>6)
    {
        return false;
    }
    if (containers[position-1]->haveKantai())
    {
        return true;
    }
    return false;
}

NS_KCL_END