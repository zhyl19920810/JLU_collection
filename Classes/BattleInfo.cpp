//
//  BattleModel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#include "BattleInfo.hpp"

NS_KCL_BEGIN


#define DEFAULT_HIT_RATE 0.95


BattleInfo* BattleInfo::create(BattleFleet* kantaiFleet,BattleFleet* enemyFleet,FormationType kantaiFormation,FormationType enemyFormation)
{
    BattleInfo* pRet=new BattleInfo;
    if (pRet&&pRet->init(kantaiFleet,enemyFleet,kantaiFormation,enemyFormation))
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}


BattleInfo::~BattleInfo()
{
    release();
}



bool BattleInfo::init(BattleFleet* kantaiFleet,BattleFleet* enemyFleet,FormationType kantaiFormation,FormationType enemyFormation)
{
    bool bRet=false;
    
    do
    {
        m_pKantaiFleet=kantaiFleet;
        m_pEnemyFleet=enemyFleet;
        m_KantaiFormationType=kantaiFormation;
        m_EnemyFormationType=enemyFormation;
        m_tWord=TongHang;
        m_AirControl=FULL;
        
        bRet=true;
    }while(0);
    
    return bRet;
}

BattleInfo* BattleInfo::create()
{
    BattleInfo* pRet=new BattleInfo;
    if (pRet&&pRet->init())
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}


bool BattleInfo::init()
{
    bool bRet=false;
    
    do
    {
        m_pKantaiFleet=NULL;
        m_pEnemyFleet=NULL;
        m_KantaiFormationType=DanZong;
        m_EnemyFormationType=DanZong;
        m_tWord=TongHang;
        m_AirControl=FULL;
        
        bRet=true;
    }while(0);
    
    return bRet;
}





float BattleInfo::GetDamageAfterMaxCorrection(float damage, AttackType type)
{
    float maxDamage=150;
    switch (type)
    {
        case NIGHT_BATTLE:
            maxDamage = 300;
            break;
        case ANTISUBMARINE:
            maxDamage = 100;
            break;
        default:
            break;
    }
    if (damage > maxDamage)
    {
        damage = sqrtf(damage - maxDamage) + maxDamage;
    }
    return damage;
}


float BattleInfo::FormationCorrection(FormationType type, bool antiSubmarine)
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


float BattleInfo::TWordCorrection(T_Word t)
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


float BattleInfo::BrokenCorrection(BrokenType type)
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
float BattleInfo::AmmoCorrection()
{
    return 1;
}

bool BattleInfo::DouldeHitTriggered(BattleCharacterInfo* acttacker)
{
    return false;
}
bool BattleInfo::SpecialAttackTriggered(BattleCharacterInfo* acttacker)
{
    return false;
}
bool BattleInfo::CutinTriggered(BattleCharacterInfo* acttacker)
{
    return false;
}


void BattleInfo::InsertToRangeVector(Shooting_Range range, int i)
{
    switch (range)
    {
        case Shooting_Range::range_exlong:
            if (i>10)
                m_vExlongIndex.insert(m_vExlongIndex.begin(), i);
            else
                m_vExlongIndex.insert(m_vExlongIndex.end(), i);
            break;
        case Shooting_Range::range_long:
            if (i>10)
                m_vLongIndex.insert(m_vLongIndex.begin(), i);
            else
                m_vLongIndex.insert(m_vLongIndex.end(), i);
            break;
        case Shooting_Range::range_mid:
            if (i>10)
                m_vMidIndex.insert(m_vMidIndex.begin(), i);
            else
                m_vMidIndex.insert(m_vMidIndex.end(), i);
            break;
        case Shooting_Range::range_short:
            if (i>10)
                m_vShortIndex.insert(m_vShortIndex.begin(), i);
            else
                m_vShortIndex.insert(m_vShortIndex.end(), i);
            break;
        default:
            break;
    }
}
void BattleInfo::ResetFireBattle(){
    m_vExlongIndex.clear();
    m_vLongIndex.clear();
    m_vMidIndex.clear();
    m_vShortIndex.clear();
    
    
    for (int i=0;i<MAX_SHIPS_PER_FLEET;i++)
    {
        if (m_pKantaiFleet->m_vBattleShip[i])
        {
            InsertToRangeVector(m_pKantaiFleet->m_vBattleShip[i]->getRange(), i);
        }
        if (m_pEnemyFleet->m_vBattleShip[i])
        {
            InsertToRangeVector(m_pEnemyFleet->m_vBattleShip[i]->getRange(), 10 + i);
        }
    }
    
}


