//
//  OrganizeContainer.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/27/16.
//
//

#ifndef _ORGANIZE_CONTAINER_
#define _ORGANIZE_CONTAINER_

#include "cocos2d.h"
#include "kantai.h"
#include "Star.hpp"
#include "HpBar.hpp"
#include "kantaiCard.hpp"
#define NUMBER_OF_CONTAINERS 6

using namespace cocos2d;
class PortOrganizeLayer;

class OrganizeContainer:public Node{
    
public:
    static OrganizeContainer* create(int position);

    bool init();
    OrganizeContainer(int position);
    void updateCharacterInfo(Kantai* kantai);
    
    void detailCallback(Ref* pSender);
    void changeCallback(Ref* pSender);
    void setDetailButtonEnble(bool bEnble);
    void setChangeButtonEnble(bool bEnble);
private:
    int position;
    Sprite* bg;
    Sprite *indexIcon;
    
    
    MenuItemImage * detailButton;
    MenuItemImage * changeButton;
    
    KantaiCard * kantaiCard;
    Sprite * characterImage;
    Label * kantaiName;
    Label * currLV;
    Label * currHp;
    Label* firePower;
    Label * antiAir;
    Label * torpedo;
    Label * armour;
    HpBar* hpBar;
    Stars * stars;
    
};

#endif