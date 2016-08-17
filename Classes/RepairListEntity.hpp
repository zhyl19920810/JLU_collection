//
//  RepairListEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//






#ifndef RepairListEntity_hpp
#define RepairListEntity_hpp

//#include "cocos2d.h"
//#include "kantai.h"
//#include "RepairListRow.hpp"
//#include "LayerCover.hpp"



//using namespace cocos2d;
//
//
//NS_KCL_BEGIN
//
//class RepairListEntity:public Node
//{
//public:
//    RepairListEntity();
//    void moveOut();
//    void moveIn();
//    inline bool isHidden(){ return hidden; }
//    CREATE_FUNC(RepairListEntity);
//    bool init() override;
//    void updateRows();
//private:
//
//    
//    //bg
//    bool hidden;
//    void initBg();
//    Menu *menu;
//    
//    //row
//    std::vector<RepairListRow*> rows;
//    void setRowVisble(int position,bool bVisible);
//    void initRows();
//    //page
//    void setPageCallback(Ref* pSender,int pageNumber);
//    void initPageSwitch();
//    int currentPage;
//    int maxPage;
//    int midPage;
//    int preMidPage;
//    int preCurrPage;
//    bool isMove;
//    MenuItemImage* firstPage;
//    MenuItemImage* previousPage;
//    MenuItemImage* nextPage;
//    MenuItemImage* lastPage;
//    std::vector<MenuItemLabel*> labelPage;
//    void pageButtonCallback(Ref* pSender,int index);
//    void pageNumberCallback(Ref* pSender,int index);
//    void updatePage();
//    
//    //sort
//    void initSortButton();
//    MenuItemToggle* sortButton;
//    void sortButtonCallback	(Ref* pSender);
//    std::vector<Kantai*> displayKantai;
//    
//    
//public:
//    
//};
//
//NS_KCL_END

#include "cocos2d.h"
#include "kantai.h"
#include "ListEntity.hpp"
#include "LayerCover.hpp"


NS_KCL_BEGIN


USING_NS_CC;


class RepairListEntity:public ListEntity
{
public:
    static RepairListEntity* create(Vec2 vec);
    void showSelect(Kantai* kantai);
    
    bool init(Vec2 vec);
private:
    
    
};


NS_KCL_END


#endif /* RepairListEntity_hpp */

















