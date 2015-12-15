//
//  BattleModel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#include "BattleModel.h"


#define DEFAULT_HIT_RATE 0.95
#define MAX_SHIPS_PER_FLEET 6

BattleModel::BattleModel(Fleet* allies,Fleet* enemy,FormationType alliesFormation,FormationType enemyFormation)
{
    for (int i=0; i<allies->size(); ++i)
    {
        this->allies.push_back(allies->ship[i]);
    }
    log("%d",enemy->size());
    for (int i=0; i<enemy->size(); ++i)
    {
        this->enemy.push_back(enemy->ship[i]);
    }
    
    tword=FanHang;
    
    this->alliesFormation=alliesFormation;
    this->enemyFormation=enemyFormation;
    tword=FanHang;
    
}


void BattleModel::resetFireBattle()
{
    exlongIndex.clear();
    longIndex.clear();
    midIndex.clear();
    shortIndex.clear();
    
    for (int i=0; i<MAX_SHIPS_PER_FLEET; ++i)
    {
        if (i<allies.size())
        {
            insertToRangeVector(range_long, i);
        }
        if (i<enemy.size()) {
            insertToRangeVector(range_long, i+10);
        }
    }
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


void BattleModel::getFireDamage(bool alliesAttack, int alliesIndex, int enemyIndex, bool &doubleHit, bool &specialAttack, bool &ci,int &damage, bool &critical,bool &miss)
{
    Attack_Type attackType=dayBattle;
    Kantai* attacker;
    Kantai* attacked;
    
    FormationType formation;
    if (alliesAttack)
    {
        attacker=allies[alliesIndex];
        attacked=enemy[enemyIndex];
        formation=alliesFormation;
    }
    else
    {
        attacked=allies[alliesIndex];
        attacker=enemy[enemyIndex];
        formation=enemyFormation;
    }
    
    bool antiSubmarine=false;
    
    if (attacked->getkantaiType()==KantaiType::Submarine||attacked->getkantaiType()==KantaiType::Diving_Carrier)
    {
        antiSubmarine=true;
        attackType=Attack_Type::antiSubmarine;
    }
    
    float hit=CCRANDOM_0_1();
    miss=false;
    
    if (hit-0.2+(float)attacked->getdodge()/100>DEFAULT_HIT_RATE)
    {
        miss=true;
        return;
    }
    
    float basicAttack=0;
    
    int type=attacker->getkantaiType();
    
    
    if (type==KantaiType::Carrier||type==KantaiType::Light_Carrier||type==KantaiType::Armor_Carrier)
    {
        basicAttack=(attacker->getfirePower()+attacker->gettorpedo())*1.5+55;
    }
    else
    {
        basicAttack=attacker->getfirePower()+5;
    }
    float preCorrection=1;
    
    
    
    
    preCorrection=preCorrection*formationCorrection(formation, antiSubmarine);
    preCorrection=preCorrection*TWordCorrection(tword);
    preCorrection=preCorrection*brokenCorrection(attacker->getBrokenType());
    
    float postCorrection=1;
    
    float randomCritical=CCRANDOM_0_1();
    critical=false;
    if (randomCritical<0.15)
    {
        critical=true;
        postCorrection=1.5;
    }
    
    doubleHit=false;
    
    specialAttack=false;
    
    ci=false;
    
    
    damage=getDamage(attackType, basicAttack, attacked->getarmor(), preCorrection, postCorrection, 1);
    
    if (!alliesAttack&&damage>=attacked->getcurrHp())
    {
        float random=CCRANDOM_0_1()*0.3+0.5;
        damage=attacked->getcurrHp()*random;
    }
    
    if (!miss&&damage<0)
    {
        float random=CCRANDOM_0_1()*0.08+0.06;
        damage=random*attacked->getcurrHp();
    }
    
    if (0<damage<1)
    {
        miss=true;
    }
    if (damage>=40)
    {
        critical=true;
    }
    if (damage<13)
    {
        critical=false;
    }
    
}




int BattleModel::getDamage(Attack_Type attackType, float basicAttack, int enemyArmour, float preCorrection, float postCorrection, float AmmoCorrection)
{
    float damage=basicAttack*preCorrection;
    damage=getDamageAfterMaxCorrection(damage, attackType);
    damage=damage*postCorrection;
    float random=CCRANDOM_0_1()*(2/3)+2/3;
    
    damage=damage-random*enemyArmour;
    damage=damage*AmmoCorrection;
    
    return damage;
}


float BattleModel::getDamageAfterMaxCorrection(float damage, Attack_Type type)
{
    float maxDamage=150;
    switch (type)
    {
        case nightBattle:
            maxDamage=300;
            break;
        case antiSubmarine:
            maxDamage=100;
            break;
        default:
            break;
    }
    
    if (damage>maxDamage)
    {
        damage=sqrt(damage-maxDamage)+maxDamage;
    }
    
    return damage;
    
}

bool BattleModel::getNextIndexToFire(bool &allies, int &index)
{
    std::vector<int> *vec=&exlongIndex;
    for (int i=0; i<4; ++i)
    {
        if (!vec->empty())
        {
            if (allies)
            {
                index=vec->front();
                vec->erase(vec->begin());
            }
            else
            {
                index=vec->back();
                vec->pop_back();
            }
            
            if (index<10)
            {
                allies=true;
            }
            else
            {
                allies=false;
                index=index-10;
            }
            
            return true;
        }
        
        if (i==0)
        {
            vec=&longIndex;
        }
        if (i==1)
        {
            vec=&midIndex;
        }
        if (i==2)
        {
            vec=&shortIndex;
        }
    }
    return false;
    
}


int BattleModel::getTargetIndex(bool alliesAttack)
{
    std::vector<int> aliveTargets;
    std::vector<Kantai*> *targets;
    
    if (alliesAttack)
    {
        targets=&enemy;
    }
    else
    {
        targets=&allies;
    }
    
    for (int i=0; i<targets->size(); ++i)
    {
        if (targets->at(i)->getcurrHp()!=0)
        {
            aliveTargets.push_back(i);
        }
    }
    
    if (aliveTargets.size()==0)
    {
        return -1;
    }
    float random=CCRANDOM_0_1()*(float)(aliveTargets.size());
    
    if (random==aliveTargets.size())
    {
        random-=1;
    }
    
    return aliveTargets[(int)(random)];
}


float BattleModel::TWordCorrection(T_Word t)
{
    switch (t)
    {
        case T_Word::TongHang:
            return 1;
            break;
        case T_Word::FanHang:
            return 0.8;
            break;
        case T_Word::TYouLi:
            return 1.2;
            break;
        case T_Word::TBuLi:
            return 0.6;
            break;
        default:
            break;
    }
}

float BattleModel::formationCorrection(FormationType type, bool antiSubmarine)
{
    switch (type)
    {
        case DanZong:
            if (antiSubmarine)
                return 0.45;
            return 1;
            break;
        case FuZong:
            if (antiSubmarine)
                return 0.6;
            return 0.8;
            break;
        case LunXing:
            if (antiSubmarine)
                return 0.9;
            return 0.7;
            break;
        case TiXing:
            if (antiSubmarine)
                return 0.75;
            return 0.6;
            break;
        case DanHeng:
            if (antiSubmarine)
                return 1;
            return 0.6;
            break;
        default:
            break;
    }
}

float BattleModel::brokenCorrection(BrokenType type)
{
    switch (type)
    {
        case BrokenType::normal:
            return 1;
            break;
        case BrokenType::tiny:
            return 1;
            break;
        case BrokenType::mid:
            return 0.7;
            break;
        case BrokenType::large:
            return 0.4;
            break;
        case BrokenType::drown:
            return 0;
            break;
        default:
            break;
    }
}
