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


NS_KCL_BEGIN

class FactoryListEntity:public ListEntity
{
public:
    void showSelect(Kantai* kantai);
    bool init(Vec2 vec);
    
    static FactoryListEntity* create(Vec2 vec);
private:
    
};


NS_KCL_END



#endif /* FactoryListEntity_hpp */
