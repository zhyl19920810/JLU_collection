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
#include "FactoryContainer.hpp"
#include "arsenal.hpp"
#include "Player.h"

using namespace cocos2d;


class PortFactoryLayer : public Layer
{
public:
    PortFactoryLayer();
    CREATE_FUNC(PortFactoryLayer);
    
    bool init();
    
private:
    
private:
    //bg
    void initLayer();
    Sprite* bgimg;
    Sprite* arsenalBg;
    Menu* menu;
    
    
    //build
public:
    FactoryContainer* getContainer(int position);
private:
    void initContainer();
    std::vector<FactoryContainer*> container;
    void buildCallback(Ref* pSender);
    
    void callBack(Ref* pSender);
    
};


#endif /* defined(__kancolle_alpha__portFactoryLayer__) */
