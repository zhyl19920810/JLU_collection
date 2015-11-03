//
//  BattleModel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#include "BattleModel.h"


BattleModel::BattleModel(Fleet* allies,Fleet* enemy,FormationType alliesFormation,FormationType enemyFormation)
{
    for (int i=0; i<allies->size(); ++i)
    {
        this->allies.push_back(allies->ship[i]);
    }
    
    for (int i=0; i<enemy->size(); ++i)
    {
        this->enemy.push_back(enemy->ship[i]);
    }
    
    tword=FanHang;
    
    this->alliesFormation=alliesFormation;
    this->enemyFormation=enemyFormation;
    
}


void BattleModel::insertToRangeVector(Shooting_Range range, int i)
{
    switch (range) {
        case Shooting_Range::range_exlong:
        {
            if (i>10)
            {
                exlongIndex.insert(exlongIndex.begin(), i);
            }
            else
            {
                exlongIndex.insert(exlongIndex.end(), i);
            }
            break;
        }
        case Shooting_Range::range_long:
        {
            if (i>10)
            {
                longIndex.insert(longIndex.begin(), i);
            }
            else
            {
                longIndex.insert(longIndex.end(), i);
            }
            break;
        }
        case Shooting_Range::range_mid:
            if (i>10)
                midIndex.insert(midIndex.begin(), i);
            else
                midIndex.insert(midIndex.end(), i);
            break;
        case Shooting_Range::range_short:
            if (i>10)
                shortIndex.insert(shortIndex.begin(), i);
            else
                shortIndex.insert(shortIndex.end(), i);
            break;
            
        default:
            break;
    }
}










