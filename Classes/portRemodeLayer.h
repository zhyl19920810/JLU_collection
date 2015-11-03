//
//  portRemodeLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portRemodeLayer__
#define __kancolle_alpha__portRemodeLayer__

#include "cocos2d.h"
using namespace cocos2d;
class PortRemodeLayer : public Layer
{
public:
    PortRemodeLayer(Node *parent);
    void callBack(Ref* pSender);
    
    
private:
    Node * parent;
    
    
private:
    void initLayer();
    
};


#endif /* defined(__kancolle_alpha__portRemodeLayer__) */
