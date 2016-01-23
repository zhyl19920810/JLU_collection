//
//  KantaiPlayerGot.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//
#include "kantai.h"

Kantai::Kantai():
kantaiImp(NULL),
parent(NULL)
{
    
}

Kantai::~Kantai()
{
    kantaiImp=NULL;
    parent=NULL;
}


Kantai* Kantai::create()
{
    Kantai* kantai=new Kantai;
    if (!kantai)
    {
        CCASSERT(false, "can not init the kantai");
    }
    return kantai;
}


Kantai* Kantai::create(int kantaiKey,int kantaiNumber,LoadState state,Ref* parent)
{
    Kantai* kantai=new Kantai;
    
    if (kantai)
    {
        kantai->init(kantaiKey, kantaiNumber,state,parent);
    }
    else
    {
        CCASSERT(false, "can not init the kantai");
    }
    return kantai;
}



void Kantai::init(int kantaiKey, int kantaiNumber, LoadState state,Ref* parent)
{
    this->parent=parent;
    this->kantaiNumber=kantaiNumber;
    this->kantaiKey=kantaiKey;
    switch (state) {
        case LoadState::INIT_KANTAI:
        {
            kantaiImp=sKantaiMgr.GetKantaiMap(kantaiNumber);
            currLV=kantaiImp->lv;
            currFuel=kantaiImp->fuel;
            currAmmo=kantaiImp->ammo;
            currHp=kantaiImp->maxHp;
            searchEnemy=kantaiImp->initSearchEnemy;
            armor=kantaiImp->initArmor;
            luck=kantaiImp->initLuck;
            AntiSubMarine=kantaiImp->initAntiSubmarine;
            dodge=kantaiImp->initDodge;
            torpedo=kantaiImp->initTorpedo;
            firePower=kantaiImp->initFirePower;
            antiAir=kantaiImp->initAntiAir;
            currExp=0;
            setUpdateExp();
            fatigueValue=INIT_FATIGUEVALUE;
            kantaiLock=false;
            kantaiStar=0;
            kantaiState=KantaiState::Free;
            brokenType=BrokenType::normal;
            int equipSize=getKantaiEquipSize();
            equipGrid.resize(equipSize);
            currPlaneLoad.resize(equipSize);
            for (int i=0; i<equipSize; ++i) {
                currPlaneLoad[i]=getInitPlaneLoad(i);
            }
            break;
        }
        case LoadState::READ_KANTAI_DATABASE:
        {
            kantaiImp=sKantaiMgr.GetKantaiMap(kantaiNumber);
            break;
        }
        default:
            break;
    }
}



//
//Kantai::Kantai(ValueVector& _kantaiData)
//{
//    equipGrid.resize(_kantaiData[4].asInt());
//    geneNewKantai(_kantaiData);
//}
//
//Kantai::Kantai(int _id,LoadState loadState)
//{
//    switch (loadState)
//    {
//        case READ_KANTAI_DATABASE:
//        {
//            kantaiKey=_id;
//            break;
//        }
//        default:
//            break;
//    }
//}
//
//
//Kantai::Kantai(int _kantaiKey,ValueVector& _kantaiData)
//{
//    int size=_kantaiData[4].asInt();
//    equipGrid.resize(size);
//    planeLoadPr.resize(size);
//    maxPlaneLoad.resize(size);
//    
//    kantaiKey=_kantaiKey;
//    geneNewKantai(_kantaiData);
//}
//
//void Kantai::geneNewKantai(ValueVector &_kantaiData)
//{
//    
////    ValueMap _name=_kantaiData[0].asValueMap();
////    kantaiName=_name.at("kantaiName").asString();
////    kantaiFullName=_name.at("kantaiFullName").asString();
////    
//////    ///这里返回插入从数据库获得的主键
//////    kantaiKey=1;   /////////??????
////    
////    ValueMap _kantaiBaseAtrr=_kantaiData[1].asValueMap();
////    kantaiNumber=_kantaiBaseAtrr.at("kantaiNumber").asInt();
////    kantaiType=_kantaiBaseAtrr.at("kantaiType").asInt();
////    currLV=1;
////    
////    
////    maxFuel=currFuel=_kantaiBaseAtrr.at("fuel").asInt();
////    currAmmo=maxAmmo=_kantaiBaseAtrr.at("ammo").asInt();
////    speed=_kantaiBaseAtrr.at("speed").asInt();
////    initRange=range=_kantaiBaseAtrr.at("range").asInt();
////    currHp=maxHp=_kantaiBaseAtrr.at("maxHp").asInt();
////    
////    
////    currExp=0;
////    
////    ///这里的设定根据一个映射表根据
////    updateExp=10000; //////////?????
////    
////    
////    ValueMap _kantaiInitAtrr=_kantaiData[3].asValueMap();
////    firePower=_kantaiInitAtrr.at("initFirePower").asInt();
////    armor=_kantaiInitAtrr.at("initArmor").asInt();
////    torpedo=_kantaiInitAtrr.at("initTorpedo").asInt();
////    dodge=_kantaiInitAtrr.at("initDodge").asInt();
////    antiAir=_kantaiInitAtrr.at("initAntiAir").asInt();
////    AntiSubMarine=_kantaiInitAtrr.at("initAntiSubmarine").asInt();
////    searchEnemy=_kantaiInitAtrr.at("initSearchEnemy").asInt();
////    luck=_kantaiInitAtrr.at("initLuck").asInt();
////    
////    fatigueValue=49;
////    
////    kantaiLock=false;
////    
////    kantaiStar=1;
////    
////    kantaiState=1;///??????
////    if (_kantaiData[4].asInt())
////    {
////        ValueVector _planeLoad=_kantaiData[6].asValueVector();
////        for (auto it=_planeLoad.begin(); it!=_planeLoad.end(); ++it)
////        {
////            planeLoad.push_back(it->asInt());
////        }
////    }
//}
//
/////set Attrubute
void Kantai::setCurrLV(int _currLV)
{
    currLV=_currLV;
    KantaiDB::getInstance()->setCurrLV(kantaiKey, currLV);
    setUpdateExp();
}

