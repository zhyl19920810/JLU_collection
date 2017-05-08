//
//  BattleAvatarCard.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattleAvatarCard_hpp
#define BattleAvatarCard_hpp

#include "SystemHeader.h"


NS_KCL_BEGIN

USING_NS_CC;

class BattleAvatarCard :public Node{
public:
    static BattleAvatarCard* create(int kantaiNumber,bool isEnemy);
    virtual bool init(int kantaiNumber,bool isEnemy);
    void SetBrokenMark(BrokenType brokenType);
    void UpdateCard(BrokenType type);
    void UpdateCard(int kantaiNumber,BrokenType type);
private:
    int       m_iKantaiNumber;
    bool      m_bIsEnemy;
    Sprite*   m_pMainImage;
    Sprite*   m_pShader;
    Sprite*   m_pBrokenMark;
};


NS_KCL_END

#endif /* BattleAvatarCard_hpp */
