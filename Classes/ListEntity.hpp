//
//  ListEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/5/16.
//
//

#ifndef ListEntity_hpp
#define ListEntity_hpp


#include "cocos2d.h"
#include "kantai.h"
#include "ListRow.hpp"
#include "OrganizeSelectEntity.hpp"
#include "LayerCover.hpp"
using namespace cocos2d;

NS_KCL_BEGIN

class ListEntity:public Node
{
public:
    ListEntity();
    void moveOut();
    void moveIn();
    
    
    inline bool isHidden(){ return hidden; }
    bool init(Vec2 vec);
    void updateRows();
    
private:
    //bg
    void initBg(Vec2 vec);
    
    //row
    std::vector<ListRow*> rows;
    void setRowVisble(int position,bool bVisible);
    void initRows();
    //page
    void setPageCallback(Ref* pSender,int pageNumber);
    void initPageSwitch();
    int currentPage;
    int maxPage;
    int midPage;
    int preMidPage;
    int preCurrPage;
    bool isMove;
    MenuItemImage* firstPage;
    MenuItemImage* previousPage;
    MenuItemImage* nextPage;
    MenuItemImage* lastPage;
    std::vector<MenuItemLabel*> labelPage;
    void pageButtonCallback(Ref* pSender,int index);
    void pageNumberCallback(Ref* pSender,int index);
    void updatePage();
    
    
    //sort
    void initSortButton();
    MenuItemToggle* sortButton;
    void sortButtonCallback	(Ref* pSender);
    
    
    
public:
    void setHide(bool _hide);
    virtual void showSelect(Kantai* kantai)=0;
    virtual void removeCallback(Ref* ref)=0;
    virtual void hideSelect(cocos2d::Ref *pSender)=0;
    
protected:
    
    bool hidden;
    std::vector<Kantai*> displayKantai;
    Menu *menu;
    LayerCover* layerCover;
    EventListenerTouchOneByOne* listener;
    Sprite* bgimg;
    Node* entity;
private:
    
    void hideFunc(Ref* pSender){hideSelect(pSender);}
};

NS_KCL_END


#endif /* ListEntity_hpp */
