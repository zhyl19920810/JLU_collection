//
//  portRepairLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portRepairLayer__
#define __kancolle_alpha__portRepairLayer__

#include "cocos2d.h"
#include "RepairContainer.hpp"
#include "RepairListEntity.hpp"
#include "dock.hpp"
#include "RepairSelectEntity.hpp"
#include "Panel.hpp"

using namespace cocos2d;

NS_KCL_BEGIN

class PortRepairLayer : public Panel
{
public:
    PortRepairLayer();
    CREATE_FUNC(PortRepairLayer);
    bool init();
    
    
    //list
    void updateContainer();

    
private:
    //bg
    void initLayer();
    std::vector<RepairContainerParent*> container;
    int containerSize;
    
    //container
    void initContainer();
    
private:
    RepairListEntity* listEntity;
public:
    void showList(int index);
    void hideList(Ref* pSender);
    
    
private:
    RepairSelectEntity* selectEntity;
public:
    void showSelect(Kantai* kantai);
    
public:
    void startRepairKantai(Kantai* kantai,int steel,int fuel,int time);
    void selectKantai(int positon);
private:
    int position;
};



NS_KCL_END
#endif /* defined(__kancolle_alpha__portRepairLayer__) */
