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
#include "Panel.hpp"


using namespace cocos2d;

NS_KCL_BEGIN

class PortScene;

class PortOrganizeLayer : public Panel
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
    bool canChangeKantai(Kantai* kantai);
    
    
    void clearFleet(Ref* pSender);
    
    void setListable(bool bVisible);
private:
    KantaiDetailEntity* detailEntity;
    KantaiListEntity* listEntity;
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
    
    FleetButton* fleetButton;
public:
    ~PortOrganizeLayer();
    void updateFleet(int fleetNumber);
    int findFirstPosNoKantai();
    bool hasKantai(int position);
    
    
private:
    LayerCover* detailCover;
    LayerCover* listCover;
    int displayChangeButtonPos;
};


NS_KCL_END

#endif