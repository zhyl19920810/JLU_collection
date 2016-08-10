//
//  buildKantaiUnit.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/3/16.
//
//

#include "buildKantaiUnit.hpp"


NS_KCL_BEGIN

bool BuildKantaiUnit::init(factoryBM mode)
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
        schedule(CC_CALLBACK_1(BuildKantaiUnit::updateButtonAndLabel, this), "BuildUnitUpdate");
        updateButtonAndLabel(0.0);
        bRet=true;
    }while(0);
    
    return bRet;
}

void BuildKantaiUnit::initRes()
{
    switch (mode)
    {
        case factoryBM::kantaiBuilding:
            minRes=30;
            currRes=min(getPlayerRes(), minRes);
            break;
        case factoryBM::equipBuilding:
            minRes=10;
            currRes=min(getPlayerRes(), minRes);
            break;
        default:
            break;
    }
    if (getPlayerRes()<currRes)   canBuild=false;
    else                          canBuild=true;
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
    }
    else
    {
        if (currRes>minRes)
        {
            currRes-=10;
            currRes=(currRes<minRes)?minRes:currRes;
        }
    }
}

void BuildKantaiUnit::resetCallback(cocos2d::Ref *pSender)
{
    if (getPlayerRes()>=minRes)
    {
        currRes=minRes;
    }
    else
    {
        currRes=getPlayerRes();
    }
}

void BuildKantaiUnit::maxCallback(cocos2d::Ref *pSender)
{
    int tmp=getPlayerRes();
    tmp=(tmp>maxRes)?maxRes:tmp;
    currRes=tmp;
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
    }
    else
    {
        if (currRes>minRes)
        {
            currRes-=10;
            currRes=(currRes<minRes)?minRes:currRes;
        }
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
    }
    else
    {
        if (currRes>minRes)
        {
            currRes-=100;
            currRes=(currRes<minRes)?minRes:currRes;
        }
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
    
    addDecade=MenuItemSprite::create(Sprite::create("ArsenalMain/addButton1.png"), Sprite::create("ArsenalMain/addButton1.png"),Sprite::create("ArsenalMain/addButton2.png"),CC_CALLBACK_1(BuildKantaiUnit::decadeCallback, this,true));
    addDecade->setPosition(185,102);
    mn->addChild(addDecade);
    
    minusDecade=MenuItemSprite::create(Sprite::create("ArsenalMain/minusButton1.png"),Sprite::create("ArsenalMain/minusButton1.png"),Sprite::create("ArsenalMain/minusButton2.png"),CC_CALLBACK_1(BuildKantaiUnit::decadeCallback, this,false));
    minusDecade->setPosition(132,102);
    mn->addChild(minusDecade);
    
    addHundred=MenuItemSprite::create(Sprite::create("ArsenalMain/addButton1.png"), Sprite::create("ArsenalMain/addButton1.png"),Sprite::create("ArsenalMain/addButton2.png"),CC_CALLBACK_1(BuildKantaiUnit::hundredCallback, this,true));
    addHundred->setPosition(185,76);
    mn->addChild(addHundred);
    
    minusHundred=MenuItemSprite::create(Sprite::create("ArsenalMain/minusButton1.png"), Sprite::create("ArsenalMain/minusButton1.png"),Sprite::create("ArsenalMain/minusButton2.png"),CC_CALLBACK_1(BuildKantaiUnit::hundredCallback, this,false));
    minusHundred->setPosition(132,76);
    mn->addChild(minusHundred);

    
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
    if ((getPlayerRes()>currRes)&&(currRes!=maxRes)) return true;
    return false;
}

bool BuildKantaiUnit::canAddHundred()
{
    if ((getPlayerRes()>currRes)&&(currRes!=maxRes)) return true;
    return false;
}

bool BuildKantaiUnit::canMinusDecade()
{
    if (currRes>minRes) return true;
    return false;
}

bool BuildKantaiUnit::canMinusHundred()
{
    if (currRes>minRes) return true;
    return false;
}

void BuildKantaiUnit::updateButtonAndLabel(float dt)
{
    resLabel->setString(to_string(currRes));
    
    if (canAddDecade())    { addDecade->setEnabled(true);    addArrow->setVisible(true);}
    else                   { addDecade->setEnabled(false);   addArrow->setVisible(false);}
    
    if (canMinusDecade())  {minusDecade->setEnabled(true);   minusArrow->setVisible(true);}
    else                   {minusDecade->setEnabled(false);  minusArrow->setVisible(false);}
    
    if (canAddHundred())   addHundred->setEnabled(true);
    else                   addHundred->setEnabled(false);
    
    if (canMinusHundred()) minusHundred->setEnabled(true);
    else                   minusHundred->setEnabled(false);
}

void BuildKantaiUnit::updateRes()
{
    if (currRes>getPlayerRes())
        currRes=getPlayerRes();
    if (currRes<minRes) canBuild=false;
}


//fuel
FuelBuildUnit* FuelBuildUnit::create(factoryBM mode)
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
AmmoBuildUnit* AmmoBuildUnit::create(factoryBM mode)
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
SteelBuildUnit* SteelBuildUnit::create(factoryBM mode)
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
AlBuildUnit* AlBuildUnit::create(factoryBM mode)
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
}

NS_KCL_END