void Kantai::setCurrFuel(int _currFuel)
{
    currFuel=_currFuel;
    KantaiDB::getInstance()->setCurrFuel(kantaiKey, _currFuel);
}

void Kantai::setCurrAmmo(int _currAmmo)
{
    currAmmo=_currAmmo;
    KantaiDB::getInstance()->setCurrAmmo(kantaiKey, _currAmmo);
}
void Kantai::setCurrHp(int _currHp)
{
    if(_currHp<0)
        currHp=0;
    currHp=_currHp;
    setBrokenType();
    KantaiDB::getInstance()->setCurrHp(kantaiKey, _currHp);
}
bool Kantai::fillUpFuel()
{
    bool bRet=false;
    do
    {
        setCurrFuel(getMaxFuel());
        bRet=true;
    }while(0);
    return bRet;
}

bool Kantai::fillUpAmmo()
{
    bool bRet=false;
    do
    {
        setCurrAmmo(getMaxAmmo());
        bRet=true;
    }while(0);
    return bRet;
}
void Kantai::setFirePower(int _firePower)
{
    firePower=_firePower;
    KantaiDB::getInstance()->setFirePower(kantaiKey, _firePower);
}
void Kantai::setArmor(int _armor)
{
    armor=_armor;
    KantaiDB::getInstance()->setArmor(kantaiKey, _armor);
}
void Kantai::setTorpedo(int _torpedo)
{
    torpedo=_torpedo;
    KantaiDB::getInstance()->setTorpedo(kantaiKey, _torpedo);
}
void Kantai::setDodge(int _dodge)
{
    dodge=_dodge;
    KantaiDB::getInstance()->setDodge(kantaiKey, _dodge);
}
void Kantai::setAntiAir(int _antiAir)
{
    antiAir=_antiAir;
    KantaiDB::getInstance()->setAntiAir(kantaiKey, _antiAir);
}
void Kantai::setAntiSubmarine(int _antiSubmarine)
{
    AntiSubMarine=_antiSubmarine;
    KantaiDB::getInstance()->setAntiSubmarine(kantaiKey, _antiSubmarine);
}
void Kantai::setSearchEnemy(int _serachEnemy)
{
    searchEnemy=_serachEnemy;
    KantaiDB::getInstance()->setSearchEnemy(kantaiKey, _serachEnemy);
}
void Kantai::setLuck(int _luck)
{
    luck=_luck;
    KantaiDB::getInstance()->setLuck(kantaiKey, _luck);
}

bool Kantai::addExp(int exp)
{
    bool bRet=false;
    do
    {
        if (currLV==100) {
            break;
        }
        currExp+=exp;
        if (currExp>=updateExp)
        {
            currExp=currExp-updateExp;
            KantaiDB::getInstance()->setCurrExp(kantaiKey, currExp);
            setCurrLV(getCurrLV()+1);
        }
    bRet=true;
    }while(0);
    return bRet;
}

void Kantai::setUpdateExp()
{
    updateExp=sExpMgr.getKantaiUpdateExp(currLV);
}


void Kantai::setFatigueValue(int _fatigueValue)
{
    fatigueValue=_fatigueValue;
    KantaiDB::getInstance()->setFatigueValue(kantaiKey, _fatigueValue);
}
void Kantai::setKantaiLock(bool _kantaiLock)
{
    kantaiLock=_kantaiLock;
    KantaiDB::getInstance()->setKantaiLock(kantaiKey, _kantaiLock);
}
void Kantai::setKantaiStar(int _kantaiStar)
{
    kantaiStar=_kantaiStar;
    KantaiDB::getInstance()->setKantaiStar(kantaiKey, _kantaiStar);
}
void Kantai::setKantaiState(KantaiState _kantaiState)
{
    kantaiState=_kantaiState;
    KantaiDB::getInstance()->setKantaiState(kantaiKey, _kantaiState);
}
void Kantai::setBrokenType()
{
    float persentage=0;
    if (getMaxHp()) {
        persentage=getCurrHp()/getMaxHp();
    }
    else
    {
        CCASSERT(false, "max Hp is 0");
    }
    
    if (persentage>0.75)
    {
        brokenType=BrokenType::normal;
    }
    else if(persentage>0.5)
    {
        brokenType=BrokenType::tiny;
    }
    else if(persentage>0.25)
    {
        brokenType=BrokenType::mid;
    }
    else if(persentage>0)
    {
        brokenType=BrokenType::large;
    }
    else
    {
        brokenType=BrokenType::drown;
    }
}






