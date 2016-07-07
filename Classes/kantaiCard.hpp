//
//  kantaiCard.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef kantaiCard_hpp
#define kantaiCard_hpp


#include "cocos2d.h"
#include "kantai.h"
using namespace cocos2d;

NS_KCL_BEGIN


class KantaiCard :public Node{
public:
    KantaiCard();
    CREATE_FUNC(KantaiCard);
    
    bool init();
    void setBrokenMark(BrokenType brokenType);
    void updateCard(Kantai* kantai,bool isEnemy=false);
    
private:
    bool isEnemy;
    Sprite* mainImage;
    Sprite* shader;
    Sprite* brokenMark;
};

NS_KCL_END


#endif /* kantaiCard_hpp */
