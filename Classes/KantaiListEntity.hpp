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

NS_KCL_BEGIN

class KantaiListEntity:public ListEntity
{
public:
    static KantaiListEntity* create(Vec2 vec);
    void removeCallback(Ref* ref);
    void showSelect(Kantai* kantai);
    void hideSelect(Ref* pSender);
    bool init(Vec2 vec);
    
    
private:

};

NS_KCL_END









#endif /* KantaiListEntity_hpp */
