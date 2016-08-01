//
//  OrganizeContainer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/27/16.
//
//

#include "OrganizeContainer.hpp"
#include "PortOrganizeLayer.h"

#define COVER_SHOW 100
#define COVER_NORMAL 0



NS_KCL_BEGIN

OrganizeContainer* OrganizeContainer::create(int position)
{
    OrganizeContainer *organizeContainer = new (std::nothrow) OrganizeContainer(position);
    if (organizeContainer && organizeContainer->init())
    {
        organizeContainer->autorelease();
        return organizeContainer;
    }
    CC_SAFE_DELETE(organizeContainer);
    return nullptr;
}

OrganizeContainer::OrganizeContainer(int position)
{
    this->position=position;
    CCASSERT(position<=6&&position>=1,"position is out of range in function \"OrganizeContainer\"");
}


void OrganizeContainer::setChangeButtonEnble(bool bEnble)
{
    changeButton->setEnabled(bEnble);
}

void OrganizeContainer::setChangeButtonVisible(bool bVisible)
{
    changeButton->setVisible(bVisible);
}

void OrganizeContainer::setDetailButtonEnble(bool bEnble)
{
    detailButton->setEnabled(bEnble);
}

void OrganizeContainer::setCoverVisble(bool bVisible,bool coverButton)
{
    templateNode->setVisible(bVisible);
    clippingNode->setVisible(bVisible);
    if (bVisible&&coverButton)
        clippingNode->setLocalZOrder(COVER_SHOW);
    else
        clippingNode->setLocalZOrder(COVER_NORMAL);
}




bool OrganizeContainer::init()
{
    bool bRet=false;
    
    do
    {
        CC_BREAK_IF(!Node::create());
        kantaiExist=false;
        kantai=NULL;
        
        initBg();
        initMainBody();
        initCover();
        
        bRet=true;
    }while(0);
    return bRet;
}

void OrganizeContainer::initBg()
{
    templateNode=Sprite::create("OrganizeMain/organKantaiBg.png");
    templateNode->setPosition(Vec2::ZERO);
    addChild(templateNode,-1);
    
    
    bg = Sprite::create("OrganizeMain/organKantaiBg.png");
    bg->setPosition(Vec2::ZERO);
    addChild(bg);
}

void OrganizeContainer::initMainBody()
{
    if (position == 1)
        indexIcon = Sprite::create("OrganizeMain/star1.png");
    else if (position ==2)
        indexIcon = Sprite::create("OrganizeMain/star2.png");
    else if (position == 3)
        indexIcon = Sprite::create("OrganizeMain/star3.png");
    else if (position == 4)
        indexIcon = Sprite::create("OrganizeMain/star4.png");
    else if (position == 5)
        indexIcon = Sprite::create("OrganizeMain/star5.png");
    else if (position == 6)
        indexIcon = Sprite::create("OrganizeMain/star6.png");
    addChild(indexIcon);
    indexIcon->setPosition(-160, 41);
    
    //exp
    expBar = Sprite::create("OrganizeMain/expBar.png");
    expBar->setPosition(78, -8);
    this->addChild(expBar);
    
    
    detailButton = MenuItemImage::create("OrganizeMain/detailButton1.png", "OrganizeMain/detailButton2.png", CC_CALLBACK_1(OrganizeContainer::detailCallback, this));
    detailButton->setPosition(35, -30);
    changeButton = MenuItemImage::create("OrganizeMain/changeButton1.png", "OrganizeMain/changeButton2.png", CC_CALLBACK_1(OrganizeContainer::changeCallback, this));
    changeButton->setPosition(118, -30);
    menu = Menu::create(detailButton,changeButton, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu,1);
    
    
    kantaiCard=KantaiCard::create();
    kantaiCard->setPosition(78, 20);
    addChild(kantaiCard);
    
    kantaiName = Label::create("", "fonts/DengXian.ttf", 25);
    kantaiName->setPosition(-120, 22);
    currLV = Label::create("", "fonts/DengXian.ttf", 18);
    currLV->setPosition(-23, 30);
    currHp = Label::create("", "fonts/DengXian.ttf", 10);
    currHp->setPosition(-25, 0);
    firePower = Label::create("", "fonts/DengXian.ttf", 15);
    firePower->setPosition(-95, -15);
    antiAir = Label::create("", "fonts/DengXian.ttf", 15);
    antiAir->setPosition(-20, -15);
    torpedo = Label::create("", "fonts/DengXian.ttf", 15);
    torpedo->setPosition(-95, -35);
    armour = Label::create("", "fonts/DengXian.ttf", 15);
    armour->setPosition(-20, -35);
    addChild(kantaiName);
    addChild(currLV);
    addChild(currHp);
    addChild(firePower);
    addChild(antiAir);
    addChild(torpedo);
    addChild(armour);
    
    lKantaiDoor=Sprite::create("OrganizeMain/lKantaiDoor.png");
    lKantaiDoor->setPosition(Vec2::ZERO);
    lKantaiDoor->setAnchorPoint(Vec2(1.0,0.5));
    rKantaiDoor=Sprite::create("OrganizeMain/rKantaiDoor.png");
    rKantaiDoor->setPosition(Vec2::ZERO);
    rKantaiDoor->setAnchorPoint(Vec2(0, 0.5));
    
    hpBar =HpBar::create();
    hpBar->setPosition(-45, 13);
    addChild(hpBar);
    stars = Stars::create();
    stars->setPosition(-145, 5);
    addChild(stars);
}



