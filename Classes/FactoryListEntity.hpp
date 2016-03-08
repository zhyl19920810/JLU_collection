//
//  FactoryListEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/6/16.
//
//

#ifndef FactoryListEntity_hpp
#define FactoryListEntity_hpp

#include "ListEntity.hpp"
#include "KantaiDestroyEntity.hpp"




class FactoryListEntity:public ListEntity
{
public:
    void removeCallback(Ref* ref);
    void showSelect(Kantai* kantai);
    void hideSelect(Ref* pSender);
    CREATE_FUNC(FactoryListEntity);
    bool init();
    
    void destoryKantai(Kantai* kantai);
    KantaiDestroyEntity* kantaiDestroyEntity;
private:
};






#endif /* FactoryListEntity_hpp */
