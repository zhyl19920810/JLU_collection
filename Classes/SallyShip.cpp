//
//  SallyShip.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#include "SallyShip.hpp"

NS_KCL_BEGIN


bool SallyShip::init()
{
    m_pShipImage = Sprite::create("SallyMain/image 1023.png");
    addChild(m_pShipImage);
    
    return true;
}



NS_KCL_END
