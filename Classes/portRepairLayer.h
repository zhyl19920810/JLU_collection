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


using namespace cocos2d;
class PortRepairLayer : public Layer
{
public:
    PortRepairLayer();
    CREATE_FUNC(PortRepairLayer);
    bool init();
    void update();
private:
    
    
private:
    //bg
    void initLayer();
    std::vector<RepairContainerParent*> container;
    
    int containerSize;
    
    
    //container
    void initContainer();
};


#endif /* defined(__kancolle_alpha__portRepairLayer__) */
