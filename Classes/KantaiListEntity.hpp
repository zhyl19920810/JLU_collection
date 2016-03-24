//
//  KantaiListEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef KantaiListEntity_hpp
#define KantaiListEntity_hpp


#include "OrganizeContainer.hpp"
#include "ListEntity.hpp"
#include "LayerCover.hpp"

class KantaiListEntity:public ListEntity
{
public:
    void removeCallback(Ref* ref);
    void showSelect(Kantai* kantai);
    void hideSelect(Ref* pSender);
    CREATE_FUNC(KantaiListEntity);
    bool init();
    OrganSelectEntity* organSelectEntity;

private:

};











#endif /* KantaiListEntity_hpp */
