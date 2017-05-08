//
//  FlagShip.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#include "FlagShip.hpp"
#include "Player.h"

NS_KCL_BEGIN

bool FlagShip::init()
{
    std::string resource=std::to_string(sPlayer.getFlagShip()->getKantaiNumber());
    m_pShipImage=Sprite::create("kantai/" + resource + "/image 17.png");
    addChild(m_pShipImage);
    
    return true;
}



NS_KCL_END
