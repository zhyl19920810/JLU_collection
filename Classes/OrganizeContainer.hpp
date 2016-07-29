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


NS_KCL_BEGIN

class PortOrganizeLayer;
class OrganizeContainer;

class OrganizeContainerAction
{
public:
    static void setPankOpen(OrganizeContainer*);
    static void setPankClose(OrganizeContainer*);
    static void setPankChange(OrganizeContainer*);
};


class OrganizeContainer:public Node
{
    friend class OrganizeContainerAction;
    friend class PortOrganizeLayer;
public:
    static OrganizeContainer* create(int position);
    OrganizeContainer(int position);
    
    void updateCharacterInfo(Kantai* kantai);
    void setKantaiVisible( bool bVisible);
    void setCoverVisble(bool bVisible,bool coverButton=false);
    bool haveKantai() const;
    int getContainerKantaiNumber() const;

    
    void changeContainer(Kantai* kantai);
    void openNewContainer(Kantai* kantai);
    
public:
    void detailCallback(Ref* pSender);
    void changeCallback(Ref* pSender);
    void setDetailButtonEnble(bool bEnble);
    void setChangeButtonEnble(bool bEnble);
    void setChangeButtonVisible(bool bVisible);
    
private:
    int position;
    Sprite* bg;
    Sprite *indexIcon;
    
    
    MenuItemImage * detailButton;
    MenuItemImage * changeButton;
    bool kantaiExist;
    KantaiCard * kantaiCard;
    Label * kantaiName;
    Label * currLV;
    Label * currHp;
    Label* firePower;
    Label * antiAir;
    Label * torpedo;
    Label * armour;
    HpBar* hpBar;
    Stars * stars;
    Sprite* expBar;
    Menu* menu;
    
    Kantai* kantai;
    Sprite* lKantaiDoor;
    Sprite* rKantaiDoor;
    
private:
    bool init();
    void initBg();
    void initMainBody();
    void initCover();
    
    
private:
    Node* templateNode;
    ClippingNode* clippingNode;
    Node* node;

};

NS_KCL_END

#endif