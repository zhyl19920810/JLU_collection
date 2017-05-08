//
//  FlagShip.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#ifndef FlagShip_hpp
#define FlagShip_hpp

#include "SystemHeader.h"


NS_KCL_BEGIN

USING_NS_CC;


class FlagShip:public Node
{
public:
    CREATE_FUNC(FlagShip);
    
    bool init();
    
private:
    Sprite* m_pShipImage;
};



NS_KCL_END

#endif /* FlagShip_hpp */
