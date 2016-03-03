//
//  KantaiDetailEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#include "KantaiDetailEntity.hpp"
#include "PortRemodeLayer.h"




KantaiDetailEntity::KantaiDetailEntity()
{
    Hidden = true;
    equipContainer.resize(4);
    equipEmpty.resize(4);
}


bool KantaiDetailEntity::init()
{
    bool bRet=false;
    
    do
    {
        if (!Node::init()) {
            break;
        }
        initPage();
        bRet=true;
    }while(0);
    return bRet;
    
}

void KantaiDetailEntity::initPage()
{
    kantaiDetailBg = Sprite::create("CommonAssets/kantaiDetailBg.png");
    this->addChild(kantaiDetailBg);
    kantaiDetailBg->setOpacity(250);
    kantaiDetailBg->setPosition(620, 195);
    
    auto top_bar = Sprite::create("OrganizeMain/topBar.png");
    addChild(top_bar);
    top_bar->setPosition(753, 397);
    
    
    auto top_label = Sprite::create("CommonAssets/kantaiDetailLabel.png");
    this->addChild(top_label);
    top_label->setPosition(415, 399);
    
    
    auto paramBoard = Sprite::create("CommonAssets/paramBoard.png");
    this->addChild(paramBoard);
    paramBoard->setPosition(450, 90);
    
    kantaiImage = Sprite::create();
    this->addChild(kantaiImage);
    kantaiImage->setPosition(670, 230);
    
    auto LVIcon = Sprite::create("CommonAssets/LVIcon.png");
    this->addChild(LVIcon);
    LVIcon->setPosition(485, 370);
    

    for (int i=0; i<4; ++i)
    {
        equipEmpty[i]=Sprite::create("CommonAssets/noEquipBg.png");
        equipEmpty[i]->setPosition(450,310-i*35);
        addChild(equipEmpty[i]);
    }
    
    for (int i=0; i<4; ++i)
    {
        equipContainer[i]=EquipContainer::create();
        equipContainer[i]->setPosition(450,310-i*35);
        addChild(equipContainer[i]);
    }
    
    //ability
    Color3B fcolor = Color3B(54, 36, 11);
    kantaiName = Label::create("", "fonts/DengXian.ttf", 20);
    kantaiName->setColor(fcolor);
    kantaiName->setPosition(365, 370);
    kantaiLV = Label::create("", "fonts/DengXian.ttf", 18);
    kantaiLV->setColor(fcolor);
    kantaiLV->setPosition(520, 370);
    kantaiHp = Label::create("", "fonts/DengXian.ttf", 10);
    kantaiHp->setColor(fcolor);
    kantaiHp->setPosition(430, 340);
    maxHP = Label::create("", "fonts/DengXian.ttf", 15);
    maxHP->setColor(fcolor);
    maxHP->setPosition(432, 146);
    firePower = Label::create("", "fonts/DengXian.ttf", 15);
    firePower->setColor(fcolor);
    firePower->setPosition(528, 146);
    armour = Label::create("", "fonts/DengXian.ttf", 15);
    armour->setColor(fcolor);
    armour->setPosition(432, 123);
    torpedo = Label::create("", "fonts/DengXian.ttf", 15);
    torpedo->setColor(fcolor);
    torpedo->setPosition(528, 123);
    dodge = Label::create("", "fonts/DengXian.ttf", 15);
    dodge->setColor(fcolor);
    dodge->setPosition(432, 100);
    antiAircraft = Label::create("", "fonts/DengXian.ttf", 15);
    antiAircraft->setColor(fcolor);
    antiAircraft->setPosition(528, 100);
    capacity = Label::create("", "fonts/DengXian.ttf", 15);
    capacity->setColor(fcolor);
    capacity->setPosition(432, 77);
    antiSubmarine = Label::create("", "fonts/DengXian.ttf", 15);
    antiSubmarine->setColor(fcolor);
    antiSubmarine->setPosition(528, 77);
    searchEnemy = Label::create("", "fonts/DengXian.ttf", 15);
    searchEnemy->setColor(fcolor);
    searchEnemy->setPosition(528, 54);
    luck = Label::create("", "fonts/DengXian.ttf", 15);
    luck->setColor(fcolor);
    luck->setPosition(528, 31);
    
    speed = Sprite::create();
    speed->setPosition(430, 57);
    range = Sprite::create();
    range->setPosition(430, 33);
    
    addChild(kantaiName);
    addChild(kantaiLV);
    addChild(kantaiHp);
    addChild(maxHP);
    addChild(firePower);
    addChild(antiAircraft);
    addChild(torpedo);
    addChild(armour);
    addChild(dodge);
    addChild(capacity);
    addChild(antiSubmarine);
    addChild(searchEnemy);
    addChild(luck);
    addChild(speed);
    addChild(range);
    
    hpBar=HpBar::create();
    this->addChild(hpBar);
    hpBar->setPosition(370, 340);
    
    stars =Stars::create();
    stars->setPosition(470, 340);
    addChild(stars);
}