int BattleInfo::GetDamage(AttackType attacktype,float basicAttack, int enemyArmour, float preCorrection, float postCorrection, float AmmoCorrection)
{
    float damage = basicAttack* preCorrection;
    damage = GetDamageAfterMaxCorrection(damage,attacktype);
    damage = damage*postCorrection;
    float random = CCRANDOM_0_1()*(2 / 3) + 2 / 3; //   2/3~4/3
    damage = damage - random*enemyArmour;
    damage = damage*AmmoCorrection;

    return damage;
}

int BattleInfo::GetTargetIndex(bool alliesAttack)
{
    std::vector<int> aliveTargets;
    std::vector<BattleCharacterInfo*> *targets;
    if (alliesAttack)
        targets = &(m_pEnemyFleet->m_vBattleShip);
    else
        targets = &(m_pKantaiFleet->m_vBattleShip);

    for (int i = 0; i < targets->size(); i++)
    {
        if ((*targets)[i]&&((*targets)[i])->getCurrHp()!=0)
            aliveTargets.push_back(i);
        //if (targets->at(i)->currentHP != 0)
    }
    if (aliveTargets.size() == 0)
        return -1;
    float random = CCRANDOM_0_1()*(float)(aliveTargets.size());
    if (random == aliveTargets.size())
        random -= 1;
    return aliveTargets[(int)random];

}

bool BattleInfo::GetNextIndexToFire(bool &allies, int &index)
{
    std::vector<int> * vec = &m_vExlongIndex;
    for (int i = 0; i < 4; i++){
        if (!vec->empty())
        {
            if (allies)
            {
                index = vec->front();
                vec->erase(vec->begin());
            }

            else
            {
                index = vec->back();
                vec->pop_back();
            }

            if (index < 10)
                allies = true;
            else
            {
                allies = false;
                index = index - 10;
            }

            return true;
        }
        if (i == 0)
            vec = &m_vLongIndex;
        if (i == 1)
            vec = &m_vMidIndex;
        if (i == 2)
            vec = &m_vShortIndex;
    }


    return false;
}



