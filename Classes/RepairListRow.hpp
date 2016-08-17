////
////  RepairListRow.hpp
////  kancolle_beta
////
////  Created by 岩林张 on 1/30/16.
////
////
//
//#ifndef RepairListRow_hpp
//#define RepairListRow_hpp
//
//
//#include "cocos2d.h"
//#include "Player.h"
//#include "RepairHpBar.hpp"
//USING_NS_CC;
//
//NS_KCL_BEGIN
//
//
//#define FONT_COLOR Color3B::BLACK
//
//class RepairListRow:public Node
//{
//public:
//    static RepairListRow* create(int position)
//    {
//        RepairListRow* tmp=new(std::nothrow) RepairListRow;
//        if (tmp&&tmp->init(position))
//        {
//            tmp->autorelease();
//            return tmp;
//        }
//        delete tmp;
//        tmp=NULL;
//        return NULL;
//    }
//    RepairListRow();
//    void setEnable(bool bVisible);
//    bool init(int position);
//    
//    void update(Kantai* kantai);
//private:
//    virtual void exchangeCallback(cocos2d::Ref *pSender);
//    int position;
//    Sprite* line;
//    Sprite* fleetIcon;
//    Label* kantaiName;
//    Label* level;
//    Label* HP;
//    Sprite* broke;
//    RepairHpBar* hpBar;
//    MenuItemSprite* menuItem;
//    Kantai* kantai;
//};
//
//NS_KCL_END
//
//
//#endif /* RepairListRow_hpp */
