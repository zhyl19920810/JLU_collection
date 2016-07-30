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
    ~PortOrganizeLayer();
    PortOrganizeLayer();

public:
    void updateContainer();
    void updateContainer(int position);
    void updateFleet(int fleetNumber);
    bool canChangeKantai(Kantai* kantai);
    
    
    void changeContainer(Kantai* kantai);
    void removeContainer();
    void clearFleet(Ref* pSender);
     Fleet* getPanelFleet(){return fleet;}
    
public:
    void showDetail(int index);
    
    void hideList(Ref* pSender);
    void showList(int index);
    int getSelectedShipIndex(){ return selectedShipIndex; }
    void setSelectedShipIndex(int index){this->selectedShipIndex = index;}
    
private:
    int selectedShipIndex;
    int displayChangeButtonPos;
    int fleetNumber;
    Fleet* fleet;
    
    
private:
    void initLayer();
    void initFleetButton();
    void initContainers();
    bool hasKantai(int position);
    int findFirstPosNoKantai();
    
private:
    Sprite* bgimg;
    KantaiDetailEntity* detailEntity;
    KantaiListEntity* listEntity;
    LayerCover* listCover;
    FleetButton* fleetButton;
    std::vector<OrganizeContainer *> containers;
    
    
public:
    void showSelect(Kantai* kantai)
    {
        organSelectEntity->updateKantai(kantai);
        organSelectEntity->moveIn();
    }
    
    
private:
    OrganSelectEntity* organSelectEntity;
};


NS_KCL_END

#endif