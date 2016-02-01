//
//  RepairHpBar.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#include "RepairHpBar.hpp"

RepairHpBar::RepairHpBar(int maxHp,int currentHp)
{
    if (maxHp<=0)
    {
        log("maxHp is below zero");
        maxHp=1;
    }
    this->maxHp=maxHp;
    this->currentHp=currentHp;
    barBg=Sprite::create("RepairMain/repairHpBar.png");
    barBg->setPosition(Vec2::ZERO);
    //barBg->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(barBg);
    bg=Sprite::create("RepairMain/repairHpBg.png");
    bar=Sprite::create("RepairMain/repairHpBar.png");
    bg->setPosition(Vec2::ZERO);
    //bg->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bar->setPosition(barBg->getPosition().x-barBg->getContentSize().width/2,barBg->getPosition().y);
    bar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(bg);
    addChild(bar);
    float percentage=currentHp/maxHp;
    bar->setScaleX(percentage);
}

void RepairHpBar::setCurrHp(int currentHp)
{
    this->currentHp=currentHp;
    float percentage=currentHp/maxHp;
    bar->setScaleX(percentage);
    if (percentage>0.75)
        bar->setColor(Color3B::GREEN);
    else if (percentage >0.5)
        bar->setColor(Color3B::ORANGE);
    else if (percentage >0.25)
        bar->setColor(Color3B::YELLOW);
    else
        bar->setColor(Color3B::RED);
}

void RepairHpBar::setHp(int maxHp, int currentHp)
{
    if (maxHp<=0)
    {
        log("maxHp is below zero");
        maxHp=1;
    }
    this->maxHp=maxHp;
    setCurrHp(currentHp);
}
