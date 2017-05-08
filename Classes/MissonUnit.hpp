//
//  MissonUnit.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef MissonUnit_hpp
#define MissonUnit_hpp

#include "SystemHeader.h"


NS_KCL_BEGIN

USING_NS_CC;

class MissionContainer :public Node
{
public:
    CREATE_FUNC(MissionContainer);
    
    virtual bool init() override;
    MissionContainer();
    void updateContainer(int areaId, int index);
private:
    Sprite* image;
    int     m_iAreaId;
    int     m_iIndex;
    //Sprite* passedIcon;
    bool locked;
    
};


NS_KCL_END

#endif /* MissonUnit_hpp */
