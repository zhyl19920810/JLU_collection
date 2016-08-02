//
//  MathUtil.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/2/16.
//
//

#include "MathUtil.hpp"
#include<math.h>
#include <ctime>
#include <cstdint>


TINA_NS_BEGIN



static bool __randomSrand = false;
int MathUtil::random(int min, int max)
{
    if (!__randomSrand)
    {
        srand(time(0));
        __randomSrand = true;
    }
    if (min > max)
        std::swap(max, min);
    
    return std::rand() % (max - min + 1) + min;
}



TINA_NS_END