//
//  KantaiListEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef KantaiListEntity_hpp
#define KantaiListEntity_hpp


#include "cocos2d.h"
#include "kantai.h"
#include "KantaiListRow.hpp"
#include "OrganizeSelectEntity.hpp"
using namespace cocos2d;
class PortOrganizeLayer;




class KantaiListEntity:public Layer
{
public:
    KantaiListEntity();
    void moveOut();
    void moveIn();
    inline bool isHidden(){ return hidden; }
    CREATE_FUNC(KantaiListEntity);
    bool init() override;
    void update();
    void updateRows();
private:

    //    Menu *listMenu;
    //    Node *firstRow;
    //    Node *list;
  
    
    
//bg
    bool hidden;
    void initBg();
    Menu *menu;

//row
    std::vector<KantaiListRow*> rows;
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
    
    
    OrganSelectEntity* organSelectEntity;
    
    void hideSelect(cocos2d::Ref *pSender);
    MenuItemSprite* hideListItem;
//sort
    void initSortButton();
    MenuItemToggle* sortButton;
    void sortButtonCallback	(Ref* pSender);
    std::vector<Kantai*> displayKantai;
    
    
public:
    void showSelect(Kantai* kantai);
    
};


#endif /* KantaiListEntity_hpp */
