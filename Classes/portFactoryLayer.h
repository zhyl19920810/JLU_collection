//
//  portFactoryLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portFactoryLayer__
#define __kancolle_alpha__portFactoryLayer__

#include "cocos2d.h"
using namespace cocos2d;
class PortFactoryLayer : public Layer
{
public:
    PortFactoryLayer(Node *parent);
    
    
    
private:
    Node * parent;
    
private:
    void initLayer();
    void callBack(Ref* pSender);
    
};


#endif /* defined(__kancolle_alpha__portFactoryLayer__) */
