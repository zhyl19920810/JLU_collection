//
//  portOrganizeLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portOrganizeLayer.h"
#include "PortScene.h"




PortOrganizeLayer::PortOrganizeLayer()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CommonAssets/commonAssets.plist", "CommonAssets/commonAssets.pvr.ccz");
    
    
    fleetToggle.resize(4);
    fleetSprite.resize(4);
    containers.resize(6);
    lKantaiDoor.resize(6);
    rKantaiDoor.resize(6);
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
        if (!Layer::init()) {
            break;
        }
        
        //this->setZOrder(-1);
        initLayer();
        initFleetButton();
        initContainers();
        bRet=true;
    }while(0);
    
    
    return bRet;
}

void PortOrganizeLayer::setKantaiVisible(int position, bool bVisible)
{
    if (bVisible)
    {
        lKantaiDoor[position-1]->setVisible(false);
        rKantaiDoor[position-1]->setVisible(false);
        containers[position-1]->setVisible(true);
    }
    else
    {
        lKantaiDoor[position-1]->setVisible(true);
        rKantaiDoor[position-1]->setVisible(true);
        containers[position-1]->setVisible(false);
    }
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
    
    auto top_bar = Sprite::create("OrganizeMain/topBar.png");
    addChild(top_bar);
    top_bar->setPosition(bgimg->getPosition()+Vec2(0, 197));
    
    auto top_label = Sprite::create("OrganizeMain/topLabel.png");
    addChild(top_label);
    top_label->setPosition(top_bar->getPosition()+Vec2(-290, 4));
    
    auto clearFleetButton = MenuItemImage::create("OrganizeMain/closeFleet1.png", "OrganizeMain/closeFleet2.png", CC_CALLBACK_1(PortOrganizeLayer::clearFleet, this));
    clearFleetButton->setPosition(415, 365);
    menu->addChild(clearFleetButton);
    
    auto fleet_name_text_box = Sprite::create("OrganizeMain/inputFleetName.png");
    fleet_name_text_box->setPosition(clearFleetButton->getPosition()+Vec2(185, 5));
    addChild(fleet_name_text_box);
    
    auto editFleetNameButton = Sprite::create("OrganizeMain/editFleetNameButton.png");
    addChild(editFleetNameButton);
    editFleetNameButton->setAnchorPoint(Vec2(0, 0.5));
    editFleetNameButton->setPosition(fleet_name_text_box->getPosition()+Vec2(fleet_name_text_box->getContentSize().width/2, 0));
    

    auto closeItem = Sprite::create("CommonAssets/image 451.png");
    closeItem->setGlobalZOrder(10);
    closeItem->setOpacity(0);
    hideDetailItem = MenuItemSprite::create(closeItem, closeItem, CC_CALLBACK_1(PortOrganizeLayer::hideDetail, this));
    hideDetailItem->setPosition(visibleSize/2);
    hideDetailItem->setEnabled(false);
    menu->addChild(hideDetailItem);
    
    auto closeItem2 = Sprite::create("CommonAssets/image 451.png");
    closeItem2->setGlobalZOrder(10);
    closeItem2->setOpacity(0);
    hideListItem = MenuItemSprite::create(closeItem2, closeItem2, CC_CALLBACK_1(PortOrganizeLayer::hideList, this));
    hideListItem->setPosition(-42, 240);
    hideListItem->setEnabled(false);
    menu->addChild(hideListItem);
    addChild(menu);


    
    detailEntity=KantaiDetailEntity::create();
    addChild(detailEntity,2);
    detailEntity->setPosition(visibleSize.width,0);
    detailEntity->setKantai(fleet->getShip(1));
    
    listEntity=KantaiListEntity::create();
    addChild(listEntity,2);
    listEntity->setPosition(visibleSize.width,0);
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
    
    for (int i=0; i<6; ++i)
    {
        lKantaiDoor[i]=Sprite::create("OrganizeMain/lKantaiDoor.png");
        lKantaiDoor[i]->setPosition(containers[i]->getPosition());
        lKantaiDoor[i]->setAnchorPoint(Vec2(1.0,0.5));
        addChild(lKantaiDoor[i]);
        rKantaiDoor[i]=Sprite::create("OrganizeMain/rKantaiDoor.png");
        rKantaiDoor[i]->setPosition(containers[i]->getPosition());
        rKantaiDoor[i]->setAnchorPoint(Vec2(0, 0.5));
        addChild(rKantaiDoor[i]);
    }
    updateContainers();
}

void PortOrganizeLayer::hideList(Ref* pSender)
{
    listEntity->moveOut();
    hideListItem->setEnabled(false);
    setDetailButtonEnble(true);
}

void PortOrganizeLayer::showList(int index)
{
    if (listEntity->isHidden())
    {
        listEntity->moveIn();
    }
    hideListItem->setEnabled(true);
    setDetailButtonEnble(false);
    UserDefault::getInstance()->setIntegerForKey("fleetNumber", fleet->getFleetKey());
    UserDefault::getInstance()->setIntegerForKey("possiton", index);
}

