//
//  SupplyShipUnit.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/29/16.
//
//

#include "SupplyShipUnit.hpp"
#include "portSupplyLayer.h"
#include "ViewMgr.hpp"
#include "SupplyInfo.hpp"


NS_KCL_BEGIN

ShipUnit::ShipUnit()
{

}


bool ShipUnit::init(int position)
{
    bool bRet=false;
    this->position=position;
    do
    {
        CC_BREAK_IF(!Node::create());
        unitState=ShipUnitState::SupplyFree;
        
        initBg();
        initDisplayAttr();
        
        bRet=true;
        
    }while(0);
    return bRet;
}


void ShipUnit::initBg()
{
    kantaiBg=Sprite::create();
    kantaiBg->setPosition(Vec2::ZERO);
    kantaiBg->setSpriteFrame("supplyNoShip.png");
    addChild(kantaiBg);
    
    select=MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShipUnit::callback,this), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush1.png"), Sprite::create("SupplyMain/SupplyPush1.png"),Sprite::create("SupplyMain/SupplyPush3.png")), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush2.png"), Sprite::create("SupplyMain/SupplyPush2.png")),
                                              NULL);
    Vec2 selectPos=Vec2(kantaiBg->getContentSize().width/2-17,kantaiBg->getContentSize().height/2);
    select->setPosition(selectPos);
    
    Menu* mn=Menu::create();
    mn->addChild(select);
    mn->setPosition(Vec2::ZERO);
    kantaiBg->addChild(mn);
    
}

void ShipUnit::initDisplayAttr()
{
    Size size=kantaiBg->getContentSize();
    star=Sprite::create();
    star->setPosition(22,size.height/2-2);
    kantaiBg->addChild(star);
    
    supplyBg1=Sprite::create();
    supplyBg1->setPosition(241,size.height/2);
    kantaiBg->addChild(supplyBg1);
    
    supplyBg2=Sprite::create();
    supplyBg2->setPosition(390,size.height/2);
    kantaiBg->addChild(supplyBg2);
    
    
    kantaiName=Label::create("", "fonts/DengXian.ttf", 20);
    kantaiName->setPosition(200,size.height/2+5);
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
}



void ShipUnit::update(Kantai *kantai)
{
    if (kantai)
        updateKantai(kantai);
    else
        setNoKantai();
}

void ShipUnit::updateKantai(Kantai* kantai)
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
    
    updateShipState();
    updateBar();
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



void ShipUnit::updateShipState()
{
    auto panel=dynamic_cast<PortSupplyLayer*>(_parent);
    auto supplyImp=panel->supplyImp;
    
    if (supplyImp->canFillUpAmmo(kantai)||supplyImp->canFillUpFuel(kantai))
    {
        unitState=SupplyToggle;
        select->setEnabled(true);
    }
    else
    {
        unitState=SupplySprite;
        select->setEnabled(false);
    }
}


void ShipUnit::updateBar()
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
    auto panel=dynamic_cast<PortSupplyLayer*>(VIEW_MGR->getPanel(PanelType::PORT_SUPPLY));
    auto supplyImp=panel->supplyImp;
    
    MenuItemToggle* toggle=select;
    if (toggle->getSelectedIndex()&&(unitState==SupplySprite))
    {
        toggle->setSelectedIndex(0);
        return;
    }
    if (toggle->getSelectedIndex()) //由关到开
    {
        if (supplyImp->canFillUpFuel(kantai))
        {
            int fuel=kantai->getMaxFuel()-kantai->getCurrFuel();
            panel->addConsumeFuel(position,fuel);
            haveAddFuel=true;
        }
        if (supplyImp->canFillUpAmmo(kantai))
        {
            int ammo=kantai->getMaxAmmo()-kantai->getCurrAmmo();
            panel->addConsumeAmmo(position,ammo);
            haveAddAmmo=true;
        }
        panel->updatehipAllState();
        unitState=SupplyToggle;
    }
    else//由开到关
    {
        if (haveAddFuel)
        {
            panel->minusConsumeFuel(position);
            haveAddFuel=false;
        }
        if (haveAddAmmo)
        {
            panel->minusConsumeAmmo(position);
            haveAddAmmo=false;
        }
        panel->updatehipAllState();
    }
}






NS_KCL_END




