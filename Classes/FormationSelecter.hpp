//
//  FormationSelecter.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#ifndef FormationSelecter_hpp
#define FormationSelecter_hpp

#include "SystemHeader.h"
#include "Formation.hpp"
#include <vector>


class Formation;


NS_KCL_BEGIN

USING_NS_CC;

class BattleFleet;


class FormationSelecter:public Node
{
public:
    CREATE_FUNC(FormationSelecter);
    virtual bool init() override;
    
    void ShowSelecter(int kantaiSize);
    void HideSelecter();
    
private:
    std::vector<Formation*>  m_vFormation;
    int                      m_iKantaiSize;
};


NS_KCL_END


#endif /* FormationSelecter_hpp */