bool Kantai::canAirBattle()
{
    KantaiType type=getKantaiType();
    if (type!=KantaiType::Air_Cruiser
        &&type!=KantaiType::Armor_Carrier
        &&type!=KantaiType::Diving_Carrier
        &&type!=KantaiType::Carrier
        &&type!=KantaiType::Light_Carrier
        &&type!=KantaiType::Seaplane_Carrier)
    {
        return false;
    }
    
    for (int i=0; i<6; ++i)
    {
        if (equipGrid[i])
        {
            auto equipType=equipGrid[i]->getEquipType();
            if (equipType==EquipScope::Aircraft||equipType==EquipScope::SeaPlane)
            {
                return true;
            }
        }
    }
    return false;
}

Equip* Kantai::getMainCannon()
{
    for (int i=0; i<6; ++i)
    {
        if (equipGrid[i]!=nullptr)
        {
            auto type=equipGrid[i]->getEquipType();
            if (type==EquipType::Small_Caliber
                ||type==EquipType::Medium_Caliber
                ||type==EquipType::Large_Caliber) {
                return equipGrid[i];
            }
        }
    }
    return nullptr;
}

void Kantai::getDamage(int damage)
{
    if (damage>0)
    {
        this->currHp=currHp-damage;
        
        if (this->currHp<0)
        {
            currHp=0;
        }
        setBrokenType();
    }
}


bool Kantai::canAttack()
{
    KantaiType type=getKantaiType();
    if (type==KantaiType::Carrier||type==KantaiType::Light_Carrier)
    {
        float percentage=getCurrHp()/getMaxHp();
        if (percentage<=0.5)
        {
            return false;
        }
    }
    
    
    if (currHp==0)
    {
        return false;
    }
    
    return true;
}

//
//
//
//
//void KantaiPrint::PrintKantaiInfo(const Kantai &_kantai)
//{
//    log("kantaiName:   %s",_kantai.getkantaiName().c_str());
//    log("kantaiFullName:  %s",_kantai.getkantaiFullName().c_str());
//    log("kantaiKey:    %d",_kantai.getkantaiKey());
//    log("kantaiNumber:    %d",_kantai.getkantaiNumber());
//    log("kantaiType:    %d",_kantai.getkantaiType());
//    log("currLv:    %d",_kantai.getcurrLV());
//    log("currFuel:    %d",_kantai.getcurrFuel());
//    log("maxFuel:    %d",_kantai.getmaxFuel());
//    log("currAmmo:    %d",_kantai.getcurrAmmo());
//    log("maxAmmo:    %d",_kantai.getmaxAmmo());
//    log("speed:    %d",_kantai.getspeed());
//    log("initRange:    %d",_kantai.getinitRange());
//    log("range:    %d",_kantai.getrange());
//    log("currHp:    %d",_kantai.getcurrHp());
//    log("maxHp:    %d",_kantai.getmaxHp());
//    log("currExp:    %d",_kantai.getcurrExp());
//    log("updateExp:    %d",_kantai.getupdateExp());
//    log("firePower:    %d",_kantai.getfirePower());
//    log("armor:    %d",_kantai.getarmor());
//    log("torpedo:    %d",_kantai.gettorpedo());
//    log("dodge:    %d",_kantai.getdodge());
//    log("antiAir:    %d",_kantai.getantiAir());
//    log("AntiSubMarine:    %d",_kantai.getAntiSubMarine());
//    log("searchEnemy:    %d",_kantai.getsearchEnemy());
//    log("luck:    %d",_kantai.getluck());
//    log("fatigueValue:    %d",_kantai.getfatigueValue());
//    log("kantaiLock:    %d",_kantai.getkantaiLock());
//    log("kantaiStar:    %d",_kantai.getkantaiStar());
//    log("kantaiState:    %d",_kantai.getkantaiStar());
////    auto _equipgrid=_kantai.getEquipgrid();
////    
////    log("kantaiEquipSize:    %d",_equipgrid->getkantaiEquipSize());
////    
////    const std::map<equilp_iter,Equip*> &_equipData=_equipgrid->getequipData();
////    
////    EquipPrint zhang;
////    for (auto it=_equipData.cbegin(); it!=_equipData.cend(); ++it)
////    {
////        zhang.PrintEquipInfo(it->second);
////    }
////    int count=1;
////    const std::map<equilp_iter,plane_load> &_planeLoad=_equipgrid->getplaneLoad();
////    for (auto it=_planeLoad.cbegin(); it!=_planeLoad.cend(); ++it)
////    {
////        log("the %d  is:  %d",count++,it->second);
////    }
//    
//    
//    
//}
//
//


