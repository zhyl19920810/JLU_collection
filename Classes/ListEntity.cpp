//
//  ListEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/5/16.
//
//

#include "ListEntity.hpp"
#include "portOrganizeLayer.h"
#include "EventPauseGuard.hpp"
#include <algorithm>
#include "PageSwitch.hpp"




#define SHIPS_PER_PAGE 10



#define HIDE_POS (Vec2(bgimg->getContentSize().width,0))
#define SHOW_POS (Vec2(-bgimg->getContentSize().width,0))
#define MOVE_TIME 0.2


NS_KCL_BEGIN

ListEntity::ListEntity()
{
    rows.resize(10);
}

void ListEntity::moveOut()
{
    if (!hidden)
    {
        CallFunc* moveByBefore=CallFunc::create([=]()
                                                {
                                                    EventPauseGuard::pause();
                                                });
        auto move=MoveBy::create(MOVE_TIME, HIDE_POS);
        CallFunc* moveByFinish=CallFunc::create([=]()
                                                {
                                                    EventPauseGuard::resume();
                                                    layerCover->setCoverEnable(false);
                                                });
        entity->runAction(Sequence::create(moveByBefore,move,moveByFinish, NULL));
        hidden = true;
    }
    
}


void ListEntity::moveIn()
{
    if (hidden)
    {
        CallFunc* moveByBefore=CallFunc::create([=]()
                                                {
                                                    layerCover->setCoverEnable(true);
                                                    EventPauseGuard::pause();
                                                });
        auto move=MoveBy::create(MOVE_TIME, SHOW_POS);
        CallFunc* moveByFinish=CallFunc::create([=]()
                                                {
                                                    EventPauseGuard::resume();
                                                });
        entity->runAction(Sequence::create(moveByBefore,move,moveByFinish, NULL));
        hidden = false;
    }
}

void ListEntity::setHide(bool _hide)
{
    if (hidden!=_hide)
    {
        if (_hide)
        {
            entity->setPosition(HIDE_POS);
            hidden=true;
        }
        else
        {
            entity->setPosition(Vec2::ZERO);
            hidden=false;
        }
    }
}




void ListEntity::setRowVisble(int position, bool bVisible)
{
    CCASSERT(position>=1&&position<=10, "kantai row isn't exist");
    rows[position-1]->setVisible(bVisible);
    rows[position-1]->setVisible(bVisible);
}


void ListEntity::initBg(Vec2 vec)
{

    auto visbleSize=Director::getInstance()->getVisibleSize();
    
    entity=Node::create();
    entity->setPosition(Vec2::ZERO);
    addChild(entity);
    
    //bg
    bgimg = Sprite::create("OrganizeMain/kantaiListBg1.png");
    entity->addChild(bgimg);
    bgimg->setPosition(Vec2::ZERO);
    bgimg->setAnchorPoint(Vec2(0, 0));
    Node::setContentSize(bgimg->getContentSize());
    Vec2 tmp=bgimg->getContentSize();
    //bgimg->setPosition(654, 195);
    
    auto visible=Director::getInstance()->getVisibleSize();
    layerCover=LayerCover::create(CC_CALLBACK_0(ListEntity::moveOut, this));
    layerCover->setPosition(tmp.x-visible.width,0);
    addChild(layerCover,-1);
    
    
    auto titleBar = Sprite::create("OrganizeMain/kantaiListTitle.png");
    bgimg->addChild(titleBar);
    //titleBar->setPosition(753, 397);
    titleBar->setPosition(tmp/2+Vec2(179, 200));
    
    auto top_label = Sprite::create("OrganizeMain/kantaiListLabel.png");
    bgimg->addChild(top_label);
    top_label->setPosition(tmp/2+Vec2(-176, 201));
    //top_label->setPosition(398, 399);
    
    auto category = Sprite::create("OrganizeMain/kantaiListCate.png");
    bgimg->addChild(category);
    category->setPosition(tmp/2+Vec2(15, 175));
    //category->setPosition(595, 370);
    

    
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch *touch, Event *event)
    {
        auto target=static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 location=target->convertToNodeSpace(touch->getLocation());
        Size s=target->getContentSize();
        Rect rect=Rect(0,0,s.width,s.height);
        
        if (rect.containsPoint(location))
        {
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,bgimg);
 
}



