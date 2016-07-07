//
//  RepairListEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#include "RepairListEntity.hpp"
#include "KantaiListEntity.hpp"
#include "portRepairLayer.h"
#include <algorithm>

NS_KCL_BEGIN

#define SHIPS_PER_PAGE 10
#define FONT_COLOR Color3B::BLACK



RepairListEntity::RepairListEntity()
{
    rows.resize(10);
}

void RepairListEntity::moveOut()
{
    if (!hidden)
    {
        this->runAction(MoveBy::create(0.2, Point(800, 0)));
        hidden = true;
    }
    
}
void RepairListEntity::moveIn()
{
    if (hidden)
    {
        this->runAction(MoveBy::create(0.2, Point(-800, 0)));
        hidden = false;
    }
}


void RepairListEntity::setRowVisble(int position, bool bVisible)
{
    CCASSERT(position>=1&&position<=10, "kantai row isn't exist");
    rows[position-1]->setVisible(bVisible);
    rows[position-1]->setVisible(bVisible);
}


void RepairListEntity::initBg()
{
    hidden = true;
    menu = Menu::create(NULL);
    menu->setPosition(Vec2::ZERO);
    
    //bg
    auto bgimg = Sprite::create("RepairMain/repairListBg.png");
    this->addChild(bgimg);
    bgimg->setPosition(644, 195);
    
    auto top_label = Sprite::create("RepairMain/repairListTitle.png");
    this->addChild(top_label);
    top_label->setPosition(388, 399);
    
    auto category = Sprite::create("RepairMain/repairListCate.png");
    this->addChild(category);
    category->setPosition(585, 370);
    

}

void RepairListEntity::hideSelect(cocos2d::Ref *pSender)
{
    selectEntity->moveOut();
    selectCover->setCoverEnable(false);
}

void RepairListEntity::showSelect(Kantai* kantai)
{
    selectEntity->moveIn();
    selectEntity->updateKantai(kantai);
    selectCover->setCoverEnable(true);
}

void RepairListEntity::initSortButton()
{
    MenuItemSprite* sortButtonUnitLV=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByLV.png"), Sprite::create("OrganizeMain/sortByLV.png"));
    MenuItemSprite* sortButtonUnitCate=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByCate.png"), Sprite::create("OrganizeMain/sortByCate.png"));
    MenuItemSprite* sortButtonUnitHP=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByHp.png"), Sprite::create("OrganizeMain/sortByHp.png"));
    MenuItemSprite* sortButtonUnitNew=MenuItemSprite::create(Sprite::create("OrganizeMain/sortByNew.png"), Sprite::create("OrganizeMain/sortByNew.png"));
    
    sortButton=MenuItemToggle::createWithCallback(CC_CALLBACK_1(RepairListEntity::sortButtonCallback, this), sortButtonUnitLV,sortButtonUnitCate,sortButtonUnitHP,sortButtonUnitNew, NULL);
    sortButton->setPosition(773, 370);
    menu->addChild(sortButton);
    
    displayKantai=sPlayer.kantaiData;
    sort(displayKantai.begin(), displayKantai.end(), [](const Kantai* lhs,const Kantai* rhs)
         {
             return lhs->getCurrLV()>rhs->getCurrLV();
         });
    
}

void RepairListEntity::initRows()
{
    for (int i=0; i<10; ++i)
    {
        rows[i]=RepairListRow::create(i+1);
        rows[i]->setPosition(540, 345 - (i+1) * 28);
        addChild(rows[i],2);
    }
}

void RepairListEntity::initPageSwitch()
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
    
    firstPage = MenuItemImage::create("CommonAssets/firstPage.png", "CommonAssets/firstPage.png",CC_CALLBACK_1(RepairListEntity::pageButtonCallback, this, 1));
    firstPage->setPosition(430,33);
    previousPage = MenuItemImage::create("CommonAssets/previousPage.png", "CommonAssets/previousPage.png",CC_CALLBACK_1(RepairListEntity::pageButtonCallback, this, 2));
    previousPage->setPosition(465, 33);
    nextPage = MenuItemImage::create("CommonAssets/nextPage.png", "CommonAssets/nextPage.png",CC_CALLBACK_1(RepairListEntity::pageButtonCallback, this, 3));
    nextPage->setPosition(685, 33);
    lastPage = MenuItemImage::create("CommonAssets/lastPage.png", "CommonAssets/lastPage.png",CC_CALLBACK_1(RepairListEntity::pageButtonCallback, this, 4));
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
        labelPage[i]=MenuItemLabel::create(Label::create(to_string(i+1), "fonts/DengXian.ttf", 16), CC_CALLBACK_1(RepairListEntity::pageNumberCallback, this, i));
        labelPage[i]->setPosition(Vec2(502+i*37, 33));
        labelPage[i]->setColor(FONT_COLOR);
        menu->addChild(labelPage[i]);
    }
    labelPage[0]->setColor(Color3B(0,127,255));
}

void RepairListEntity::pageNumberCallback(cocos2d::Ref *pSender, int index)
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



void RepairListEntity::pageButtonCallback(cocos2d::Ref *pSender, int index)
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

void RepairListEntity::updatePage()
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


bool RepairListEntity::init()
{
    bool bRet=false;
    do
    {
        
        if (!Node::init())
        {
            break;
        }
        
        initBg();
        initSortButton();
        initRows();
        initPageSwitch();
        addChild(menu);
        updateRows();
        
        
        selectCover=LayerCover::create(CC_CALLBACK_1(RepairListEntity::hideSelect, this));
        selectCover->setPosition(0,0);
        addChild(selectCover,2);
        
        selectEntity=RepairSelectEntity::create();
        selectEntity->setPosition(238,0);
        //addChild(selectEntity,3);
        
        bRet=true;
    }while(0);
    return bRet;
}

void RepairListEntity::sortButtonCallback(cocos2d::Ref *pSender)
{
    int index=sortButton->getSelectedIndex();
    function<bool(const Kantai*,const Kantai*)> fun;
    switch (index)
    {
        case 1:
            fun=[](const Kantai* lhs,const Kantai* rhs){return lhs->getKantaiType()>rhs->getKantaiType();};
            break;
        case 2:
            fun=[](const Kantai* lhs,const Kantai* rhs)
            {
                float lMax=lhs->getMaxHp();
                float lCurr=lhs->getCurrHp();
                float rMax=rhs->getMaxHp();
                float rCurr=rhs->getCurrHp();
                rMax=rMax?rMax:1;
                lMax=lMax?lMax:1;
                return (lCurr/lMax)<(rCurr/rMax);
            };
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

void RepairListEntity::updateRows()
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