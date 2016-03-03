//
//  portOrganizeLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef _PORT_ORGANIZE_LAYER_
#define _PORT_ORGANIZE_LAYER_

#include "cocos2d.h"
#include "Player.h"
#include "OrganizeContainer.hpp"
#include "KantaiDetailEntity.hpp"
#include "KantaiListEntity.hpp"
using namespace cocos2d;
class PortScene;

class PortOrganizeLayer : public Layer
{
public:
    bool init();
    CREATE_FUNC(PortOrganizeLayer);
    PortOrganizeLayer();
    void selectFleet(Ref* pSender, int fleetIndex);
    void clearFleet(Ref* pSender);
    void hideDetail(Ref* pSender);
    void showDetail(int index);
    void hideList(Ref* pSender);
    void showList(int index);
    void updateContainers();
    inline int getSelectedShipIndex(){ return selectedShipIndex; }
    inline void setSelectedShipIndex(int index)
    {
        this->selectedShipIndex = index;
    }
    void setKantaiVisible(int position,bool bVisible);
    Fleet* getPanelFleet(){return fleet;}
    void setChangeButtonEnble(bool bEnble);
    void setDetailButtonEnble(bool bEnble);
    bool hasSameKantai(int kantaiNumber);
private:
    KantaiDetailEntity* detailEntity;
    KantaiListEntity* listEntity;
    MenuItemSprite * hideDetailItem;
    MenuItemSprite * hideListItem;
    int selectedShipIndex;
    std::vector<OrganizeContainer *> containers;
    std::vector<Sprite*> lKantaiDoor;
    std::vector<Sprite*> rKantaiDoor;
    
private:
    void initLayer();
    void initFleetButton();
    void initContainers();
    
    

private:
    Sprite* bgimg;
    Fleet* fleet;
    int fleetNumber;
    std::vector<Sprite*> fleetSprite;
    std::vector<MenuItemToggle*> fleetToggle;
    void fleetCallback(Ref* pSender,int layNumber);
    void changeFleet(int fleetNumber);
public:
    ~PortOrganizeLayer();
    void SetFleetButtonVisible(int fleetNumber,bool bVisible);
    
    
};


#endif