void ListEntity::initSortButton()
{
    Vec2 tmp=bgimg->getContentSize()/2;
    MenuItemSprite* sortButtonUnitLV=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByLV.png"), Sprite::create("OrganizeMain/sortByLV.png"));
    MenuItemSprite* sortButtonUnitCate=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByCate.png"), Sprite::create("OrganizeMain/sortByCate.png"));
    MenuItemSprite* sortButtonUnitHP=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByHp.png"), Sprite::create("OrganizeMain/sortByHp.png"));
    MenuItemSprite* sortButtonUnitNew=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByNew.png"), Sprite::create("OrganizeMain/sortByNew.png"));
    
    sortButton=MenuItemToggle::createWithCallback(CC_CALLBACK_1(ListEntity::sortButtonCallback, this), sortButtonUnitLV,sortButtonUnitCate,sortButtonUnitHP,sortButtonUnitNew, NULL);
    sortButton->setPosition(tmp+Vec2(180, 150));
    //sortButton->setPosition(773, 370);
    
    menu = Menu::create(NULL);
    menu->setPosition(Vec2::ZERO);
    bgimg->addChild(menu,2);
    menu->addChild(sortButton);
    
    
    displayKantai=sPlayer.kantaiData;
    sort(displayKantai.begin(), displayKantai.end(), [](const Kantai* lhs,const Kantai* rhs)
         {
             return lhs->getCurrLV()>rhs->getCurrLV();
         });
}

void ListEntity::initRows()
{
    Vec2 tmp=bgimg->getContentSize()/2;
    
    for (int i=0; i<10; ++i)
    {
        rows[i]=ListRow::create(i+1);
        //rows[i]->setPosition(540, 345 - (i + 1) * 28);
        rows[i]->setPosition(tmp+Vec2(-40, 150 - (i + 1) * 28));
        entity->addChild(rows[i]);
    }
}




bool ListEntity::init(Vec2 vec)
{
    bool bRet=false;
    do
    {
        
        if (!Node::init())
        {
            break;
        }
        
        
        hidden=false;
        initBg(vec);
        initSortButton();
        initRows();
        setHide(true);
        initPageSwitch();
        updateRows();
        
        
        bRet=true;
    }while(0);
    return bRet;
}

void ListEntity::sortButtonCallback(cocos2d::Ref *pSender)
{
    int index=sortButton->getSelectedIndex();
    function<bool(const Kantai*,const Kantai*)> fun;
    switch (index)
    {
        case 1:
            fun=[](const Kantai* lhs,const Kantai* rhs){return lhs->getKantaiType()>rhs->getKantaiType();};
            break;
        case 2:
            fun=[](const Kantai* lhs,const Kantai* rhs){return lhs->getCurrHp()>rhs->getCurrHp();};
            break;
        case 3:
            fun=[](const Kantai* lhs,const Kantai* rhs){return lhs->getKantaiNumber()>rhs->getKantaiNumber();};
            break;
        case 0:
            fun=[](const Kantai* lhs,const Kantai* rhs){return lhs->getCurrLV()>rhs->getCurrLV();};
            break;
        default:
            break;
    }
    sort(displayKantai.begin(), displayKantai.end(), fun);
    updateRows();
}

void ListEntity::updateRow(int currPage)
{
    this->currPage=currPage;
    int i=currPage*10;
    int j=0;
    while (i<displayKantai.size()&&j<10)
    {
        rows[j]->update(displayKantai[i]);
        rows[j]->setVisible(true);
        ++j;
        ++i;
    }
    while (j<10)
    {
        rows[j]->setVisible(false);
        ++j;
    }
}

void ListEntity::updateRows()
{
    updateRow(currPage);
}

void ListEntity::addKantai(Kantai* kantai)
{
    displayKantai.push_back(kantai);
    sortButtonCallback(this);
    pageSwitch->addKantai();
    
}


void ListEntity::destoryKantai(Kantai *kantai)
{
    int p1=0,p2=0;
    while (p2<displayKantai.size())
    {
        if (displayKantai[p2]!=kantai)
        {
            displayKantai[p1++]=displayKantai[p2++];
        }else
        {
            ++p2;
        }
    }
    displayKantai.pop_back();
    pageSwitch->destroyKantai();
}

void ListEntity::initPageSwitch()
{
    currPage=0;
    Vec2 tmp=bgimg->getContentSize()/2;
    pageSwitch=PageSwitch::create(std::bind(&ListEntity::updateRow,this,std::placeholders::_1),static_cast<int>(displayKantai.size()));
    pageSwitch->setPosition(tmp);
    bgimg->addChild(pageSwitch);
    
}



NS_KCL_END