void BattleInfo::GetFireDamage(bool alliesAttack, int alliesIndex, int enemyIndex, bool &doubleHit, bool &specialAttack, bool &ci,int &damage, bool &critical,bool &miss)
{
    AttackType attackType = AttackType::DAY_BATTLE;
    BattleCharacterInfo *attacker;
    BattleCharacterInfo *attacked;
    FormationType formation;
    if (alliesAttack)
    {
        attacker = m_pKantaiFleet->m_vBattleShip[alliesIndex];
        attacked = m_pEnemyFleet->m_vBattleShip[enemyIndex];
        formation = m_KantaiFormationType;
    }
    else
    {
        attacked = m_pKantaiFleet->m_vBattleShip[alliesIndex];
        attacker = m_pEnemyFleet->m_vBattleShip[enemyIndex];
        formation = m_EnemyFormationType;
    }

    bool antiSubmarine = false;
    if (attacked->getKantaiType()==KantaiType::Submarine||
        attacked->getKantaiType()==KantaiType::Diving_Carrier||
        attacked->getKantaiType()==KantaiType::Diving_Mothership)
    {
        antiSubmarine = true;
        attackType = AttackType::ANTISUBMARINE;
    }


    float hit = CCRANDOM_0_1();
    miss = false;
    if (hit - (float)attacker->getHitRate()/100 + (float)attacked->getDodge()/100>DEFAULT_HIT_RATE)
    {
        miss = true;
        return;
    }


    float basicAttack=0;
    if (attacker->getKantaiType()==KantaiType::Carrier||
        attacker->getKantaiType()==KantaiType::Light_Carrier||
        attacker->getKantaiType()==KantaiType::Armor_Carrier||
        attacker->getKantaiType()==KantaiType::Diving_Carrier||
        attacker->getKantaiType()==KantaiType::Battle_Carrier||
        attacker->getKantaiType()==KantaiType::Seaplane_Carrier)
    {
        basicAttack = (attacker->getFirePower() + attacker->getTorpedo())*1.5 + attacker->getBomb() * 2 + 55; //
    }
    else
    {
        basicAttack = attacker->getFirePower() + 5;
    }
    float preCorrection = 1;
    preCorrection = preCorrection*FormationCorrection(formation, antiSubmarine);
    preCorrection = preCorrection*TWordCorrection(m_tWord);
    preCorrection = preCorrection*BrokenCorrection(attacker->getBrokenType());

    float postCorrection = 1;
    //±©ª˜
    float randomCritical = CCRANDOM_0_1();
    critical = false;
    if (randomCritical < 0.15)
    {
        critical = true;
        postCorrection = 1.5;
    }
    doubleHit = DouldeHitTriggered(attacker);
    specialAttack = SpecialAttackTriggered(attacker);
    ci = CutinTriggered(attacker);
    if (doubleHit)
    { }
    if (specialAttack)
    { }
    if (ci)
    {	}



    damage = GetDamage(attackType, basicAttack, attacked->getArmor(), preCorrection, postCorrection, AmmoCorrection());

    //ª˜≥¡±£ª§
    if (!alliesAttack && damage >= attacked->getCurrHp())
    {
        float random = CCRANDOM_0_1()*(0.3) + 0.5; //0.5~0.8
        damage = attacked->getCurrHp()*random;
    }

    //≤¡…À
    if (!miss && damage < 0)
    {
        float random = CCRANDOM_0_1()*(0.08) + 0.06; //   0.06~0.14
        damage = random*attacked->getCurrHp();
    }

    //æ¿’˝œ‘ æ
    if (0 < damage < 1)
        miss = true;
    if (damage >= 40)
        critical = true;
    if (damage < 13)
        critical = false;

}







NS_KCL_END



