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
using namespace cocos2d;
class PortRepairLayer : public Layer
{
public:
    PortRepairLayer(Node *parent);
    
    
private:
    Node * parent;
    
    
private:
    void initLayer();
    
};


#endif /* defined(__kancolle_alpha__portRepairLayer__) */
