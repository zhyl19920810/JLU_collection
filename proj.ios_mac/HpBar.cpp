//
//  HpBar.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#include "HpBar.hpp"


HpBar::HpBar(int maxHp, int currentHp)
{

    bar = Sprite::create("CommonAssets/hpBar.png");
    bar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(bar);
    auto bgBar = Sprite::create("CommonAssets/HpBarBg.png");
    this->addChild(bgBar);
    bgBar->setPosition(0,0);
    bar->setPosition(-30, 0);
    setHp(maxHp, currentHp);
    
}

void HpBar::setCurrentHp(int currentHp)
{
    this->currentHp = currentHp;
    float persentage = (float)currentHp / (float)maxHp;
    bar->setScaleX(persentage);
    if (persentage > 0.75)
        bar->setColor(Color3B::GREEN);
    else if (persentage >0.5)
        bar->setColor(Color3B::ORANGE);
    else if (persentage >0.25)
        bar->setColor(Color3B::YELLOW);
    else
        bar->setColor(Color3B::RED);
    
}
void HpBar::setHp(int maxHp, int currentHp)
{
    this->maxHp = maxHp;
    setCurrentHp(currentHp);
}