//
//
//#define DEFAULT_HIT_RATE 0.95
//BattleModel::BattleModel(Fleet* allies, Fleet* enemy, FormationType alliesFormation, FormationType enemyFormation)
//{
//    
//    for (int i = 0; i < allies->size(); i++)
//        this->allies.push_back(allies->getShip(i));
//    for (int i = 0; i < enemy->size(); i++)
//        this->enemy.push_back(enemy->getShip(i));
//    
//    //CharacterInfo *einfo = XMLParser::getInstance()->loadCharacterInfo("BeiFangQiJi");
//    //this->enemy.push_back(einfo);
//    //CharacterInfo *einfo2 = XMLParser::getInstance()->loadCharacterInfo("RU");
//    //this->enemy.push_back(einfo2);
//    //CharacterInfo *einfo3 = XMLParser::getInstance()->loadCharacterInfo("LI");
//    //this->enemy.push_back(einfo3);
//    //CharacterInfo *einfo4 = XMLParser::getInstance()->loadCharacterInfo("HO");
//    //this->enemy.push_back(einfo4);
//    //CharacterInfo *einfo5 = XMLParser::getInstance()->loadCharacterInfo("HO");
//    //this->enemy.push_back(einfo5);
//    //CharacterInfo *einfo6 = XMLParser::getInstance()->loadCharacterInfo("DO");
//    //this->enemy.push_back(einfo6);
//    
//    this->alliesFormation = alliesFormation;
//    this->enemyFormation = enemyFormation;
//    tword = FanHang;
//    resetFireBattle();
//    
//}
//BattleModel::BattleModel()
//{
//    
//    CharacterInfo *info = XMLParser::getInstance()->loadCharacterInfo("JiaHeGai");
//    this->allies.push_back(info);
//    CharacterInfo *info2 = XMLParser::getInstance()->loadCharacterInfo("NaKe");
//    this->allies.push_back(info2);
//    CharacterInfo *info3 = XMLParser::getInstance()->loadCharacterInfo("Yi19");
//    this->allies.push_back(info3);
//    CharacterInfo *info4 = XMLParser::getInstance()->loadCharacterInfo("XiLiGai2");
//    this->allies.push_back(info4);
//    CharacterInfo *info5 = XMLParser::getInstance()->loadCharacterInfo("AiDang");
//    this->allies.push_back(info5);
//    CharacterInfo *info6 = XMLParser::getInstance()->loadCharacterInfo("ChuiXue");
//    this->allies.push_back(info6);
//    
//    CharacterInfo *einfo = XMLParser::getInstance()->loadCharacterInfo("BeiFangQiJi");
//    this->enemy.push_back(einfo);
//    CharacterInfo *einfo2 = XMLParser::getInstance()->loadCharacterInfo("RU");
//    this->enemy.push_back(einfo2);
//    CharacterInfo *einfo3 = XMLParser::getInstance()->loadCharacterInfo("RU");
//    this->enemy.push_back(einfo3);
//    CharacterInfo *einfo4 = XMLParser::getInstance()->loadCharacterInfo("RU");
//    this->enemy.push_back(einfo4);
//    CharacterInfo *einfo5 = XMLParser::getInstance()->loadCharacterInfo("RU");
//    this->enemy.push_back(einfo5);
//    CharacterInfo *einfo6 = XMLParser::getInstance()->loadCharacterInfo("RU");
//    this->enemy.push_back(einfo6);
//    
//    alliesFormation = DanZong;
//    enemyFormation = LunXing;
//    tword = FanHang;
//    resetFireBattle();
//}
////void BattleModel::insertToRangeVector(Shooting_Range range, int i)
////{
////    switch (range)
////    {
////        case Shooting_Range::range_exlong:
////            if (i>10)
////                exlongIndex.insert(exlongIndex.begin(), i);
////            else
////                exlongIndex.insert(exlongIndex.end(), i);
////            break;
////        case Shooting_Range::range_long:
////            if (i>10)
////                longIndex.insert(longIndex.begin(), i);
////            else
////                longIndex.insert(longIndex.end(), i);
////            break;
////        case Shooting_Range::range_mid:
////            if (i>10)
////                midIndex.insert(midIndex.begin(), i);
////            else
////                midIndex.insert(midIndex.end(), i);
////            break;
////        case Shooting_Range::range_short:
////            if (i>10)
////                shortIndex.insert(shortIndex.begin(), i);
////            else
////                shortIndex.insert(shortIndex.end(), i);
////            break;
////        default:
////            break;
////    }
////}
////void BattleModel::resetFireBattle(){
////    exlongIndex.clear();
////    longIndex.clear();
////    midIndex.clear();
////    shortIndex.clear();
////    
////    
////    for (int i = 0; i < MAX_SHIPS_PER_FLEET; i++)
////    {
////        if (i < allies.size())
////        {
////            insertToRangeVector(allies[i]->range, i);
////        }
////        if (i < enemy.size())
////        {
////            insertToRangeVector(enemy[i]->range, 10 + i);
////        }
////    }
////    
////}
//bool BattleModel::getNextIndexToFire(bool &allies, int &index)
//{
//    std::vector<int> * vec = &exlongIndex;
//    for (int i = 0; i < 4; i++){
//        if (!vec->empty())
//        {
//            if (allies)
//            {
//                index = vec->front();
//                vec->erase(vec->begin());
//            }
//            
//            else
//            {
//                index = vec->back();
//                vec->pop_back();
//            }
//            
//            if (index < 10)
//                allies = true;
//            else
//            {
//                allies = false;
//                index = index - 10;
//            }
//            
//            return true;
//        }
//        if (i == 0)
//            vec = &longIndex;
//        if (i == 1)
//            vec = &midIndex;
//        if (i == 2)
//            vec = &shortIndex;
//    }
//    
//    
//    return false;
//}
//int BattleModel::getTargetIndex(bool alliesAttack)
//{
//    std::vector<int> aliveTargets;
//    std::vector<CharacterInfo*> *targets;
//    if (alliesAttack)
//        targets = &enemy;
//    else
//        targets = &allies;
//    
//    for (int i = 0; i < targets->size(); i++)
//    {
//        if (targets->at(i)->currentHP != 0)
//            aliveTargets.push_back(i);
//    }
//    if (aliveTargets.size() == 0)
//        return -1;
//    float random = CCRANDOM_0_1()*(float)(aliveTargets.size());
//    if (random == aliveTargets.size())
//        random -= 1;
//    return aliveTargets[(int)random];
//    
//}
//void BattleModel::getFireDamage(bool alliesAttack, int alliesIndex, int enemyIndex, bool &doubleHit, bool &specialAttack, bool &ci,int &damage, bool &critical,bool &miss)
//{
//    Attack_Type attackType = dayBattle;
//    CharacterInfo *attacker;
//    CharacterInfo *attacked;
//    FormationType formation;
//    if (alliesAttack){
//        attacker = allies[alliesIndex];
//        attacked = enemy[enemyIndex];
//        formation = alliesFormation;
//    }
//    else
//    {
//        attacked = allies[alliesIndex];
//        attacker = enemy[enemyIndex];
//        formation = enemyFormation;
//    }
//    
//    bool antiSubmarine = false;
//    if (attacked->type == SS || attacked->type == SSV)
//    {
//        antiSubmarine = true;
//        attackType = Attack_Type::antiSubmarine;
//    }
//    
//    //√¸÷–
//    float hit = CCRANDOM_0_1();
//    miss = false;
//    if (hit - (float)attacker->hitRate/100 + (float)attacked->agility/100>DEFAULT_HIT_RATE)
//    {
//        miss = true;
//        return;
//    }
//    
//    
//    float basicAttack=0;
//    if (attacker->type == CV || attacker->type == CVL || attacker->type==CVA) //ª˘±æπ•ª˜¡¶=ª¡¶*1.5+¿◊◊∞*1.5+±¨◊∞*2+55
//    {
//        
//        basicAttack = (attacker->firePower + attacker->torpedo)*1.5 + attacker->bomb * 2 + 55; //
//    }
//    else //ª˘±æπ•ª˜¡¶=ª¡¶+5
//    {
//        basicAttack = attacker->firePower + 5;
//    }
//    float preCorrection = 1;
//    preCorrection = preCorrection*formationCorrection(formation, antiSubmarine);
//    preCorrection = preCorrection*TWordCorrection(tword);
//    preCorrection = preCorrection*brokenCorrection(attacker->brokenType);
//    
//    float postCorrection = 1;
//    //±©ª˜
//    float randomCritical = CCRANDOM_0_1();
//    critical = false;
//    if (randomCritical < 0.15)
//    {
//        critical = true;
//        postCorrection = 1.5;
//    }
//    doubleHit = douldeHitTriggered(attacker);
//    specialAttack = specialAttackTriggered(attacker);
//    ci = cutinTriggered(attacker);
//    if (doubleHit)
//    { }
//    if (specialAttack)
//    { }
//    if (ci)
//    {	}
//    
//    
//    
//    damage = getDamage(attackType, basicAttack, attacked->armour, preCorrection, postCorrection, ammoCorrection());
//    
//    //ª˜≥¡±£ª§
//    if (!alliesAttack && damage >= attacked->currentHP)
//    {
//        float random = CCRANDOM_0_1()*(0.3) + 0.5; //0.5~0.8
//        damage = attacked->currentHP*random;
//    }
//    
//    //≤¡…À
//    if (!miss && damage < 0)
//    {
//        float random = CCRANDOM_0_1()*(0.08) + 0.06; //   0.06~0.14
//        damage = random*attacked->currentHP;
//    }
//    
//    //æ¿’˝œ‘ æ
//    if (0 < damage < 1)
//        miss = true;
//    if (damage >= 40)
//        critical = true;
//    if (damage < 13)
//        critical = false;
//    
//    
//    
//    
//    
//}
////bool BattleModel::douldeHitTriggered(CharacterInfo *acttacker)
////{
////    return false;
////}
////bool BattleModel::specialAttackTriggered(CharacterInfo *acttacker)
////{
////    return false;
////}
////bool BattleModel::cutinTriggered(CharacterInfo *acttacker)
////{
////    return false;
////}
//int BattleModel::getDamage(Attack_Type attacktype,float basicAttack, int enemyArmour, float preCorrection, float postCorrection, float AmmoCorrection)
//{
//    float damage = basicAttack* preCorrection;
//    damage = getDamageAfterMaxCorrection(damage,attacktype);
//    damage = damage*postCorrection;
//    float random = CCRANDOM_0_1()*(2 / 3) + 2 / 3; //   2/3~4/3
//    damage = damage - random*enemyArmour;
//    damage = damage*AmmoCorrection;
//    
//    return damage;
//}
//float BattleModel::getDamageAfterMaxCorrection(float damage, Attack_Type type)
//{
//    float maxDamage=150;
//    switch (type)
//    {
//        case nightBattle:
//            maxDamage = 300;
//            break;
//        case antiSubmarine:
//            maxDamage = 100;
//            break;
//        default:
//            break;
//    }
//    if (damage > maxDamage)
//    {
//        damage = sqrtf(damage - maxDamage) + maxDamage;
//    }
//    return damage;
//}
//float BattleModel::formationCorrection(FormationType type, bool antiSubmarine)
//{
//    switch (type)
//    {
//        case DanZong:
//            if (antiSubmarine)
//                return 0.45;
//            return 1;
//            break;
//        case FuZong:
//            if (antiSubmarine)
//                return 0.6;
//            return 0.8;
//            break;
//        case LunXing:
//            if (antiSubmarine)
//                return 0.9;
//            return 0.7;
//            break;
//        case TiXing:
//            if (antiSubmarine)
//                return 0.75;
//            return 0.6;
//            break;
//        case DanHeng:
//            if (antiSubmarine)
//                return 1;
//            return 0.6;
//            break;
//        default:
//            break;
//    }
//}
//float BattleModel::TWordCorrection(T_Word t)
//{
//    switch (t)
//    {
//        case T_Word::TongHang:
//            return 1;
//            break;
//        case T_Word::FanHang:
//            return 0.8;
//            break;
//        case T_Word::TYouLi:
//            return 1.2;
//            break;
//        case T_Word::TBuLi:
//            return 0.6;
//            break;
//        default:
//            break;
//    }
//}
//float BattleModel::brokenCorrection(BrokenType type)
//{
//    switch (type)
//    {
//        case BrokenType::normal:
//            return 1;
//            break;
//        case BrokenType::tiny:
//            return 1;
//            break;
//        case BrokenType::mid:
//            return 0.7;
//            break;
//        case BrokenType::large:
//            return 0.4;
//            break;
//        case BrokenType::drown:
//            return 0;
//            break;
//        default:
//            break;
//    }
//}
//float BattleModel::ammoCorrection()
//{
//    return 1;
//}
