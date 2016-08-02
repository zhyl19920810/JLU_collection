//
//  SupplyInfo.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/2/16.
//
//

#ifndef SupplyInfo_hpp
#define SupplyInfo_hpp


#include "SystemHeader.h"
#include "kantai.h"


NS_KCL_BEGIN

class Fleet;

class SupplyImp
{
    friend class PortSupplyLayer;
    friend class ShipUnit;
public:
    
    static SupplyImp* create();
    
    bool canFillUpAmmo(Kantai* kantai);
    void addConsumeAmmo(int position,int ammo);
     int minusConsumeAmmo(int position);
    
    
    bool canFillUpFuel(Kantai* kantai);
    void addConsumeFuel(int position,int fuel);
    int minusConsumeFuel(int position);
    
    int getConsumeAmmo() {return consumeAmmo;}
    int getConsumeFuel() {return consumeFuel;}
    
    void refresh();
    
    void callAmmoButton(Fleet* fleet);
    void callFuelButton(Fleet* fleet);
    void callMidButton(Fleet* fleet);
private:
    
    void refreshLayer();
    
    bool init();
    int consumeAmmo;
    int consumeFuel;
    std::map<int,int> ammoST;
    std::map<int,int> fuelST;
    
};


NS_KCL_END

#endif /* SupplyInfo_hpp */
