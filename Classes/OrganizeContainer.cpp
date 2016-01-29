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
        bg = Sprite::create("OrganizeMain/organKantaiBg.png");
        addChild(bg);
        //    parent->addChild(this);
        
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
        auto expBar = Sprite::create("OrganizeMain/expBar.png");
        expBar->setPosition(78, -8);
        this->addChild(expBar);
        
        
        detailButton = MenuItemImage::create("OrganizeMain/detailButton1.png", "OrganizeMain/detailButton2.png", CC_CALLBACK_1(OrganizeContainer::detailCallback, this));
        detailButton->setPosition(35, -30);
        changeButton = MenuItemImage::create("OrganizeMain/changeButton1.png", "OrganizeMain/changeButton2.png", CC_CALLBACK_1(OrganizeContainer::changeCallback, this));
        changeButton->setPosition(118, -30);
        auto menu = Menu::create(detailButton, changeButton, NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);
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
        
        
        hpBar = new HpBar(1, 1);
        hpBar->setPosition(-45, 13);
        addChild(hpBar);
        stars = new Stars();
        stars->setPosition(-145, 5);
        addChild(stars);
        
        bRet=true;
    }while(0);
    return bRet;
}


void OrganizeContainer::updateCharacterInfo(Kantai* kantai)
{

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
    stars->setNumber(3);//这里得改
    
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