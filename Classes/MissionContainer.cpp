//
//  MissionContainer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#include "MissionContainer.h"



MissionContainer::MissionContainer(int areaId,int index)
{
    image=Sprite::create();
    addChild(image);
    updateContainer(areaId, index);
}

void MissionContainer::updateContainer(int areaId, int index)
{
    if (areaId == 1)
    {
        if (index == 0)
            image->setTexture("interface/SallyMain/SallyMain_384.png");
        else if (index == 1)
            image->setTexture("interface/SallyMain/SallyMain_386.png");
        else if (index == 2)
            image->setTexture("interface/SallyMain/SallyMain_388.png");
        else if (index == 3)
            image->setTexture("interface/SallyMain/SallyMain_390.png");
    }
    else if (areaId == 2)
    {
        if (index == 0)
            image->setTexture("interface/SallyMain/SallyMain_397.png");
        else if (index == 1)
            image->setTexture("interface/SallyMain/SallyMain_399.png");
        else if (index == 2)
            image->setTexture("interface/SallyMain/SallyMain_401.png");
        else if (index == 3)
            image->setTexture("interface/SallyMain/SallyMain_403.png");
    }
    else if (areaId == 3)
    {
        if (index == 0)
            image->setTexture("interface/SallyMain/SallyMain_407.png");
        else if (index == 1)
            image->setTexture("interface/SallyMain/SallyMain_409.png");
        else if (index == 2)
            image->setTexture("interface/SallyMain/SallyMain_411.png");
        else if (index == 3)
            image->setTexture("interface/SallyMain/SallyMain_413.png");
    }
    else if (areaId == 4)
    {
        if (index == 0)
            image->setTexture("interface/SallyMain/SallyMain_417.png");
        else if (index == 1)
            image->setTexture("interface/SallyMain/SallyMain_419.png");
        else if (index == 2)
            image->setTexture("interface/SallyMain/SallyMain_421.png");
        else if (index == 3)
            image->setTexture("interface/SallyMain/SallyMain_423.png");
    }
    else if (areaId == 5)
    {
        if (index == 0)
            image->setTexture("interface/SallyMain/SallyMain_425.png");
        else if (index == 1)
            image->setTexture("interface/SallyMain/SallyMain_427.png");
        else if (index == 2)
            image->setTexture("interface/SallyMain/SallyMain_429.png");
        else if (index == 3)
            image->setTexture("interface/SallyMain/SallyMain_431.png");
    }
    else if (areaId == 6)
    {
        if (index == 0)
            image->setTexture("interface/SallyMain/SallyMain_435.png");
        else if (index == 1)
            image->setTexture("interface/SallyMain/SallyMain_437.png");
        else if (index == 2)
            image->setTexture("interface/SallyMain/SallyMain_382.png");
        else if (index == 3)
            image->setTexture("interface/SallyMain/SallyMain_382.png");
    }

    
    
    
    
}
