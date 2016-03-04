//
//  OrganizeContainer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/27/16.
//
//

#include "OrganizeContainer.hpp"
#include "PortOrganizeLayer.h"


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

void OrganizeContainer::setDetailButtonEnble(bool bEnble)
{
    detailButton->setEnabled(bEnble);
}

bool OrganizeContainer::init()
{
    bool bRet=false;
    
    do
    {
        kantaiExist=false;
        kantai=NULL;
        bg = Sprite::create("OrganizeMain/organKantaiBg.png");
        addChild(bg);
        
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
        menu = Menu::create(detailButton, NULL);
        menu->setPosition(Vec2::ZERO);
        addChild(menu);
        
        changeMn=Menu::create(changeButton, NULL);
        changeMn->setPosition(Vec2::ZERO);
        addChild(changeMn,2);
        
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
        //addChild(lKantaiDoor);
        rKantaiDoor=Sprite::create("OrganizeMain/rKantaiDoor.png");
        rKantaiDoor->setPosition(Vec2::ZERO);
        rKantaiDoor->setAnchorPoint(Vec2(0, 0.5));
        //addChild(rKantaiDoor);
        
        hpBar =HpBar::create();
        hpBar->setPosition(-45, 13);
        addChild(hpBar);
        stars = Stars::create();
        stars->setPosition(-145, 5);
        addChild(stars);
        
        setClippingNode();
        
        bRet=true;
    }while(0);
    return bRet;
}

void OrganizeContainer::setClippingNode()
{
    clippingNode = ClippingNode::create();
    clippingNode->setStencil(bg);
    clippingNode->setInverted(false);
    clippingNode->setAlphaThreshold(0);
    addChild(clippingNode);
    clippingNode->addChild(lKantaiDoor);
    clippingNode->addChild(rKantaiDoor);
}



void OrganizeContainer::setKantaiVisible( bool bVisible)
{
    lKantaiDoor->setVisible(!bVisible);
    rKantaiDoor->setVisible(!bVisible);
    kantaiExist=bVisible;
    if (!kantaiExist) {
        kantai=NULL;
    }
    //bg->setVisible(bVisible);
    indexIcon->setVisible(bVisible);
    detailButton->setVisible(bVisible);
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
    menu->setVisible(bVisible);
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
        setKantaiVisible(false);
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

void OrganizeContainerAction::setPankOpen(cocos2d::Node *left, cocos2d::Node *right,Node* clippingNode)
{
    left->setPosition(0,0);
    right->setPosition(0,0);
    left->runAction(MoveBy::create(0.3, Vec2(-left->getContentSize().width, 0)));
    right->runAction(MoveBy::create(0.3, Vec2(right->getContentSize().width, 0)));
}

void OrganizeContainerAction::setPankClose(cocos2d::Node *left, cocos2d::Node *right,Node* clippingNode)
{
    left->setPosition(-left->getContentSize().width,0);
    right->setPosition(right->getContentSize().width, 0);
    left->runAction(MoveBy::create(0.3, Vec2(left->getContentSize().width, 0)));
    right->runAction(MoveBy::create(0.3, Vec2(-right->getContentSize().width, 0)));
}

void OrganizeContainerAction::setPankChange(cocos2d::Node *left, cocos2d::Node *right,Node* clippingNode)
{
    left->setVisible(true);
    right->setVisible(true);
    clippingNode->setLocalZOrder(100);
    CallFunc* f1=CallFunc::create(bind(OrganizeContainerAction::setPankClose,left, right,clippingNode));
    CallFunc* f2=CallFunc::create(bind(OrganizeContainerAction::setPankOpen, left,right,clippingNode));
    CallFunc* f3=CallFunc::create([=]()
                                  {
                                      left->setVisible(false);
                                      right->setVisible(false);
                                      clippingNode->setLocalZOrder(0);
                                  });
    left->runAction(Sequence::create(f1,DelayTime::create(0.35),f2,DelayTime::create(0.3),f3, NULL));
}

void OrganizeContainer::changeContainer(Kantai* kantai)
{
    if (kantai)
    {
        OrganizeContainerAction::setPankChange(lKantaiDoor, rKantaiDoor,clippingNode);
        CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganizeContainer::updateCharacterInfo, this,kantai));
        runAction(Sequence::create(DelayTime::create(0.35),f1,DelayTime::create(0.3), NULL));
    }
    else
    {
        OrganizeContainerAction::setPankClose(lKantaiDoor, rKantaiDoor,clippingNode);
        //这里进行判断，如果kantai为空的话，执行close,然后到时间0.35秒过后执行updateCharacterInfo刷新一下，把kantai关闭
    }
}


void OrganizeContainer::removeContainer()
{
    lKantaiDoor->setVisible(true);
    rKantaiDoor->setVisible(true);
    OrganizeContainerAction::setPankClose(lKantaiDoor, rKantaiDoor,clippingNode);
    CallFunc* f1=CallFunc::create(CC_CALLBACK_0(OrganizeContainer::updateCharacterInfo, this,kantai));
    CallFunc* f2=CallFunc::create([this](){setKantaiVisible(false);});
    runAction(Sequence::create(DelayTime::create(0.3),f1,DelayTime::create(0.3),f2, NULL));
    
}
