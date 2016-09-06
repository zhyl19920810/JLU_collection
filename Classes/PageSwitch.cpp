//
//  PageSwitch.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/30/16.
//
//

#include "PageSwitch.hpp"

#define FONT_COLOR Color3B::BLACK

NS_KCL_BEGIN



void PageSwitch::initPageSwitch()
{
    
    currentPage=0;
    midPage=2;
    auto menu = Menu::create(NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu,2);
    
    
    
    firstPage = MenuItemImage::create("CommonAssets/firstPage.png", "CommonAssets/firstPage.png",CC_CALLBACK_1(PageSwitch::pageButtonCallback, this, 1));
    //firstPage->setPosition(430,33);
    firstPage->setPosition(Vec2(-174,-162));
    previousPage = MenuItemImage::create("CommonAssets/previousPage.png", "CommonAssets/previousPage.png",CC_CALLBACK_1(PageSwitch::pageButtonCallback, this, 2));
    //previousPage->setPosition(465, 33);
    previousPage->setPosition(Vec2(-139,-162));
    nextPage = MenuItemImage::create("CommonAssets/nextPage.png", "CommonAssets/nextPage.png",CC_CALLBACK_1(PageSwitch::pageButtonCallback, this, 3));
    //nextPage->setPosition(685, 33);
    nextPage->setPosition(Vec2(81,-162));
    lastPage = MenuItemImage::create("CommonAssets/lastPage.png", "CommonAssets/lastPage.png",CC_CALLBACK_1(PageSwitch::pageButtonCallback, this, 4));
    //lastPage->setPosition(720, 33);
    lastPage->setPosition(Vec2(116,-162));
    menu->addChild(firstPage);
    menu->addChild(previousPage);
    menu->addChild(nextPage);
    menu->addChild(lastPage);
    
    labelPage.resize(5);
    for (int i=0; i<5; ++i)
    {
        labelPage[i]=MenuItemLabel::create(Label::create(std::to_string(i+1), "fonts/DengXian.ttf", 16), CC_CALLBACK_1(PageSwitch::pageNumberCallback, this, i));
        //labelPage[i]->setPosition(Vec2(502+i*37, 33));
        labelPage[i]->setPosition(Vec2(-102+i*37, -162));
        labelPage[i]->setColor(FONT_COLOR);
        labelPage[i]->setVisible(false);
        menu->addChild(labelPage[i]);
    }
    labelPage[0]->setColor(Color3B(0,127,255));
    
    updatePageNum();
    
}


void PageSwitch::updatePageNum()
{
    maxPage=(displaySize-1)/10;
    if (maxPage<5)
    {
        isMove=false;
    }else
    {
        isMove=true;
    }
    if (maxPage<5)
    {
        labelPageSize=maxPage+1;
    }
    else
    {
        labelPageSize=5;
    }
    if (currentPage>maxPage) currentPage=maxPage;
        
    int i=0;
    for (; i<labelPageSize; ++i)
    {
        labelPage[i]->setVisible(true);
    }
    while (i<5)
    {
        labelPage[i]->setVisible(false);
        ++i;
    }
    if (isMove)
    {
        if (currentPage<=2)
        {
            midPage=2;
        }
        else if(currentPage>=maxPage-2)
        {
            midPage=maxPage-2;
        }
        else
            midPage=currentPage;
    }
}


void PageSwitch::addKantai()
{
    ++displaySize;
    updatePageNum();
    updatePage();
}

void PageSwitch::destroyKantai()
{
    --displaySize;
    updatePageNum();
    updatePage();
}

void PageSwitch::pageNumberCallback(cocos2d::Ref *pSender, int index)
{
//    preCurrPage=currentPage;
//    preMidPage=midPage;
    labelPage[currentPage-midPage+2]->setColor(FONT_COLOR);
    int foot=index-2;
    currentPage=foot+midPage;
//    if (!isMove)
//    {
//        
//    }else
//    {
//        if (foot>0)
//        {
//            while (foot&&((midPage+2)<maxPage))
//            {
//                ++midPage;
//                --foot;
//            }
//        }
//        else
//        {
//            while (foot&&((midPage-2)>0))
//            {
//                --midPage;
//                ++foot;
//            }
//        }
//    }
    updatePageNum();
    labelPage[currentPage-midPage+2]->setColor(Color3B(0,127,255));
    updatePage();
}



void PageSwitch::pageButtonCallback(cocos2d::Ref *pSender, int index)
{
//    preCurrPage=currentPage;
//    preMidPage=midPage;
    labelPage[currentPage-midPage+2]->setColor(FONT_COLOR);
//    switch (index)
//    {
//        case 1:
//            currentPage=0;
//            if (isMove) {
//                midPage=2;
//            }
//            
//            break;
//        case 2:
//            if (!currentPage) {
//                break;
//            }
//            --currentPage;
//            if (isMove)
//            {
//                while (midPage>currentPage&&(midPage-2)>0)
//                    --midPage;
//            }
//            break;
//        case 3:
//            if (currentPage==maxPage) {
//                break;
//            }
//            ++currentPage;
//            if (isMove)
//            {
//                while (midPage<currentPage&&(midPage+2)<maxPage)
//                    ++midPage;
//            }
//            break;
//        case 4:
//            currentPage=maxPage;
//            if (isMove) {
//                midPage=maxPage-2;
//            }
//            break;
//        default:
//            break;
//    }

    
    switch (index)
    {
        case 1:
            currentPage=0;
            break;
        case 2:
            if (!currentPage) break;
            --currentPage;
            break;
        case 3:
            if (currentPage==maxPage) break;
            ++currentPage;
            break;
        case 4:
            currentPage=maxPage;
            break;
            default:
            break;
    }
    

    updatePageNum();
    labelPage[currentPage-midPage+2]->setColor(Color3B(0,127,255));
    updatePage();
}

void PageSwitch::updatePage()
{
    callback(currentPage);
    for (int i=0; i<5; ++i)
    {
        labelPage[i]->setString(std::to_string(midPage-1+i));
    }
}

PageSwitch* PageSwitch::create(UpdateCallback callback, int displaySize)
{
    PageSwitch* pRet=new PageSwitch;
    if (pRet&&pRet->init(callback, displaySize))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool PageSwitch::init(UpdateCallback callback, int displaySize)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        this->displaySize=displaySize;
        this->callback=callback;
        initPageSwitch();
        
        bRet=true;
    }
    while(0);
    return bRet;
}









NS_KCL_END