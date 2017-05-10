//
//  BattleModel.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattleModel_hpp
#define BattleModel_hpp

//#include "CharacterInfo.h"
//#include "XMLParser.h"
//#include "GameModel.h"

#include "SystemHeader.h"
#include "Fleet.h"
#include "BattleFleetInfo.hpp"
//#include "BattlePanel.hpp"


NS_KCL_BEGIN

USING_NS_CC;


//enum FormationType{
//    DanZong = 1,
//    FuZong = 2,
//    LunXing = 3,
//    TiXing = 4,
//    DanHeng = 5
//};


enum AttackType
{
    DAY_BATTLE,
    NIGHT_BATTLE,
    ANTISUBMARINE,
};



enum T_Word
{
    TongHang,
    FanHang,
    TYouLi,
    TBuLi
};


enum AirControl{
    FULL,
    ADVANTAGE,
    BALANCE,
    LOST
};



class BattleInfo:Ref
{
    friend class BattlePanel;
public:
    static BattleInfo* create(BattleFleet* kantaiFleet,BattleFleet* enemyFleet,FormationType kantaiFormation,FormationType enemyFormation);
    bool init(BattleFleet* kantaiFleet,BattleFleet* enemyFleet,FormationType kantaiFormation,FormationType enemyFormation);
    
    static BattleInfo* create();
    bool init();
    
    
    ~BattleInfo();
public:
    inline BattleFleet*  GetKantais(){ return m_pKantaiFleet; }
    inline BattleFleet*  getEnemies(){ return m_pEnemyFleet; }
    inline void SetKantaiFormation(FormationType formation){ m_KantaiFormationType = formation; }
    inline void SetEnemyFormation(FormationType formation){ m_EnemyFormationType = formation; }
    inline FormationType GetKantaiFormation(){ return m_KantaiFormationType; }
    inline FormationType GetEnemyFormation(){ return m_EnemyFormationType; }
    inline void SetTWord(T_Word tword){ m_tWord = tword; }
    inline T_Word GetTWord(){ return m_tWord; }
    
    
public:
    float GetDamageAfterMaxCorrection(float damage, AttackType type);
    float FormationCorrection(FormationType type, bool antiSubmarine);
    float TWordCorrection(T_Word t);
    float BrokenCorrection(BrokenType type);
    float AmmoCorrection();
    bool  DouldeHitTriggered(BattleCharacterInfo *acttacker);
    bool  SpecialAttackTriggered(BattleCharacterInfo *acttacker);
    bool  CutinTriggered(BattleCharacterInfo *acttacker);
    void  ResetFireBattle();
    void  InsertToRangeVector(Shooting_Range range, int i);
    
    
private:
    FormationType     m_KantaiFormationType;
    FormationType     m_EnemyFormationType;
    BattleFleet*      m_pKantaiFleet;
    BattleFleet*      m_pEnemyFleet;
    T_Word            m_tWord;
    AirControl        m_AirControl;
    
    
    std::vector<int>  m_vExlongIndex;
    std::vector<int>  m_vLongIndex;
    std::vector<int>  m_vMidIndex;
    std::vector<int>  m_vShortIndex;
    
    
    
private:
    int GetDamage(AttackType attacktype,float basicAttack,int enemyArmour,float preCorrection, float postCorrection, float AmmoCorrection);
    //float postCorrection();
  
public:
    int GetTargetIndex(bool alliesAttack);
    bool GetNextIndexToFire(bool &allies, int &index);
    void GetFireDamage(bool alliesAttack, int alliesIndex, int enemyIndex, bool &doubleHit, bool &specialAttack, bool &ci, int &damage, bool &critical,bool &miss);
};


//
//class BattleModel{
//public:
//    BattleModel();
//    BattleModel(Fleet* allies, Fleet* enemy, FormationType alliesFormation, FormationType enemyFormation);
//    //À˜µ–
//    
//    //∫Ωø’’Ω
//    inline AirControl getAirControl(){ return airControl; }
//    
//    //÷ß‘ÆΩ¢∂”
//    
//    //ø™ƒª¿◊ª˜
//    
//    //≈⁄ª˜’Ω
//    void resetFireBattle();
//    int getTargetIndex(bool alliesAttack);
//    bool getNextIndexToFire(bool &allies, int &index);
//    void getFireDamage(bool alliesAttack, int alliesIndex, int enemyIndex, bool &doubleHit, bool &specialAttack, bool &ci, int &damage, bool &critical,bool &miss);
//    bool douldeHitTriggered(CharacterInfo *acttacker);  // «∑Ò¥•∑¢∂˛¡¨
//    bool specialAttackTriggered(CharacterInfo *acttacker);	// «∑Ò¥•∑¢Ãÿ ‚π•ª˜
//    bool cutinTriggered(CharacterInfo *acttacker); // «∑Ò¥•∑¢CI
//    
//    
//    inline std::vector<CharacterInfo*> getAllies(){ return allies; }
//    inline std::vector<CharacterInfo*> getEnemies(){ return enemy; }
//    inline void setAlliesFormation(FormationType formation){ alliesFormation = formation; }
//    inline void setEnemyFormation(FormationType formation){ enemyFormation = formation; }
//    inline FormationType getAlliesFormation(){ return alliesFormation; }
//    inline FormationType getEnemyFormation(){ return enemyFormation; }
//    inline void setTWord(T_Word tword){ this->tword = tword; }
//    inline T_Word getTWord(){ return tword; }
//private:
//    std::vector<CharacterInfo*> allies;
//    std::vector<CharacterInfo*> enemy;
//    FormationType alliesFormation;
//    FormationType enemyFormation;
//    Air_Control airControl;
//    T_Word tword;
//    
//    //◊‹…À∫¶π´ Ω …À∫¶=[…œœﬁ–ﬁ’˝(ª˘±æπ•ª˜¡¶*…œœﬁ«∞≤π’˝)*…œœﬁ∫Û≤π’˝-µ–◊∞º◊*¬“ ˝]*µØ“©¡ø≤π’˝
//    int getDamage(Attack_Type attacktype,float basicAttack,int enemyArmour,float preCorrection, float postCorrection, float AmmoCorrection);
//    
//    //π•ª˜¡¶…œœﬁ≤π’˝
//    float getDamageAfterMaxCorrection(float damage, Attack_Type type);
//    //…À∫¶≤π’˝ ∑µªÿ≥À∑®œµ ˝
//    float formationCorrection(FormationType type,bool antiSubmarine); //’Û–Õ≤π’˝
//    float TWordCorrection(T_Word t);//T◊÷≤π’˝
//    float brokenCorrection(BrokenType type);//…ÀÀ≤π’˝
//    float ammoCorrection();//≤–µØ≤π’˝  TODO
//    
//    float postCorrection();//
//    
//    
//    //¥Ê∑≈∏˜¥¨…‰≥Ã£¨”√”⁄º∆À„≈⁄ª˜À≥–Ú°£’˝ ˝¥˙±ÌŒ“∑Ω£¨∏∫ ˝¥˙±Ìµ–∑Ω°£
//    void  insertToRangeVector(Shooting_Range range, int index);
//    std::vector<int> exlongIndex;
//    std::vector<int> longIndex;
//    std::vector<int> midIndex;
//    std::vector<int> shortIndex;
//    
//    
//private:
//    
//    
//};
//

NS_KCL_END

#endif /* BattleModel_hpp */