void OrganizeContainer::initCover()
{
    clippingNode = ClippingNode::create();
    clippingNode->setStencil(templateNode);
    clippingNode->setInverted(false);
    clippingNode->setAlphaThreshold(0);
    addChild(clippingNode);
    clippingNode->addChild(lKantaiDoor);
    clippingNode->addChild(rKantaiDoor);
}


void OrganizeContainer::setKantaiVisible(bool bVisible)
{
    if (bVisible)
    {
        lKantaiDoor->setPosition(-lKantaiDoor->getContentSize().width,0);
        rKantaiDoor->setPosition(rKantaiDoor->getContentSize().width, 0);
    }
    else
    {
        lKantaiDoor->setPosition(0,0);
        rKantaiDoor->setPosition(0, 0);
    }
    
    kantaiExist=bVisible;
    if (!kantaiExist) {
        kantai=NULL;
    }
    bg->setVisible(bVisible);
    indexIcon->setVisible(bVisible);
    kantaiCard->setVisible(bVisible);
    kantaiName->setVisible(bVisible);
    currLV->setVisible(bVisible);
    currHp->setVisible(bVisible);
    firePower->setVisible(bVisible);
    antiAir->setVisible(bVisible);
    torpedo->setVisible(bVisible);
    armour->setVisible(bVisible);
    hpBar->setVisible(bVisible);
    stars->setVisible(bVisible);
    expBar->setVisible(bVisible);
    detailButton->setVisible(bVisible);
    changeButton->setVisible(bVisible);
}



bool OrganizeContainer::haveKantai() const
{
    return kantaiExist;
}

int OrganizeContainer::getContainerKantaiNumber() const
{
    return kantai->getKantaiNumber();
}

void OrganizeContainer::updateCharacterInfo(Kantai* kantai)
{
    if (kantai)
    {
        setKantaiVisible(true);
        setCoverVisble(false);
        this->kantai=kantai;
        char name[30];
        bzero(name, sizeof(name));
        sprintf(name,"%d", kantai->getFirePower());
        firePower->setString(name);
        sprintf(name,"%d", kantai->getTorpedo());
        torpedo->setString(name);
        sprintf(name,"%d", kantai->getAntiAir());
        antiAir->setString(name);
        sprintf(name,"%d", kantai->getArmor());
        armour->setString(name);
        sprintf(name,"%d", kantai->getCurrLV());
        currLV->setString(name);
        sprintf(name,"%d/%d", kantai->getCurrHp(),kantai->getMaxHp());
        currHp->setString(name);
        kantaiName->setString(kantai->getKantaiName());
        if (kantaiName->getContentSize().width>80)
            kantaiName->setScaleX(0.8);
        else kantaiName->setScaleX(1);
        kantaiCard->updateCard(kantai);
        hpBar->setHp(kantai->getMaxHp(), kantai->getCurrHp());
        stars->setNumber(kantai->getStars());
    }
    else
    {
        setKantaiVisible(false);
        setCoverVisble(true);
    }
    
}


