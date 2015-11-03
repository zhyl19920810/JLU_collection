//
//  BattleBar.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#include "BattleBar.h"


BattleBar::BattleBar(Node* parent)
{
    this->parent=parent;
    init();
}


void BattleBar::init()
{
    centerGreenBar = Sprite::create("interface/BattleMain/BattleMain_550.png");
    centerGreenBar->setZOrder(1);
    centerGreenBar->setPosition(400, 240);
    centerGreenBar->setOpacity(0);
    parent->addChild(centerGreenBar);
    
    topGreenBar = Sprite::create("interface/BattleMain/BattleMain_550.png");
    topGreenBar->setZOrder(1);
    topGreenBar->setPosition(400, 400);
    topGreenBar->setOpacity(0);
    parent->addChild(topGreenBar);
    
    bottomGreenBar = Sprite::create("interface/BattleMain/BattleMain_550.png");
    bottomGreenBar->setZOrder(1);
    bottomGreenBar->setPosition(400, 100);
    bottomGreenBar->setOpacity(0);
    parent->addChild(bottomGreenBar);
    
}


void BattleBar::openAndCloseAnimation(GreenBarPosition position, cocos2d::Sprite *label, float delay)
{
    bool labelPositionSet=true;
    Point p=label->getPosition();
    if (p.x==0&&p.y==0)
    {
        labelPositionSet=false;
    }
    switch (position)
    {
        case topleft:
        {
            if (!labelPositionSet)
            {
                label->setPosition(220,400);
            }
            parent->addChild(label);
            label->setZOrder(1);
            openAndCloseAnimation(topGreenBar, label, delay);
            break;
        }
        case center:
        {
            if (!labelPositionSet)
            {
                label->setPosition(400,240);
            }
            parent->addChild(label);
            label->setZOrder(1);
            openAndCloseAnimation(centerGreenBar, label, delay);
            break;
        }
        case bottom:
        {
            if (!labelPositionSet)
            {
                label->setPosition(400,100);
            }
            parent->addChild(label);
            label->setZOrder(1);
            openAndCloseAnimation(bottomGreenBar, label, delay);
            break;
        }
        default:
            break;
    }
}


void BattleBar::openAndCloseAnimation(GreenBarPosition position, GreenBarLableType type, float delay)
{
    Sprite* label=nullptr;
    switch (type)
    {
        case scout_start:
        {
            label=Sprite::create("interface/BattleMain/BattleMain_555.png");
            break;
        }
        case scouter_doesnt_back:
        {
            label=Sprite::create("interface/BattleMain/BattleMain_555.png");
            break;
        }
        case enemy_scouted:
            label = Sprite::create("interface/BattleMain/BattleMain_558.png");
            break;
        case enemy_scouted_scouter_doesnt_back:
            label = Sprite::create("interface/BattleMain/BattleMain_556.png");
            break;
        case enemy_not_scouted:
            label = Sprite::create("interface/BattleMain/BattleMain_557.png");
            break;
        case enemy_seen:
            label = Sprite::create("interface/BattleMain/BattleMain_559.png");
            break;
        default:
            break;
    }
    this->openAndCloseAnimation(position, label,delay);

}

void BattleBar::openAndCloseAnimation(GreenBarPosition position, GreenBarLableType type)
{
    openAndCloseAnimation(position, type, 0);
}




void BattleBar::openAndCloseAnimation(cocos2d::Sprite *border, cocos2d::Sprite *label, float delay)
{
    border->setScaleY(0.2);
    FiniteTimeAction* fadeIn=FadeIn::create(0.01);
    FiniteTimeAction* scaleUp=ScaleBy::create(0.3, 1, 5, 0);
    FiniteTimeAction* scaleDown=ScaleBy::create(0.3, 1, 0.2, 0);
    FiniteTimeAction* fadeOut=FadeOut::create(0.2);
    auto action=Sequence::create(DelayTime::create(delay),fadeIn,scaleUp,DelayTime::create(0.7),scaleDown,fadeOut, NULL);
    border->runAction(action);
    
    
    Point labelPostion=label->getPosition();
    FiniteTimeAction* fadeIn2=FadeIn::create(0.01);
    FiniteTimeAction* moveLeft=MoveTo::create(0.6, Point(labelPostion.x-30,labelPostion.y));
    FiniteTimeAction* fadeOut2=FadeOut::create(0.2);
    auto action2=Sequence::create(DelayTime::create(delay),fadeIn2,moveLeft,DelayTime::create(0.5),fadeOut2, NULL);
    label->runAction(action2);
}




void BattleBar::openAndCloseAnimation(GreenBarPosition position, cocos2d::Sprite *label)
{
    openAndCloseAnimation(position, label, 0);
}





void BattleBar::runAction(cocos2d::Action *action, GreenBarPosition position)
{
    switch (position)
    {
        case top:
        {
            topGreenBar->runAction(action);
            break;
        }
        case topleft:
        {
            break;
        }
        case center:
        {
            centerGreenBar->runAction(action);
            break;
        }
        case bottom:
        {
            bottomGreenBar->runAction(action);
            break;
        }

        default:
            break;
    }
}

