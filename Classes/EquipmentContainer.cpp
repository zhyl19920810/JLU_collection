//
//  EquipmentContainer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#include "EquipmentContainer.hpp"
#include "SystemHeader.h"
#include "EquipPicMgr.hpp"

EquipContainer::EquipContainer()
{
    
}

bool EquipContainer::init()
{
    bool bRet=false;
    do
    {
        if (!Node::init()) {
            break;
        }
        initContainer();
        bRet=true;
    }while(0);
    return bRet;
}


//EquipmentContainer::EquipmentContainer(Equipment* equipment)
//{
//    initContainer();
//    updateEquipment(equipment);
//}
void EquipContainer::updateEquip(Equip* equip)
{
    if (equip == nullptr )
    {
        border->setVisible(true);
        label->setVisible(false);
        icon->setVisible(false);
    }
    else
    {
        border->setVisible(true);
        label->setVisible(true);
        icon->setVisible(true);
        
        label->setString(equip->getEquipName());
        auto tmp=sEquipPicMgr.getEquipPicMap(equip->getEquipNumber())->resource;
        char name[50];
        bzero(name, sizeof(name));
        sprintf(name, "icons/%s.png",tmp);
        icon->setTexture(name);
    }
}
void EquipContainer::initContainer()
{

    border = Sprite::create("CommonAssets/equipBg.png");
    this->addChild(border);
    label = Label::create("", "fonts/DengXian.ttf", 15);
    this->addChild(label);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label->setColor(Color3B(54, 36, 11));
    label->setPosition(-65, 0);
    icon = Sprite::create();
    icon->setPosition(-83, 0);
    this->addChild(icon);
    border->setVisible(false);
    label->setVisible(false);
    icon->setVisible(false);
}