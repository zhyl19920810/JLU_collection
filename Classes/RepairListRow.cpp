//
//  RepairListRow.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#include "RepairListRow.hpp"
#include "RepairListEntity.hpp"
#include "ViewMgr.hpp"
#include "portRepairLayer.h"


NS_KCL_BEGIN

bool RepairListRow::init(int position)
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
        addChild(kantaiName);
        
        level = Label::create("", "fonts/DengXian.ttf", 13);
        level->setPosition(32, 0);
        level->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        level->setColor(fcolor);
        addChild(level);
        
        hpBar=new RepairHpBar(1,1);
        hpBar->setPosition(120,0);
        addChild(hpBar);
        hpBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        
        HP=Label::create("", "fonts/DengXian.ttf", 10);
        HP->setPosition(200,0);
        HP->setColor(fcolor);
        HP->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(HP);
        
        broke=Sprite::create();
        broke->setPosition(180,0);
        addChild(broke);
        

        auto item = Sprite::create("OrganizeMain/image 182.png");
        item->setOpacity(0);

        menuItem=MenuItemSprite::create(item, Sprite::create("RepairMain/image 56.png"),item,CC_CALLBACK_1(RepairListRow::exchangeCallback, this));
        menuItem->setPosition(Vec2(50, 2));
        menuItem->setScaleY(0.85);
        menuItem->setScaleX(1.2);

        auto mn=Menu::create(menuItem,NULL);
        mn->setPosition(Vec2::ZERO);
        addChild(mn);
        
        bRet=true;
    }while(0);
    
    return bRet;
}


void RepairListRow::update(Kantai* kantai)
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
        if (sPlayer.getFlagShip()==kantai) {
            fleetIcon->setTexture("RepairMain/flagIcon.png");
        }
    }
    else
    {
        fleetIcon->setVisible(false);
    }

    std::string type = Help::getKantaiType(kantai->getKantaiType());
    char name[50];
    bzero(name, sizeof(name));
    sprintf(name,"%s  %s",type.c_str(),kantai->getKantaiName());
    kantaiName->setString(name);
    sprintf(name, "%d",kantai->getCurrLV());
    level->setString(name);
    sprintf(name, "%d//%d",kantai->getCurrHp(),kantai->getMaxHp());
    HP->setString(name);
    hpBar->setHp(kantai->getMaxHp(), kantai->getCurrHp());
    
    auto brokeType=kantai->getBrokenType();
    switch (brokeType) {
        case normal:
            broke->setTexture("");
            break;
        case tiny:
            broke->setTexture("RepairMain/xiaopo.png");
            break;
        case mid:
            broke->setTexture("RepairMain/zhongpo.png");
            break;
        case large:
            broke->setTexture("RepairMain/dapo.png");
            break;
        default:
            break;
    }
    auto kantaiState=kantai->getKantaiState();
    if (kantaiState==KantaiState::Repairing) {
        broke->setTexture("RepairMain/xiufu.png");
    }
    else if(kantaiState==KantaiState::Expedition)
    {
        broke->setTexture("RepairMain/yuanzheng.png");
    }

}


RepairListRow::RepairListRow():kantai(NULL)
{
    
}

void RepairListRow::exchangeCallback(cocos2d::Ref *pSender)
{
    auto panel=dynamic_cast<PortRepairLayer*>(VIEW_MGR->getPanel(PanelType::PORT_REPAIR));
    panel->showSelect(kantai);
}

void RepairListRow::setEnable(bool bVisible)
{
    menuItem->setEnabled(bVisible);
}

NS_KCL_END

