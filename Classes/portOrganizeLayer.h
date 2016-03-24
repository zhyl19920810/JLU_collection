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
#include "FleetButton.hpp"
#include "LayerCover.hpp"

using namespace cocos2d;
class PortScene;

class PortOrganizeLayer : public Layer
{
public:
    bool init();
    CREATE_FUNC(PortOrganizeLayer);
    PortOrganizeLayer();
    
    void hideDetail(Ref* pSender);
    void showDetail(int index);
    void hideList(Ref* pSender);
    void showList(int index);
    
    void updateContainer();
    void updateContainer(int position);
    void changeContainer(Kantai* kantai);
    void removeContainer();
    inline int getSelectedShipIndex(){ return selectedShipIndex; }
    inline void setSelectedShipIndex(int index)
    {
        this->selectedShipIndex = index;
    }
    Fleet* getPanelFleet(){return fleet;}
    //void setChangeButtonEnble(bool bEnble);
    //void setDetailButtonEnble(bool bEnble);
    bool hasSameKantai(int kantaiNumber);
    
    void clearFleet(Ref* pSender);
    
    void setListable(bool bVisible);
private:
    KantaiDetailEntity* detailEntity;
    KantaiListEntity* listEntity;
    //MenuItemSprite * hideDetailItem;
    //MenuItemSprite * hideListItem;
    int selectedShipIndex;
    std::vector<OrganizeContainer *> containers;
    
    
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
    //LayerColor* bgCover;
    //EventListenerTouchOneByOne* listener;
    
    FleetButton* fleetButton;
public:
    ~PortOrganizeLayer();
    void updateFleet(int fleetNumber);
    int findFirstPosNoKantai();
    bool hasKantai(int position);
    
    
private:
    LayerCover* detailCover;
    LayerCover* listCover;
};


#endif