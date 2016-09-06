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


class PageSwitch;


class ListEntity:public Node
{
public:
    ListEntity();
    void moveOut();
    void moveIn();
    
    inline bool isHidden(){ return hidden; }
    bool init(Vec2 vec);
    void updateRow(int currPage);
    void updateRows();
    void destoryKantai(Kantai* kantai);
    void addKantai(Kantai* kantai);
private:
    //bg
    void initBg(Vec2 vec);
    void setHide(bool _hide);
    
    //row
    std::vector<ListRow*> rows;
    void setRowVisble(int position,bool bVisible);
    void initRows();
    //page

    //sort
    void initSortButton();
    MenuItemToggle* sortButton;
    
public:
    virtual void showSelect(Kantai* kantai)=0;
    
protected:
    bool hidden;
    std::vector<Kantai*> displayKantai;
    LayerCover* layerCover;
    EventListenerTouchOneByOne* listener;
    Sprite* bgimg;
    Node* entity;
    Menu* menu;
protected:
    void sortButtonCallback	(Ref* pSender);
    
private:
    void initPageSwitch();
    PageSwitch* pageSwitch;
    int currPage;

};

NS_KCL_END


#endif /* ListEntity_hpp */
