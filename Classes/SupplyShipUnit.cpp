//
//  SupplyShipUnit.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/29/16.
//
//

#include "SupplyShipUnit.hpp"
#include "portSupplyLayer.h"

NS_KCL_BEGIN

ShipUnit::ShipUnit()
{

}


bool ShipUnit::init(int position)
{
    bool bRet=false;
    this->position=position;
    Color3B fcolor=Color3B::WHITE;
    
    do
    {
        if (!Node::init())
        {
            break;
        }
        condition=SupplyFree;
        kantaiBg=Sprite::create();
        kantaiBg->setPosition(Vec2::ZERO);
        kantaiBg->setSpriteFrame("supplyNoShip.png");
        addChild(kantaiBg);
        
        select=MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShipUnit::callback,this), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush1.png"), Sprite::create("SupplyMain/SupplyPush1.png")), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush2.png"), Sprite::create("SupplyMain/SupplyPush2.png")),
                                                  NULL);
        Vec2 selectPos=Vec2(kantaiBg->getContentSize().width/2-17,kantaiBg->getContentSize().height/2);
        select->setPosition(selectPos);
        Menu* mn=Menu::create();
        mn->addChild(select);
        mn->setPosition(Vec2::ZERO);
        kantaiBg->addChild(mn);
        
        Size size=kantaiBg->getContentSize();
        
        star=Sprite::create();
        star->setPosition(22,size.height/2-2);
        kantaiBg->addChild(star);
        
        kantaiName=Label::create();
        kantaiName->setPosition(200,size.height/2+5);
        kantaiName->setSystemFontSize(20);
        kantaiName->setColor(Color3B::WHITE);
        kantaiName->setAlignment(TextHAlignment::RIGHT);
        kantaiBg->addChild(kantaiName);
        
        kantaiLV = Label::create("", "fonts/DengXian.ttf", 13);
        kantaiLV->setPosition(290, size.height/2+5);
        kantaiLV->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        kantaiLV->setColor(Color3B::BLACK);
        kantaiBg->addChild(kantaiLV);
        
        kantaiState=Sprite::create();
        kantaiState->setPosition(88,size.height/2-3);
        kantaiBg->addChild(kantaiState);
        
        supplyBg1=Sprite::create();
        supplyBg1->setPosition(241,size.height/2);
        kantaiBg->addChild(supplyBg1);
        
        supplyBg2=Sprite::create();
        supplyBg2->setPosition(390,size.height/2);
        kantaiBg->addChild(supplyBg2);
        
        fuelBar=ValueBar::create();
        kantaiBg->addChild(fuelBar);
        fuelBar->setPosition(Vec2(356, size.height/2));
        
        ammoBar=ValueBar::create();
        kantaiBg->addChild(ammoBar);
        ammoBar->setPosition(Vec2(426,size.height/2));
        
        hpBar=HpBar::create();
        kantaiBg->addChild(hpBar);
        hpBar->setPosition(Vec2(208, size.height/2-13));
        
        stars=Stars::create();
        kantaiBg->addChild(stars);
        stars->setPosition(Vec2(250, size.height/2-10));
        
        haveAddFuel=false;
        haveAddAmmo=false;
        bRet=true;
        
    }while(0);
    return bRet;
}


void ShipUnit::update(Kantai *kantai)
{
    if (kantai)
        setKantai(kantai);
    else
        setNoKantai();
}

void ShipUnit::setKantai(Kantai* kantai)
{
    select->setEnabled(true);
    select->setVisible(true);
    star->setVisible(true);
    kantaiName->setVisible(true);
    kantaiState->setVisible(true);
    supplyBg1->setVisible(true);
    supplyBg2->setVisible(true);
    ammoBar->setVisible(true);
    fuelBar->setVisible(true);
    stars->setVisible(true);
    hpBar->setVisible(true);
    kantaiLV->setVisible(true);
    
    this->kantai=kantai;
    
    
    double percentage=0;
    int maxHp=kantai->getMaxHp();
    int currHp=kantai->getCurrHp();
    if (maxHp!=0)
    {
        percentage=(float)currHp/(float)maxHp;
    }else maxHp=1;
    
    char name[50];
    bzero(name, sizeof(name));
    if (percentage>0.5) {
        sprintf(name, "kantai/%d/image 27.png",kantai->getKantaiNumber());
    }else
    {
        sprintf(name, "kantai/%d/image 29.png",kantai->getKantaiNumber());
    }
    kantaiBg->setTexture(name);
    
    sprintf(name, "star%d.png",position);
    star->setSpriteFrame(name);
    kantaiName->setString(kantai->getKantaiName());
    
    
    sprintf(name, "%d",kantai->getCurrLV());
    kantaiLV->setString(name);
    
    if (percentage>0.75)
    {
        kantaiState->setVisible(false);
    }
    else if (percentage>0.5)
    {
        kantaiState->setSpriteFrame("xiaopoState.png");
    }
    else if (percentage>0.25)
    {
        kantaiState->setSpriteFrame("zhongpoState.png");
    }
    else if(percentage>0)
    {
        kantaiState->setSpriteFrame("dapoState.png");
    }
    else
    {
        kantaiState->setSpriteFrame("sunhuaiState.png");
    }
    
    if (kantai->getKantaiState()==KantaiState::Expedition)
    {
        kantaiState->setVisible(true);
        kantaiState->setSpriteFrame("yuanzhengState.png");
    }
    
    supplyBg1->setSpriteFrame("supplyShipBg1.png");
    supplyBg2->setSpriteFrame("supplyShipBg2.png");
    hpBar->setHp(kantai->getMaxHp(), kantai->getCurrHp());
    stars->setNumber(kantai->getStars());
    
    freshShipCondition();
    freshShipAttr();
}


