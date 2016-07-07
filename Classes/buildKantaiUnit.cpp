//
//  buildKantaiUnit.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/3/16.
//
//

#include "buildKantaiUnit.hpp"


NS_KCL_BEGIN

bool BuildKantaiUnit::init(factoryBuildingMode mode)
{
    bool bRet=false;
    do
    {
        this->mode=mode;
        if (!Node::init()) {
            break;
        }
        initRes();
        initBg();
        initIcon();
        updateButtonAndLabel();
        bRet=true;
    }while(0);
    
    return bRet;
}

void BuildKantaiUnit::initRes()
{
    if (mode==factoryBuildingMode::kantaiBuilding) {
        minRes=currRes=30;
    }
    else
    {
        minRes=currRes=10;
    }
    if (getPlayerRes()<currRes) {
        canBuild=false;
    }
    else
        canBuild=true;
    maxRes=999;
}

void BuildKantaiUnit::arrowCallback(cocos2d::Ref *pSender, bool addDir)
{
    if (addDir)
    {
        int tmp1=maxRes-currRes;
        tmp1=(tmp1>10)?10:tmp1;
        int tmp2=getPlayerRes()-currRes;
        tmp2=(tmp2>10)?10:tmp2;
        int add=min(tmp1,tmp2);
        currRes+=add;
        updateButtonAndLabel();
    }
    else
    {
        currRes-=10;
        currRes=(currRes<minRes)?minRes:currRes;
        updateButtonAndLabel();
    }
}

void BuildKantaiUnit::resetCallback(cocos2d::Ref *pSender)
{
    currRes=minRes;
    updateButtonAndLabel();
}

void BuildKantaiUnit::maxCallback(cocos2d::Ref *pSender)
{
    int tmp=getPlayerRes();
    tmp=(tmp>maxRes)?maxRes:tmp;
    tmp=(tmp<minRes)?minRes:tmp;
    currRes=tmp;
    updateButtonAndLabel();
}

void BuildKantaiUnit::decadeCallback(cocos2d::Ref *pSender, bool addDir)
{
    if (addDir)
    {
        int tmp1=maxRes-currRes;
        tmp1=(tmp1>10)?10:tmp1;
        int tmp2=getPlayerRes()-currRes;
        tmp2=(tmp2>10)?10:tmp2;
        int add=min(tmp1,tmp2);
        currRes+=add;
        updateButtonAndLabel();
    }
    else
    {
        currRes-=10;
        currRes=(currRes<minRes)?minRes:currRes;
        updateButtonAndLabel();
    }
}


void BuildKantaiUnit::hundredCallback(cocos2d::Ref *pSender, bool addDir)
{
    if (addDir)
    {
        int tmp1=maxRes-currRes;
        tmp1=(tmp1>100)?100:tmp1;
        int tmp2=getPlayerRes()-currRes;
        tmp2=(tmp2>100)?100:tmp2;
        int add=min(tmp1,tmp2);
        currRes+=add;
        updateButtonAndLabel();
    }
    else
    {
        currRes-=100;
        currRes=(currRes<minRes)?minRes:currRes;
        updateButtonAndLabel();
    }
}




