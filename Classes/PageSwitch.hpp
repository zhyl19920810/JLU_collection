//
//  PageSwitch.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/30/16.
//
//

#ifndef PageSwitch_hpp
#define PageSwitch_hpp

#include "cocos2d.h"
#include "SystemHeader.h"


NS_KCL_BEGIN


USING_NS_CC;

class PageSwitch:public Node
{
    typedef std::function<void(int)> UpdateCallback;
public:
    static PageSwitch* create(UpdateCallback callback,int displaySize);
    void addKantai();
    void destroyKantai();
private:
    bool init(UpdateCallback callback,int displaySize);
    
    int displaySize;
    UpdateCallback callback;
    
    
    void updatePage();
    void initPageSwitch();
    int currentPage;
    int maxPage;
    int midPage;
//    int preMidPage;
//    int preCurrPage;
    bool isMove;
    int labelPageSize;
    MenuItemImage* firstPage;
    MenuItemImage* previousPage;
    MenuItemImage* nextPage;
    MenuItemImage* lastPage;
    std::vector<MenuItemLabel*> labelPage;
    void pageButtonCallback(Ref* pSender,int index);
    void pageNumberCallback(Ref* pSender,int index);
    
    void updatePageNum();
};







NS_KCL_END



#endif /* PageSwitch_hpp */
