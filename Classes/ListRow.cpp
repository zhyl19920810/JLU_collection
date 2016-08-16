//
//  ListRow.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/5/16.
//
//


#include "ListRow.hpp"
#include "ListEntity.hpp"
#include "ViewMgr.hpp"

NS_KCL_BEGIN

bool ListRow::init(int position)
{
    bool bRet=false;
    this->position=position;
    Color3B fcolor = FONT_COLOR;
    
    do
    {
        if (!Node::init())
        {
            break;
        }
        line = Sprite::create("CommonAssets/Line.png");
        addChild(line);
        line->setPosition(35, -12);
        
        fleetIcon = Sprite::create();
        addChild(fleetIcon);
        fleetIcon->setPosition(-160,0);
        
        kantaiName = Label::create("", "fonts/DengXian.ttf", 13);
        kantaiName->setAlignment(TextHAlignment::LEFT);
        kantaiName->setPosition(-135, 0);
        kantaiName->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        kantaiName->setColor(fcolor);
        
        level = Label::create("", "fonts/DengXian.ttf", 13);
        level->setPosition(32, 0);
        level->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        level->setColor(fcolor);
        
        maxHP = Label::create("", "fonts/DengXian.ttf", 13);
        maxHP->setPosition(70, 0);
        maxHP->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        maxHP->setColor(fcolor);
        
        firePower = Label::create("", "fonts/DengXian.ttf", 13);
        firePower->setPosition(105, 0);
        firePower->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        firePower->setColor(fcolor);
        
        torpedo = Label::create("", "fonts/DengXian.ttf", 13);
        torpedo->setPosition(135, 0);
        torpedo->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        torpedo->setColor(fcolor);
        
        antiAir = Label::create("", "fonts/DengXian.ttf", 13);
        antiAir->setPosition(165, 0);
        antiAir->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        antiAir->setColor(fcolor);
        
        speed = Sprite::create();
        speed->setPosition(189, 2);
        
        auto item = Sprite::create("OrganizeMain/image 182.png");
        item->setOpacity(0);
        Sprite* lock1=Sprite::create("OrganizeMain/lock1.png");
        Sprite* lock2=Sprite::create("OrganizeMain/lock2.png");
        menuItem=MenuItemSprite::create(item, Sprite::create("OrganizeMain/image 182.png"),item,CC_CALLBACK_1(ListRow::exchangeCallback, this));
        menuItem->setPosition(Vec2(15, 2));
        menuItem->setScaleY(0.85);
        menuItem->setScaleX(0.95);
        lockIcon=MenuItemToggle::createWithCallback(CC_CALLBACK_1(ListRow::lockCallback, this), MenuItemSprite::create(lock1,lock1),MenuItemSprite::create(lock2,lock2), NULL);
        lockIcon->setPosition(speed->getPosition().x+speed->getContentSize().width+40, 0);
        
        auto mn=Menu::create(menuItem,lockIcon,NULL);
        mn->setPosition(Vec2::ZERO);
        addChild(mn);
        
        addChild(kantaiName);
        addChild(level);
        addChild(maxHP);
        addChild(firePower);
        addChild(torpedo);
        addChild(antiAir);
        addChild(speed);
        bRet=true;
    }while(0);
    
    return bRet;
}


void ListRow::update(Kantai* kantai)
{
    this->kantai=kantai;
    auto fleet=kantai->getFleet();
    if (fleet)
    {
        fleetIcon->setVisible(true);
        int fleetNumber=dynamic_cast<Fleet*>(fleet)->getFleetKey();
        switch (fleetNumber)
        {
            case 1:
                fleetIcon->setTexture("CommonAssets/one3.png");
                break;
            case 2:
                fleetIcon->setTexture("CommonAssets/two3.png");
                break;
            case 3:
                fleetIcon->setTexture("CommonAssets/three3.png");
                break;
            case 4:
                fleetIcon->setTexture("CommonAssets/four3.png");
                break;
            default:
                break;
        }
    }
    else
    {
        fleetIcon->setVisible(false);
    }
    lockIcon->setSelectedIndex(0);
    if (kantai->getKantaiLock()) {
        lockIcon->setSelectedIndex(1);
    }
    std::string type = Help::getKantaiType(kantai->getKantaiType());
    char name[50];
    bzero(name, sizeof(name));
    sprintf(name,"%s  %s",type.c_str(),kantai->getKantaiName());
    kantaiName->setString(name);
    sprintf(name, "%d",kantai->getCurrLV());
    level->setString(name);
    sprintf(name, "%d",kantai->getMaxHp());
    maxHP->setString(name);
    sprintf(name, "%d",kantai->getFirePower());
    firePower->setString(name);
    sprintf(name, "%d",kantai->getTorpedo());
    torpedo->setString(name);
    sprintf(name, "%d",kantai->getAntiAir());
    antiAir->setString(name);
    
    if (kantai->getSpeed() == high_speed)
        speed->setTexture("CommonAssets/highSpeed.png");
    else
        speed->setTexture("CommonAssets/lowSpeed.png");
}


ListRow::ListRow():kantai(NULL)
{
    
}

void ListRow::exchangeCallback(cocos2d::Ref *pSender)
{
    auto parentNode=static_cast<Node*>(this->getParent());
    auto parent=static_cast<ListEntity*>(parentNode->getParent());
    parent->showSelect(kantai);
}

void ListRow::setEnable(bool bVisible)
{
    menuItem->setEnabled(bVisible);
    lockIcon->setEnabled(bVisible);
}

void ListRow::lockCallback(cocos2d::Ref *pSender)
{
    bool lock=kantai->getKantaiLock();
    kantai->setKantaiLock(!lock);
}

NS_KCL_END