void BuildKantaiUnit::initBg()
{
    unitBg=Sprite::create("ArsenalMain/unitBg.png");
    unitBg->setPosition(Vec2::ZERO);
    addChild(unitBg);
    
    resLabel=Label::create("","fonts/DengXian.ttf",40);
    resLabel->setPosition(28,50);
    resLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    unitBg->addChild(resLabel);
    
    mn=Menu::create();
    mn->setPosition(Vec2::ZERO);
    unitBg->addChild(mn);
    
    addArrow=MenuItemSprite::create(Sprite::create("ArsenalMain/addArrow.png"), Sprite::create("ArsenalMain/addArrow.png"),CC_CALLBACK_1(BuildKantaiUnit::arrowCallback, this,true));
    addArrow->setPosition(56,85);
    mn->addChild(addArrow);
    
    minusArrow=MenuItemSprite::create(Sprite::create("ArsenalMain/minusArrow.png"), Sprite::create("ArsenalMain/minusArrow.png"),CC_CALLBACK_1(BuildKantaiUnit::arrowCallback, this,false));
    minusArrow->setPosition(56,17);
    mn->addChild(minusArrow);
    
    addDecade=MenuItemSprite::create(Sprite::create("ArsenalMain/addButton1.png"), Sprite::create("ArsenalMain/addButton1.png"),CC_CALLBACK_1(BuildKantaiUnit::decadeCallback, this,true));
    addDecade->setPosition(185,102);
    mn->addChild(addDecade);
    addDecadeUp=Sprite::create("ArsenalMain/addButton2.png");
    addDecadeUp->setPosition(addDecade->getPosition());
    unitBg->addChild(addDecadeUp);
    
    
    minusDecade=MenuItemSprite::create(Sprite::create("ArsenalMain/minusButton1.png"),Sprite::create("ArsenalMain/minusButton1.png"),CC_CALLBACK_1(BuildKantaiUnit::decadeCallback, this,false));
    minusDecade->setPosition(132,102);
    mn->addChild(minusDecade);
    minusDecadeUp=Sprite::create("ArsenalMain/minusButton2.png");
    minusDecadeUp->setPosition(minusDecade->getPosition());
    unitBg->addChild(minusDecadeUp);
    
    
    addHundred=MenuItemSprite::create(Sprite::create("ArsenalMain/addButton1.png"), Sprite::create("ArsenalMain/addButton1.png"),CC_CALLBACK_1(BuildKantaiUnit::hundredCallback, this,true));
    addHundred->setPosition(185,76);
    mn->addChild(addHundred);
    addHundredUp=Sprite::create("ArsenalMain/addButton2.png");
    addHundredUp->setPosition(addHundred->getPosition());
    unitBg->addChild(addHundredUp);
    
    
    minusHundred=MenuItemSprite::create(Sprite::create("ArsenalMain/minusButton1.png"), Sprite::create("ArsenalMain/minusButton1.png"),CC_CALLBACK_1(BuildKantaiUnit::hundredCallback, this,false));
    minusHundred->setPosition(132,76);
    mn->addChild(minusHundred);
    minusHundredUp=Sprite::create("ArsenalMain/minusButton2.png");
    minusHundredUp->setPosition(minusHundred->getPosition());
    unitBg->addChild(minusHundredUp);
    
    
    resetButton=MenuItemSprite::create(Sprite::create("ArsenalMain/resetButton.png"), Sprite::create("ArsenalMain/resetButton.png"),CC_CALLBACK_1(BuildKantaiUnit::resetCallback, this));
    resetButton->setPosition(160,46);
    mn->addChild(resetButton);
    
    maxButton=MenuItemSprite::create(Sprite::create("ArsenalMain/maxButton.png"), Sprite::create("ArsenalMain/maxButton.png"),CC_CALLBACK_1(BuildKantaiUnit::maxCallback, this));
    maxButton->setPosition(160,19);
    mn->addChild(maxButton);
}

int BuildKantaiUnit::getPlayerRes()
{
    return sPlayer.getFuel();
}




bool BuildKantaiUnit::canAddDecade()
{
    if ((getPlayerRes()>currRes)&&(currRes!=maxRes))
    {
        return true;
    }
    return false;
}

bool BuildKantaiUnit::canAddHundred()
{
    if ((getPlayerRes()>currRes)&&(currRes!=maxRes))
    {
        return true;
    }
    return false;
}

bool BuildKantaiUnit::canMinusDecade()
{
    if (currRes==30) {
        return false;
    }
    return true;
}

bool BuildKantaiUnit::canMinusHundred()
{
    if (currRes==30) {
        return false;
    }
    return true;
}

void BuildKantaiUnit::updateButtonAndLabel()
{
    resLabel->setString(to_string(currRes));
    if (canAddDecade()) {
        setAddDecadeVisible(true);
    }
    else
    {
        setAddDecadeVisible(false);
    }
    
    if (canMinusDecade())
    {
        setMinusDecadeVisible(true);
    }
    else
    {
        setMinusDecadeVisible(false);
    }
    
    if (canAddHundred())
    {
        setAddHundredVisible(true);
    }
    else
    {
        setAddHundredVisible(false);
    }
    
    if (canMinusHundred())
    {
        setMinusHundredVisible(true);
    }
    else
    {
        setMinusHundredVisible(false);
    }
    if (canAddDecade())
    {
        addArrow->setVisible(true);
        addArrow->setEnabled(true);
    }
    else
    {
        addArrow->setVisible(false);
        addArrow->setEnabled(false);
    }
    if (canMinusDecade())
    {
        minusArrow->setVisible(true);
        minusArrow->setEnabled(true);
    }
    else
    {
        minusArrow->setVisible(false);
        minusArrow->setEnabled(false);
    }
}

