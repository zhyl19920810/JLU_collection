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
    void changeContainer(Kantai* preKantai,Kantai* kantai);
    void openNewContainer(Kantai* kantai);
    bool haveKantai() const;
    Kantai* getKantai(){return kantai;}
    int getContainerKantaiNumber() const;
    void setChangeButtonVisible(bool bVisible);
    
private:
    void setCoverVisble(bool bVisible,bool coverButton=false);
    void setKantaiVisible( bool bVisible);
    void detailCallback(Ref* pSender);
    void changeCallback(Ref* pSender);

private:
    bool init();
    void initBg();
    void initMainBody();
    void initCover();
    
    
private:
    int position;
    Sprite* bg;
    //Sprite *indexIcon;
    MenuItemImage * detailButton;
    MenuItemImage * changeButton;
    bool kantaiExist;
    KantaiCard * kantaiCard;
    Label* kantaiName;
    Label* currLV;
    Label* currHp;
    Label* firePower;
    Label* antiAir;
    Label* torpedo;
    Label* armour;
    HpBar* hpBar;
    Stars * stars;
    Sprite* expBar;
    Menu* menu;
    Kantai* kantai;
    Sprite* lKantaiDoor;
    Sprite* rKantaiDoor;
    Node* templateNode;
    ClippingNode* clippingNode;
    Node* node;

};

NS_KCL_END

#endif