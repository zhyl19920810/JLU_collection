//
//  SallyShip.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef SallyShip_hpp
#define SallyShip_hpp


#include "SystemHeader.h"

NS_KCL_BEGIN


USING_NS_CC;

class SallyShip:public Node
{
public:
    CREATE_FUNC(SallyShip);
    
    virtual bool init() override;
    
    
private:
    Sprite*   m_pShipImage;
};





NS_KCL_END




#endif /* SallyShip_hpp */