void ShipUnit::setNoKantai()
{
    kantaiBg->setSpriteFrame("supplyNoShip.png");
    select->setEnabled(false);
    select->setVisible(false);
    star->setVisible(false);
    kantaiName->setVisible(false);
    kantaiState->setVisible(false);
    supplyBg1->setVisible(false);
    supplyBg2->setVisible(false);
    ammoBar->setVisible(false);
    fuelBar->setVisible(false);
    stars->setVisible(false);
    hpBar->setVisible(false);
    kantaiLV->setVisible(false);
}



void ShipUnit::freshShipCondition()
{
    auto layer=dynamic_cast<PortSupplyLayer*>(_parent);
    if (layer->canFillUpAmmo(position, kantai)||layer->canFillUpFuel(position, kantai))
    {
        condition=SupplyToggle;
    }
    else
    {
        condition=SupplySprite;
    }
}


void ShipUnit::freshShipAttr()
{
    double ammoNo=kantai->getCurrAmmo()*10/kantai->getMaxAmmo();
    double fuelNo=kantai->getCurrFuel()*10/kantai->getMaxFuel();
    if (ammoNo<0.0001&&ammoNo>-0.0001) {
        ammoNo=0;
    }
    if (fuelNo<0.0001&&fuelNo>-0.0001) {
        fuelNo=0;
    }
    ammoBar->update(ceil(ammoNo));
    fuelBar->update(ceil(fuelNo));
}



void ShipUnit::callback(cocos2d::Ref *pSender)
{
    MenuItemToggle* toggle=select;
    if (toggle->getSelectedIndex()&&(condition==SupplySprite))
    {
        toggle->setSelectedIndex(0);
        return;
    }
    auto layer=dynamic_cast<PortSupplyLayer*>(_parent);
    if (toggle->getSelectedIndex()) //由关到开
    {
        if (layer->canFillUpFuel(position,kantai))
        {
            int fuel=kantai->getMaxFuel()-kantai->getCurrFuel();
            layer->addConsumeFuel(position,fuel);
            haveAddFuel=true;
        }
        if (layer->canFillUpAmmo(position,kantai))
        {
            int ammo=kantai->getMaxAmmo()-kantai->getCurrAmmo();
            layer->addConsumeAmmo(position,ammo);
            haveAddAmmo=true;
        }
        layer->freshShipAllCondition();
        condition=SupplyToggle;
    }
    else//由开到关
    {
        if (haveAddFuel)
        {
            layer->minusConsumeFuel(position);
            haveAddFuel=false;
        }
        if (haveAddAmmo)
        {
            layer->minusConsumeAmmo(position);
            haveAddAmmo=false;
        }
        layer->freshShipAllCondition();
    }
}



NS_KCL_END


//bool ShipUnit::init(Kantai *kantai)
//{
//    condition=SupplyFree;
//    kantaiBg=Sprite::create();
//    kantaiBg->setPosition(371,366-52*position);
//    kantaiBg->setSpriteFrame("supplyNoShip.png");
//    parent->addChild(kantaiBg);
//
//    select=MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShipUnit::callback,this), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush1.png"), Sprite::create("SupplyMain/SupplyPush1.png")), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush2.png"), Sprite::create("SupplyMain/SupplyPush2.png")),
//                                              NULL);
//    select->setPosition(kantaiBg->getPosition()-Vec2(17, 0));
//    Menu* mn=Menu::create();
//    mn->addChild(select);
//    mn->setPosition(Vec2::ZERO);
//    parent->addChild(mn);
//
//    Size size=kantaiBg->getContentSize();
//
//    star=Sprite::create();
//    star->setPosition(22,size.height/2-2);
//    kantaiBg->addChild(star);
//
//    kantaiName=Label::create();
//    kantaiName->setPosition(200,size.height/2+5);
//    kantaiName->setSystemFontSize(20);
//    kantaiName->setColor(Color3B::WHITE);
//    kantaiName->setAlignment(TextHAlignment::RIGHT);
//    kantaiBg->addChild(kantaiName);
//
//    kantaiState=Sprite::create();
//    kantaiState->setPosition(88,size.height/2-3);
//    kantaiBg->addChild(kantaiState);
//
//    supplyBg1=Sprite::create();
//    supplyBg1->setPosition(241,size.height/2);
//    kantaiBg->addChild(supplyBg1);
//
//    supplyBg2=Sprite::create();
//    supplyBg2->setPosition(390,size.height/2);
//    kantaiBg->addChild(supplyBg2);
//
//    fuelBar=new ValueBar(Vec2(356, size.height/2), kantaiBg);
//    ammoBar=new ValueBar(Vec2(426,size.height/2), kantaiBg);
//    this->position=position;
//    this->parent=parent;
//    haveAddFuel=false;
//    haveAddAmmo=false;
//}



