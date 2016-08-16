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




#define SHIPS_PER_PAGE 10
#define FONT_COLOR Color3B::BLACK


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
    
    
    menu = Menu::create(NULL);
    menu->setPosition(Vec2::ZERO);
    bgimg->addChild(menu,2);
    
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



void ListEntity::initPageSwitch()
{
    Vec2 tmp=bgimg->getContentSize()/2;
    currentPage=0;
    maxPage=(displayKantai.size()-1)/10;
    midPage=2;
    if (maxPage<5)
    {
        isMove=false;
    }else
    {
        isMove=true;
    }
    
    firstPage = MenuItemImage::create("CommonAssets/firstPage.png", "CommonAssets/firstPage.png",CC_CALLBACK_1(ListEntity::pageButtonCallback, this, 1));
    //firstPage->setPosition(430,33);
    firstPage->setPosition(tmp+Vec2(-174,-162));
    previousPage = MenuItemImage::create("CommonAssets/previousPage.png", "CommonAssets/previousPage.png",CC_CALLBACK_1(ListEntity::pageButtonCallback, this, 2));
    //previousPage->setPosition(465, 33);
    previousPage->setPosition(tmp+Vec2(-139,-162));
    nextPage = MenuItemImage::create("CommonAssets/nextPage.png", "CommonAssets/nextPage.png",CC_CALLBACK_1(ListEntity::pageButtonCallback, this, 3));
    //nextPage->setPosition(685, 33);
    nextPage->setPosition(tmp+Vec2(81,-162));
    lastPage = MenuItemImage::create("CommonAssets/lastPage.png", "CommonAssets/lastPage.png",CC_CALLBACK_1(ListEntity::pageButtonCallback, this, 4));
    //lastPage->setPosition(720, 33);
    lastPage->setPosition(tmp+Vec2(116,-162));
    menu->addChild(firstPage);
    menu->addChild(previousPage);
    menu->addChild(nextPage);
    menu->addChild(lastPage);
    
    if (maxPage<5) {
        labelPage.resize(maxPage+1);
    }
    else
        labelPage.resize(5);
    for (int i=0; i<labelPage.size(); ++i)
    {
        labelPage[i]=MenuItemLabel::create(Label::create(to_string(i+1), "fonts/DengXian.ttf", 16), CC_CALLBACK_1(ListEntity::pageNumberCallback, this, i));
        //labelPage[i]->setPosition(Vec2(502+i*37, 33));
        labelPage[i]->setPosition(tmp+Vec2(-102+i*37, -162));
        labelPage[i]->setColor(FONT_COLOR);
        menu->addChild(labelPage[i]);
    }
    labelPage[0]->setColor(Color3B(0,127,255));
}

void ListEntity::pageNumberCallback(cocos2d::Ref *pSender, int index)
{
    preCurrPage=currentPage;
    preMidPage=midPage;
    labelPage[currentPage-midPage+2]->setColor(FONT_COLOR);
    int foot=index-2;
    currentPage=foot+midPage;
    if (!isMove)
    {
        
    }else
    {
        if (foot>0)
        {
            while (foot&&((midPage+2)<maxPage))
            {
                ++midPage;
                --foot;
            }
        }
        else
        {
            while (foot&&((midPage-2)>0))
            {
                --midPage;
                ++foot;
            }
        }
    }
    
    labelPage[currentPage-midPage+2]->setColor(Color3B(0,127,255));
    updatePage();
}



void ListEntity::pageButtonCallback(cocos2d::Ref *pSender, int index)
{
    preCurrPage=currentPage;
    preMidPage=midPage;
    labelPage[currentPage-midPage+2]->setColor(FONT_COLOR);
    switch (index)
    {
        case 1:
            currentPage=0;
            if (isMove) {
                midPage=2;
            }
            
            break;
        case 2:
            if (!currentPage) {
                break;
            }
            --currentPage;
            if (isMove)
            {
                while (midPage>currentPage&&(midPage-2)>0)
                    --midPage;
            }
            break;
        case 3:
            if (currentPage==maxPage) {
                break;
            }
            ++currentPage;
            if (isMove)
            {
                while (midPage<currentPage&&(midPage+2)<maxPage)
                    ++midPage;
            }
            break;
        case 4:
            currentPage=maxPage;
            if (isMove) {
                midPage=maxPage-2;
            }
            break;
        default:
            break;
    }
    labelPage[currentPage-midPage+2]->setColor(Color3B(0,127,255));
    updatePage();
}

void ListEntity::updatePage()
{
    if (preCurrPage!=currentPage)
    {
        updateRows();
    }
    preCurrPage=currentPage;
    
    if (isMove) {
        if (preMidPage!=midPage)
        {
            for (int i=0; i<5; ++i)
            {
                labelPage[i]->setString(to_string(midPage-1+i));
            }
        }
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
        initPageSwitch();
        setHide(true);
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

void ListEntity::updateRows()
{
    int i=currentPage*10;
    int j=0;
    while (i<displayKantai.size()&&j<10)
    {
        rows[j]->update(displayKantai[i]);
        rows[j]->setVisible(true);
        //rows[j]->setEnable(true);
        ++j;
        ++i;
    }
    while (j<10)
    {
        rows[j]->setVisible(false);
        //rows[j]->setEnable(false);
        ++j;
    }
}


NS_KCL_END







