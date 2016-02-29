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
    static Stars* create()
    {
        Stars* tmp=new(std::nothrow) Stars;
        if (tmp&&tmp->init())
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    bool init();
    Stars();
    void setNumber(int number);
private:
    std::vector<Sprite*> stars;
};


#endif /* Star_hpp */
