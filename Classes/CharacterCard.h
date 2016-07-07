//
//  CharacterCard.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/25/15.
//
//

#ifndef __kancolle_beta__CharacterCard__
#define __kancolle_beta__CharacterCard__

#include "cocos2d.h"
#include "kantai.h"

USING_NS_CC;

NS_KCL_BEGIN

class CharacterCard:public Node
{
public:
    CharacterCard();
    
    CharacterCard(Kantai* kantai);
    
    CharacterCard(int kantaiNumber);
    
    CharacterCard(bool isEnemy,int kantaiNumber);
    
    void setBrokenMark(BrokenType brokenType);
    
    void updateCharacter(int kantaiNumber,BrokenType type);
    
    
private:
    void initCard();
    
    bool isEnemy;
    
    Sprite* mainImage;
    
    Sprite* shader;
    
    Sprite* brokenMark;
    
};

NS_KCL_END

#endif /* defined(__kancolle_beta__CharacterCard__) */
