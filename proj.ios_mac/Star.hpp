//
//  Star.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef Star_hpp
#define Star_hpp

#include "cocos2d.h"
#define MAX_STARS_NUMBER 5
using namespace cocos2d;

class Stars:public Node{
public:
    Stars();
    void setNumber(int number);
private:
    std::vector<Sprite*> stars;
};


#endif /* Star_hpp */