void BuildKantaiUnit::setAddDecadeVisible(bool bVisible)
{
    addDecade->setEnabled(bVisible);
    addDecade->setVisible(bVisible);
    addDecadeUp->setVisible(!bVisible);
}

void BuildKantaiUnit::setMinusDecadeVisible(bool bVisible)
{
    minusDecade->setEnabled(bVisible);
    minusDecade->setVisible(bVisible);
    minusDecadeUp->setVisible(!bVisible);
}

void BuildKantaiUnit::setAddHundredVisible(bool bVisible)
{
    addHundred->setEnabled(bVisible);
    addHundred->setVisible(bVisible);
    addHundredUp->setVisible(!bVisible);
}

void BuildKantaiUnit::setMinusHundredVisible(bool bVisible)
{
    minusHundred->setEnabled(bVisible);
    minusHundred->setVisible(bVisible);
    minusHundredUp->setVisible(!bVisible);
}


//fuel
FuelBuildUnit* FuelBuildUnit::create(factoryBuildingMode mode)
{
    FuelBuildUnit* pRet=new FuelBuildUnit;
    if (pRet&&pRet->init(mode))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}

int FuelBuildUnit::getPlayerRes()
{
    return sPlayer.getFuel();
}

void FuelBuildUnit::initIcon()
{
    auto fuelIcon=Sprite::create("ArsenalMain/fuelIcon.png");
    unitBg->addChild(fuelIcon);
    fuelIcon->setPosition(32,108);
}

void FuelBuildUnit::minusPlayerRes(int res)
{
    sPlayer.minusFuel(res);
    ////////////////////////////////
}


//ammo
AmmoBuildUnit* AmmoBuildUnit::create(factoryBuildingMode mode)
{
    AmmoBuildUnit* pRet=new AmmoBuildUnit;
    if (pRet&&pRet->init(mode))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}

int AmmoBuildUnit::getPlayerRes()
{
    return sPlayer.getAmmo();
}

void AmmoBuildUnit::initIcon()
{
    auto ammoIcon=Sprite::create("ArsenalMain/ammoIcon.png");
    unitBg->addChild(ammoIcon);
    ammoIcon->setPosition(32,108);
}

void AmmoBuildUnit::minusPlayerRes(int res)
{
    sPlayer.minusAmmo(res);
    ////////////////////////////////
}


//steel
SteelBuildUnit* SteelBuildUnit::create(factoryBuildingMode mode)
{
    SteelBuildUnit* pRet=new SteelBuildUnit;
    if (pRet&&pRet->init(mode))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}

int SteelBuildUnit::getPlayerRes()
{
    return sPlayer.getSteel();
}

void SteelBuildUnit::initIcon()
{
    auto steelIcon=Sprite::create("ArsenalMain/steelIcon.png");
    unitBg->addChild(steelIcon);
    steelIcon->setPosition(32,108);
}

void SteelBuildUnit::minusPlayerRes(int res)
{
    sPlayer.minusSteel(res);
    ////////////////////////////////
}

//Al
AlBuildUnit* AlBuildUnit::create(factoryBuildingMode mode)
{
    AlBuildUnit* pRet=new AlBuildUnit;
    if (pRet&&pRet->init(mode))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}

int AlBuildUnit::getPlayerRes()
{
    return sPlayer.getAluminium();
}

void AlBuildUnit::initIcon()
{
    auto AlIcon=Sprite::create("ArsenalMain/AlIcon.png");
    unitBg->addChild(AlIcon);
    AlIcon->setPosition(60,108);
}

void AlBuildUnit::minusPlayerRes(int res)
{
    sPlayer.minusAluminium(res);
    ////////////////////////////////
}

NS_KCL_END