void OrganizeContainer::detailCallback(Ref* pSender)
{
    auto parent=dynamic_cast<PortOrganizeLayer*>(this->getParent());
    parent->setSelectedShipIndex(position);
    parent->showDetail(position);
}
void OrganizeContainer::changeCallback(Ref* pSender)
{
    auto parent=dynamic_cast<PortOrganizeLayer*>(this->getParent());
    parent->setSelectedShipIndex(position);
    parent->showList(position);
}



void OrganizeContainerAction::setPankOpen(OrganizeContainer* container)
{
    auto left=container->lKantaiDoor;
    auto right=container->rKantaiDoor;
    CallFunc* f1=CallFunc::create([=]()
                                  {
                                      container->setCoverVisble(true,true);
                                      left->setPosition(0,0);
                                      right->setPosition(0,0);
                                      left->runAction(MoveBy::create(0.3, Vec2(-left->getContentSize().width, 0)));
                                      right->runAction(MoveBy::create(0.3, Vec2(right->getContentSize().width, 0)));
                                  });
    CallFunc* f2=CallFunc::create([=]()
                                  {
                                      container->setCoverVisble(false);
                                  });
    left->runAction(Sequence::create(f1,DelayTime::create(0.35),f2, NULL));
}

void OrganizeContainerAction::setPankClose(OrganizeContainer* container)
{
    auto left=container->lKantaiDoor;
    auto right=container->rKantaiDoor;
    CallFunc* f1=CallFunc::create([=]()
                                  {
                                      container->setCoverVisble(true,true);
                                      left->setPosition(-left->getContentSize().width,0);
                                      right->setPosition(right->getContentSize().width, 0);
                                      left->runAction(MoveBy::create(0.3, Vec2(left->getContentSize().width, 0)));
                                      right->runAction(MoveBy::create(0.3, Vec2(-right->getContentSize().width, 0)));
                                  });
    CallFunc* f2=CallFunc::create([=]()
                                  {
                                      //container->setCoverVisble(false);
                                  });
    left->runAction(Sequence::create(f1,DelayTime::create(0.35),f2, NULL));
}




void OrganizeContainer::changeContainer(Kantai* preKantai,Kantai* kantai)
{
    if (!preKantai)
    {
        openNewContainer(kantai);
    }
    else if (kantai)
    {
        CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganizeContainerAction::setPankClose,this));
        CallFunc* f2=CallFunc::create(CC_CALLBACK_0(OrganizeContainer::updateCharacterInfo, this,kantai));
        CallFunc* f3=CallFunc::create(CC_CALLBACK_0(OrganizeContainerAction::setPankOpen,this));
        runAction(Sequence::create(f1,DelayTime::create(0.35),f2,f3,DelayTime::create(0.3), NULL));
    }
    else
    {
        CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganizeContainerAction::setPankClose,this));
        CallFunc* f2=CallFunc::create(CC_CALLBACK_0(OrganizeContainer::updateCharacterInfo, this,kantai));
        runAction(Sequence::create(f1,DelayTime::create(0.35),f2, NULL));
    }
}



void OrganizeContainer::openNewContainer(Kantai *kantai)
{
    CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganizeContainer::updateCharacterInfo, this,kantai));
    CallFunc* f2=CallFunc::create(CC_CALLBACK_0(OrganizeContainerAction::setPankOpen,this));
    runAction(Sequence::create(f1,f2,DelayTime::create(0.35), NULL));
}




NS_KCL_END


