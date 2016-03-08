//
//  ListEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/5/16.
//
//

#include "ListEntity.hpp"
#include "portOrganizeLayer.h"



#include <algorithm>


#define SHIPS_PER_PAGE 10
#define FONT_COLOR Color3B::BLACK



ListEntity::ListEntity()
{
    rows.resize(10);
}

void ListEntity::moveOut()
{
    if (!hidden)
    {
        this->runAction(MoveBy::create(0.4, Point(800, 0)));
        hidden = true;
    }
    
}
void ListEntity::moveIn()
{
    if (hidden)
    {
        this->runAction(MoveBy::create(0.4, Point(-800, 0)));
        hidden = false;
    }
}


void ListEntity::setRowVisble(int position, bool bVisible)
{
    CCASSERT(position>=1&&position<=10, "kantai row isn't exist");
    rows[position-1]->setVisible(bVisible);
    rows[position-1]->setVisible(bVisible);
}


void ListEntity::initBg()
{
    hidden = true;
    menu = Menu::create(NULL);
    menu->setPosition(Vec2::ZERO);
    //bg
    auto bgimg = Sprite::create("OrganizeMain/kantaiListBg1.png");
    this->addChild(bgimg);
    bgimg->setPosition(654, 195);
    
    auto titleBar = Sprite::create("OrganizeMain/kantaiListTitle.png");
    this->addChild(titleBar);
    titleBar->setPosition(753, 397);
    
    auto top_label = Sprite::create("OrganizeMain/kantaiListLabel.png");
    this->addChild(top_label);
    top_label->setPosition(398, 399);
    
    auto category = Sprite::create("OrganizeMain/kantaiListCate.png");
    this->addChild(category);
    category->setPosition(595, 370);
    

    
    auto closeItem2 = Sprite::create("CommonAssets/image 451.png");
    closeItem2->setGlobalZOrder(10);
    closeItem2->setOpacity(0);
    hideListItem = MenuItemSprite::create(closeItem2, closeItem2, CC_CALLBACK_1(ListEntity::hideSelect, this));
    hideListItem->setPosition(170, 240);
    hideListItem->setEnabled(false);
    menu->addChild(hideListItem);
    hideListItem->setGlobalZOrder(10);
    
}



void ListEntity::initSortButton()
{
    MenuItemSprite* sortButtonUnitLV=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByLV.png"), Sprite::create("OrganizeMain/sortByLV.png"));
    MenuItemSprite* sortButtonUnitCate=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByCate.png"), Sprite::create("OrganizeMain/sortByCate.png"));
    MenuItemSprite* sortButtonUnitHP=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByHp.png"), Sprite::create("OrganizeMain/sortByHp.png"));
    MenuItemSprite* sortButtonUnitNew=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByNew.png"), Sprite::create("OrganizeMain/sortByNew.png"));
    
    sortButton=MenuItemToggle::createWithCallback(CC_CALLBACK_1(ListEntity::sortButtonCallback, this), sortButtonUnitLV,sortButtonUnitCate,sortButtonUnitHP,sortButtonUnitNew, NULL);
    sortButton->setPosition(773, 370);
    menu->addChild(sortButton);
    
    
    displayKantai=sPlayer.kantaiData;
    sort(displayKantai.begin(), displayKantai.end(), [](const Kantai* lhs,const Kantai* rhs)
         {
             return lhs->getCurrLV()>rhs->getCurrLV();
         });
    
}

void ListEntity::initRows()
{

    
    for (int i=0; i<10; ++i)
    {
        rows[i]=ListRow::create(i+1);
        rows[i]->setPosition(540, 345 - (i + 1) * 28);
        addChild(rows[i]);
    }
}



void ListEntity::initPageSwitch()
{
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
    firstPage->setPosition(430,33);
    previousPage = MenuItemImage::create("CommonAssets/previousPage.png", "CommonAssets/previousPage.png",CC_CALLBACK_1(ListEntity::pageButtonCallback, this, 2));
    previousPage->setPosition(465, 33);
    nextPage = MenuItemImage::create("CommonAssets/nextPage.png", "CommonAssets/nextPage.png",CC_CALLBACK_1(ListEntity::pageButtonCallback, this, 3));
    nextPage->setPosition(685, 33);
    lastPage = MenuItemImage::create("CommonAssets/lastPage.png", "CommonAssets/lastPage.png",CC_CALLBACK_1(ListEntity::pageButtonCallback, this, 4));
    lastPage->setPosition(720, 33);
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
        labelPage[i]->setPosition(Vec2(502+i*37, 33));
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


bool ListEntity::init()
{
    bool bRet=false;
    do
    {
        
        if (!Layer::init())
        {
            break;
        }
        
        initBg();
        initSortButton();
        initRows();
        initPageSwitch();
        addChild(menu);
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