void PortOrganizeLayer::updateContainers()
{
    for (int i = 0; i < 6; i++)
    {
        auto kantai=fleet->getShip(i+1);
        if (kantai)
        {
            containers[i]->updateCharacterInfo(kantai);
            setKantaiVisible(i+1, true);
        }
        else
        {
            setKantaiVisible(i+1, false);
        }
    }
    //parent->updateAssistantGirl();
}
void PortOrganizeLayer::showDetail(int index)
{
    if (detailEntity->isHidden())
    {
        detailEntity->moveIn();
    }
    detailEntity->setKantai(fleet->getShip(index));
    hideDetailItem->setEnabled(true);
    setChangeButtonEnble(false);
}
void PortOrganizeLayer::hideDetail(Ref* pSender)
{
    detailEntity->moveOut();
    hideDetailItem->setEnabled(false);
    setChangeButtonEnble(true);
}





void PortOrganizeLayer::setDetailButtonEnble(bool bEnble)
{
    for (int i=0;i<6; ++i)
    {
        containers[i]->setDetailButtonEnble(bEnble);
    }
}

void PortOrganizeLayer::setChangeButtonEnble(bool bEnble)
{
    for (int i=0; i<6; ++i)
    {
        containers[i]->setChangeButtonEnble(bEnble);
    }
}


void PortOrganizeLayer::selectFleet(Ref* pSender, int fleetIndex)
{
    //setCurrentFleet(fleetIndex);
}

void PortOrganizeLayer::clearFleet(Ref* pSender)
{
    
}





void PortOrganizeLayer::initFleetButton()
{
    fleetNumber=1;
    fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    fleetSprite[0]=Sprite::createWithSpriteFrameName("one1.png");
    bgimg->addChild(fleetSprite[0]);
    fleetSprite[0]->setPosition(Vec2(47, bgimg->getContentSize().height-27));
    
    fleetToggle[0]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortOrganizeLayer::fleetCallback, this,1), MenuItemSprite::create(Sprite::createWithSpriteFrameName("one2.png"), Sprite::createWithSpriteFrameName("one2.png")),
                                                      MenuItemSprite::create(Sprite::createWithSpriteFrameName("one3.png"), Sprite::createWithSpriteFrameName("one3.png")), NULL);
    fleetToggle[0]->setPosition(fleetSprite[0]->getPosition());
    
    
    fleetSprite[1]=Sprite::createWithSpriteFrameName("two1.png");
    bgimg->addChild(fleetSprite[1]);
    fleetSprite[1]->setPosition(fleetSprite[0]->getPosition()+Vec2(30, 0));
    
    fleetToggle[1]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortOrganizeLayer::fleetCallback, this,2), MenuItemSprite::create(Sprite::createWithSpriteFrameName("two2.png"), Sprite::createWithSpriteFrameName("two2.png")),
                                                      MenuItemSprite::create(Sprite::createWithSpriteFrameName("two3.png"), Sprite::createWithSpriteFrameName("two3.png")), NULL);
    fleetToggle[1]->setPosition(fleetSprite[1]->getPosition());
    
    
    
    fleetSprite[2]=Sprite::createWithSpriteFrameName("three1.png");
    bgimg->addChild(fleetSprite[2]);
    fleetSprite[2]->setPosition(fleetSprite[1]->getPosition()+Vec2(30, 0));
    
    fleetToggle[2]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortOrganizeLayer::fleetCallback, this,3), MenuItemSprite::create(Sprite::createWithSpriteFrameName("three2.png"), Sprite::createWithSpriteFrameName("three2.png")),
                                                      MenuItemSprite::create(Sprite::createWithSpriteFrameName("three3.png"), Sprite::createWithSpriteFrameName("three3.png")), NULL);
    fleetToggle[2]->setPosition(fleetSprite[2]->getPosition());
    
    
    
    fleetSprite[3]=Sprite::createWithSpriteFrameName("four1.png");
    bgimg->addChild(fleetSprite[3]);
    fleetSprite[3]->setPosition(fleetSprite[2]->getPosition()+Vec2(30, 0));
    
    fleetToggle[3]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortOrganizeLayer::fleetCallback, this,4), MenuItemSprite::create(Sprite::createWithSpriteFrameName("four2.png"), Sprite::createWithSpriteFrameName("four2.png")),
                                                      MenuItemSprite::create(Sprite::createWithSpriteFrameName("four3.png"), Sprite::createWithSpriteFrameName("four3.png")), NULL);
    fleetToggle[3]->setPosition(fleetSprite[3]->getPosition());
    
    auto mn=Menu::create(fleetToggle[0],fleetToggle[1],fleetToggle[2],fleetToggle[3], NULL);
    mn->setPosition(Vec2::ZERO);
    bgimg->addChild(mn);
    
    fleetToggle[0]->setSelectedIndex(1);
    for (int i=1; i<=4; ++i)
    {
        SetFleetButtonVisible(i, sPlayer.getFleetByFleetKey(i));
    }
}

void PortOrganizeLayer::fleetCallback(cocos2d::Ref *pSender, int layNumber)
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

void PortOrganizeLayer::changeFleet(int fleetNumber)
{
    this->fleetNumber=fleetNumber;
    fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    updateContainers();
}

void PortOrganizeLayer::SetFleetButtonVisible(int fleetNumber, bool bVisible)
{
    if (bVisible)
    {
        fleetToggle[fleetNumber-1]->setVisible(true);
        fleetSprite[fleetNumber-1]->setVisible(false);
    }
    else
    {
        fleetToggle[fleetNumber-1]->setVisible(false);
        fleetSprite[fleetNumber-1]->setVisible(true);
    }
}


bool PortOrganizeLayer::hasSameKantai(int kantaiNumber)
{
    
}