void KantaiDetailEntity::setEquipContainerVisible(int equipNumber, bool bVisible)
{
    CCASSERT(equipNumber>=1&&equipNumber<=4, "equipNumber is empty");
    if (bVisible)
    {
        equipContainer[equipNumber-1]->setVisible(true);
        equipEmpty[equipNumber-1]->setVisible(false);
    }
    else
    {
        equipContainer[equipNumber-1]->setVisible(false);
        equipEmpty[equipNumber-1]->setVisible(true);
    }
}


void KantaiDetailEntity::moveOut()
{
    auto size=Director::getInstance()->getVisibleSize();
    if (!Hidden)
    {
        this->runAction(MoveBy::create(0.2, ccp(size.width, 0)));
        Hidden = true;
    }
    
}
void KantaiDetailEntity::moveIn()
{
    auto size=Director::getInstance()->getVisibleSize();
    if (Hidden)
    {
        this->runAction(MoveBy::create(0.2, ccp(-size.width, 0)));
        Hidden = false;
    }
}

void KantaiDetailEntity::setKantai(Kantai *kantai)
{
    char name[30];
    bzero(name, sizeof(name));
    equipSize=kantai->getKantaiEquipSize();
    if (kantai->getBrokenType() == BrokenType::normal || kantai->getBrokenType() == BrokenType::tiny)
        sprintf(name, "kantai/%d/image 5.png",kantai->getKantaiNumber());
    else
        sprintf(name, "kantai/%d/image 7.png",kantai->getKantaiNumber());
    kantaiImage->setTexture(name);
    
    
    int i=0;
    for (; i<equipSize; ++i)
    {
        setEquipContainerVisible(i+1, true);
        equipContainer[i]->updateEquip(kantai->getEquip(i+1));
    }
    for (; i<4; ++i)
    {
        setEquipContainerVisible(i+1, false);
        equipContainer[i]->updateEquip(NULL);
    }
    
    
    
    
    sprintf(name, "%d",kantai->getFirePower());
    firePower->setString(name);
    sprintf(name, "%d",kantai->getTorpedo());
    torpedo->setString(name);
    sprintf(name, "%d",kantai->getAntiAir());
    antiAircraft->setString(name);
    sprintf(name, "%d",kantai->getArmor());
    armour->setString(name);
    kantaiName->setString(kantai->getKantaiName());
    sprintf(name, "%d",kantai->getCurrLV());
    kantaiLV->setString(name);
    sprintf(name, "%d/%d",kantai->getCurrHp(),kantai->getMaxHp());
    kantaiHp->setString(name);
    sprintf(name, "%d",kantai->getMaxHp());
    maxHP->setString(name);
    sprintf(name, "%d",kantai->getDodge());
    dodge->setString(name);
    sprintf(name, "%d",kantai->getAntiSubMarine());
    antiSubmarine->setString(name);
    sprintf(name, "%d",kantai->getSearchEnemy());
    searchEnemy->setString(name);
    sprintf(name, "%d",kantai->getLuck());
    luck->setString(name);
    
    int planeLoad=0;
    for (int i=0; i<equipSize; ++i)
    {
        planeLoad+=kantai->getInitPlaneLoad(i+1);
    }
    sprintf(name, "%d",planeLoad);
    capacity->setString(name);
    
    if (kantai->getSpeed() ==high_speed)
        speed->setTexture("CommonAssets/high_speed.png");
    else
        speed->setTexture("CommonAssets/low_speed.png");
    
    Shooting_Range kantaiRange=kantai->getRange();
    if (kantaiRange == Shooting_Range::range_exlong)
        range->setTexture("CommonAssets/range_exlong.png");
    else if (kantaiRange == Shooting_Range::range_long)
        range->setTexture("CommonAssets/range_long.png");
    else if (kantaiRange == Shooting_Range::range_mid)
        range->setTexture("CommonAssets/range_mid.png");
    else if (kantaiRange == Shooting_Range::range_short)
        range->setTexture("CommonAssets/range_short.png");
    else if (kantaiRange == Shooting_Range::range_non)
        range->setTexture("CommonAssets/range_non.png");
    
    
    if (kantaiName->getContentSize().width>80)
        kantaiName->setScaleX(0.8);
    else kantaiName->setScaleX(1);
    
    hpBar->setHp(kantai->getMaxHp(), kantai->getCurrHp());
    stars->setNumber(kantai->getStars());
}

