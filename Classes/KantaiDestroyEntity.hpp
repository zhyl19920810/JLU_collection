//
//  KantaiDestroyEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/6/16.
//
//

#ifndef KantaiDestroyEntity_hpp
#define KantaiDestroyEntity_hpp


#include "cocos2d.h"
#include "kantaiCard.hpp"
#include "MenuItemTouch.hpp"
USING_NS_CC;

NS_KCL_BEGIN



class KantaiDestroyEntity:public Layer
{
public:
    CREATE_FUNC(KantaiDestroyEntity);
    bool init();
    
    KantaiDestroyEntity();
    
    
    void initBg();
    void initKantai();
    void update(Kantai* kantai);
    
    void moveOut();
    void moveIn();
    void destroyCallback(Ref* pSender);
    bool canDestroyKantai(Kantai* kantai);
private:
    
    bool hidden;
    Sprite* bgImg;
    MenuItemButton* destroyButton;
    KantaiCard* kantaiCard;
    Kantai* kantai;
    
    Label* fuel;
    Label* ammo;
    Label* steel;
    Label* al;
    
    int fuelVal;
    int ammoVal;
    int steelVal;
    int alVal;
    
};

NS_KCL_END

#endif /* KantaiDestroyEntity_hpp */
