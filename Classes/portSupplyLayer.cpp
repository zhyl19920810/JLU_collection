//
//  portSupplyLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portSupplyLayer.h"
#include "portScene.h"


void  ValueBar::setVisible(bool visible)
{
    barPic->setVisible(visible);
}


ValueBar::ValueBar(const cocos2d::Vec2 &location,Node* parent)
{
    barPic=Sprite::create();
    barPic->setPosition(location);
    this->parent=parent;
    parent->addChild(barPic);
}

void ValueBar::setValue(int value)
{
    char name[30];
    bzero(name, sizeof(name));
    sprintf(name, "value%d.png",value);
    barPic->setSpriteFrame(name);
}


void ShipUnit::setNoKantai()
{
    kantaiBg->setSpriteFrame("supplyNoShip.png");
    star->setVisible(false);
    kantaiName->setVisible(false);
    kantaiState->setVisible(false);
    supplyBg1->setVisible(false);
    supplyBg2->setVisible(false);
    ammoBar->setVisible(false);
    fuelBar->setVisible(false);
}



PortSupplyLayer::PortSupplyLayer()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SupplyMain/supplyLayer.plist", "SupplyMain/supplyLayer.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CommonAssets/commonAssets.plist", "CommonAssets/commonAssets.pvr.ccz");
    consumeAmmo=0;
    consumeFuel=0;
    fleetNumber=1;
    ammoST.clear();
    fuelST.clear();
    shipUnit.resize(6);
    
}

PortSupplyLayer::~PortSupplyLayer()
{
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("SupplyMain/supplyLayer.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("SupplyMain/supplyLayer.pvr.ccz");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("CommonAssets/commonAssets.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("CommonAssets/commonAssets.pvr.ccz");
}


bool PortSupplyLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    initLayer();
    initKantaiTable();
    
    return true;
}


void PortSupplyLayer::initLayer()
{
    Size size=Director::getInstance()->getVisibleSize();
    
    auto bgimg = Sprite::createWithSpriteFrameName("supplyBg1.png");
    this->addChild(bgimg);
    //bgimg->setOpacity(200);
    bgimg->setPosition(450, 200);
    
    auto bgimg2 = Sprite::createWithSpriteFrameName("supplyBg2.png");
    this->addChild(bgimg2,2);
    bgimg2->setPosition(695, 200);
    
    
    auto fuelIcon=Sprite::create();
    fuelIcon->setSpriteFrame("supplyFuel.png");
    this->addChild(fuelIcon);
    fuelIcon->setPosition(417, 364);
    
    auto ammoIcon = Sprite::createWithSpriteFrameName("supplyAmmo.png");
    this->addChild(ammoIcon);
    ammoIcon->setPosition(525, 364);
    
    char tmp[30];
    bzero(tmp, sizeof(tmp));
    
    sprintf(tmp, "%d",sPlayer.getFuel());
    fuelNumber=Label::create();
    addChild(fuelNumber);
    fuelNumber->setPosition(fuelIcon->getPosition()+Vec2(45, 0));
    fuelNumber->setString(tmp);
    fuelNumber->setColor(Color3B::BLACK);
    
    sprintf(tmp, "%d",sPlayer.getAmmo());
    ammoNumber=Label::create();
    addChild(ammoNumber);
    ammoNumber->setPosition(ammoIcon->getPosition()+Vec2(45, 0));
    ammoNumber->setString(tmp);
    ammoNumber->setColor(Color3B::BLACK);
    
    auto bgimg3 = Sprite::createWithSpriteFrameName("supplyBg3.png");
    this->addChild(bgimg3);
    bgimg3->setAnchorPoint(Vec2(1, 0.5));
    bgimg3->setPosition(size.width, size.height*5/6);
    bgimg3->setGlobalZOrder(-1);
    bgimg3->setOpacity(150);
    
    auto supplyTitle =Sprite::createWithSpriteFrameName("suppyTitle.png");
    this->addChild(supplyTitle,2);
    supplyTitle->setPosition(size.width-supplyTitle->getContentSize().width/2, size.height*3/4);
    
    auto leftTitle=Sprite::createWithSpriteFrameName("leftTitle.png");
    this->addChild(leftTitle);
    leftTitle->setPosition(Vec2(156, size.height*5/6));
    
    auto rightTitle=Sprite::createWithSpriteFrameName("rightTitle.png");
    addChild(rightTitle);
    rightTitle->setPosition(Vec2(size.width-130, size.height*5/6));
        auto midButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("AFButton2.png"),Sprite::createWithSpriteFrameName("AFButton3.png"), CC_CALLBACK_1(PortSupplyLayer::callBack, this));
    midButton->setPosition(700, 50);
    midButtonUp=Sprite::createWithSpriteFrameName("AFButton1.png");
    addChild(midButtonUp,3);
    midButtonUp->setPosition(midButton->getPosition());
    
    
    
    auto fuelButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("fuelButton2.png"),Sprite::createWithSpriteFrameName("fuelButton3.png"), CC_CALLBACK_1(PortSupplyLayer::callBack, this));
    fuelButton->setPosition(midButton->getPosition().x-midButton->getContentSize().width/2-fuelButton->getContentSize().width/2, 50);
    fuelButtonUp=Sprite::createWithSpriteFrameName("fuelButton1.png");
    addChild(fuelButtonUp,3);
    fuelButtonUp->setPosition(fuelButton->getPosition());
    
    
    auto ammoButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ammoButton2.png"),Sprite::createWithSpriteFrameName("ammoButton3.png"), CC_CALLBACK_1(PortSupplyLayer::callBack, this));
    ammoButton->setPosition(midButton->getPosition().x+midButton->getContentSize().width/2+fuelButton->getContentSize().width/2, 50);
    ammoButtonUp=Sprite::createWithSpriteFrameName("ammoButton1.png");
    addChild(ammoButtonUp,3);
    ammoButtonUp->setPosition(ammoButton->getPosition());
    
    
    
    auto menu = Menu::create(fuelButton, midButton, ammoButton, NULL);
    this->addChild(menu,2);
    menu->setPosition(0, 0);
    

    
    
    auto fuelBox =Sprite::createWithSpriteFrameName("fuelBox.png");
    this->addChild(fuelBox,2);
    fuelBox->setPosition(650, 295);
    
    auto ammoBox =Sprite::createWithSpriteFrameName("ammoBox.png");
    this->addChild(ammoBox,2);
    ammoBox->setPosition(750, 295);
    
    auto fuelBg =Sprite::createWithSpriteFrameName("fuelBg.png");
    this->addChild(fuelBg,2);
    fuelBg->setPosition(650, 190);
    
    auto ammoBg =Sprite::createWithSpriteFrameName("ammoBg.png");
    this->addChild(ammoBg,2);
    ammoBg->setPosition(750, 190);
    
    
    auto lSupplyLight=Sprite::createWithSpriteFrameName("supplyLight.png");
    addChild(lSupplyLight,3);
    lSupplyLight->setPosition(fuelBg->getPosition()-Vec2(0,15));
    
    auto rSupplyLight=Sprite::createWithSpriteFrameName("supplyLight.png");
    addChild(rSupplyLight,3);
    rSupplyLight->setPosition(ammoBg->getPosition()-Vec2(0,15));
}

void PortSupplyLayer::addConsumeAmmo(int position,int ammo)
{
    if (ammoButtonUp->isVisible())
    {
        ammoButtonUp->setVisible(false);
    }
    if (midButtonUp->isVisible())
    {
        midButtonUp->setVisible(false);
    }
    consumeAmmo+=ammo;
    ammoST.insert(std::pair<int, int>(position,ammo));
    

    
    ///Action
}

void PortSupplyLayer::addConsumeFuel(int position, int fuel)
{
    if (fuelButtonUp->isVisible())
    {
        fuelButtonUp->setVisible(false);
    }
    if (midButtonUp->isVisible()) {
        midButtonUp->setVisible(false);
    }
    consumeFuel+=fuel;
    fuelST.insert(std::pair<int, int>(position,fuel));
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeFuel);
    consumeFuelLabel->setString(tmp);
    
    //action
}

int PortSupplyLayer::minusConsumeAmmo(int position)
{
    auto it=ammoST.find(position);
    CCASSERT(it!=ammoST.end(), "the position do not exist in \"function minusConsumeAmmo\"");
    int minusAmmo=it->second;
    consumeAmmo-=minusAmmo;
    ammoST.erase(it);
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeAmmo);
    consumeAmmoLabel->setString(tmp);
    
    if (!consumeAmmo) {
        ammoButtonUp->setVisible(true);
        if (!consumeFuel) {
            midButtonUp->setVisible(true);
        }
    }
    return minusAmmo;
}

int PortSupplyLayer::minusConsumeFuel(int position)
{
    auto it=fuelST.find(position);
    CCASSERT(it!=fuelST.end(), "the position do not exist in \"function minusConsumeFuel\"");
    int minusFuel=it->second;
    consumeFuel-=minusFuel;
    fuelST.erase(it);
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeFuel);
    consumeFuelLabel->setString(tmp);
    
    if (!consumeFuel) {
        fuelButtonUp->setVisible(true);
        if (!consumeAmmo) {
            midButtonUp->setVisible(true);
        }
    }
    return minusFuel;
}

void ShipUnit::callback(Ref* pSender)
{
    log("dfgsdflgkjsdkfgsdf");
}

ShipUnit::ShipUnit(int position,Node* parent)
{
    kantaiBg=Sprite::create();
    kantaiBg->setPosition(371,366-52*position);
    kantaiBg->setSpriteFrame("supplyNoShip.png");
    parent->addChild(kantaiBg);
    
    Size size=kantaiBg->getContentSize();
    
    star=Sprite::create();
    star->setPosition(22,size.height/2-2);
    kantaiBg->addChild(star);
    
    kantaiName=Label::create();
    kantaiName->setPosition(200,size.height/2+5);
    kantaiName->setSystemFontSize(20);
    kantaiName->setColor(Color3B::WHITE);
    kantaiName->setAlignment(TextHAlignment::RIGHT);
    kantaiBg->addChild(kantaiName);
    
    kantaiState=Sprite::create();
    kantaiState->setPosition(88,size.height/2-3);
    kantaiBg->addChild(kantaiState);
    
    supplyBg1=Sprite::create();
    supplyBg1->setPosition(241,size.height/2);
    kantaiBg->addChild(supplyBg1);
    
    supplyBg2=Sprite::create();
    supplyBg2->setPosition(390,size.height/2);
    kantaiBg->addChild(supplyBg2);
    
    fuelBar=new ValueBar(Vec2(356, size.height/2), kantaiBg);
    ammoBar=new ValueBar(Vec2(426,size.height/2), kantaiBg);
    this->position=position;
    this->parent=parent;
    

    
}


bool ShipUnit::init(Kantai *kantai)
{
    bool bRet=false;
    do
    {
        this->kantai=kantai;
        select=MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShipUnit::callback,this), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush1.png"), Sprite::create("SupplyMain/SupplyPush1.png")), MenuItemSprite::create(Sprite::create("SupplyMain/SupplyPush2.png"), Sprite::create("SupplyMain/SupplyPush2.png")),
                                                  NULL);
        select->setPosition(kantaiBg->getPosition()-Vec2(17, 0));
        Menu* mn=Menu::create();
        mn->addChild(select);
        mn->setPosition(Vec2::ZERO);
        parent->addChild(mn);
        
        char name[50];
        bzero(name, sizeof(name));
        sprintf(name, "kantai/%d/image 27.png",kantai->getKantaiNumber());
        kantaiBg->setTexture(name);
        
        
        sprintf(name, "star%d.png",position);
        star->setSpriteFrame(name);
        kantaiName->setString(kantai->getKantaiName());
        
        
        double percentage=0;
        int maxHp=kantai->getMaxHp();
        int currHp=kantai->getCurrHp();
        if (maxHp!=0)
        {
            percentage=(float)currHp/(float)maxHp;
        }
        if (percentage>0.75)
        {
            kantaiState->setVisible(false);
        }
        else if (percentage>0.5)
        {
            kantaiState->setSpriteFrame("xiaopoState.png");
        }
        else if (percentage>0.25)
        {
            kantaiState->setSpriteFrame("zhongpoState.png");
        }
        else if(percentage>0)
        {
            kantaiState->setSpriteFrame("dapoState.png");
        }
        else
        {
            kantaiState->setSpriteFrame("sunhuaiState.png");
        }
    
        if (kantai->getKantaiState()==KantaiState::Expedition)
        {
            kantaiState->setVisible(true);
            kantaiState->setSpriteFrame("yuanzhengState.png");
        }

        
        
        supplyBg1->setSpriteFrame("supplyShipBg1.png");
        supplyBg2->setSpriteFrame("supplyShipBg2.png");
        double ammoNo=kantai->getCurrAmmo()*10/kantai->getMaxAmmo();
        double fuelNo=kantai->getCurrFuel()*10/kantai->getMaxFuel();
        
        if (ammoNo<0.0001&&ammoNo>-0.0001) {
            ammoNo=0;
        }
        if (fuelNo<0.0001&&fuelNo>-0.0001) {
            fuelNo=0;
        }
        ammoBar->setValue(ceil(ammoNo));
        fuelBar->setValue(ceil(fuelNo));
        
        bRet=true;
    }while(0);
    return bRet;
}


void PortSupplyLayer::initKantaiTable()
{
//    auto fleet=sPlayer.getFleetByFleetKey(fleetNumber);
//    shipUnit[0]=new ShipUnit(1,this);
//    shipUnit[0]->init(fleet->getShip(1));
//    
    for (int i=0; i<6; ++i)
    {
        shipUnit[i]=new ShipUnit(i+1,this);
    }

    auto fleet=sPlayer.getFleetByFleetKey(fleetNumber);

    if (!fleet)
    {
        for (int i=0; i<6; ++i)
        {
            shipUnit[i]->setNoKantai();
            
        }
        return;
    }
    for (int i=0; i<6; ++i)
    {
        auto kantai=fleet->getShip(i+1);
        if (!kantai)
        {
            shipUnit[i]->setNoKantai();
        }
        else
        {
            shipUnit[i]->init(kantai);
        }
    }
    

//    
//    for (int i=1; i<=6; ++i) {
//        if (!isKantaiExist(i))
//        {
//            kantaiBg[i]->setSpriteFrame("supplyNoShip.png");
//            kantaiName[i]->setVisible(false);
//            kantaiAF[i]->setVisible(false);
//        }
//        else
//        {
//            if (canFillUpAmmo(i)||canFillUpFuel(i))
//            {
//
//            }
//        }
//    }
}

bool PortSupplyLayer::isKantaiExist(int position)
{
    Kantai* kantai=fleet->getShip(position);
    if (!kantai) {
        return false;
    }
    return true;
}

bool PortSupplyLayer::canFillUpAmmo(int position)
{
    Kantai* kantai=fleet->getShip(position);
}


bool PortSupplyLayer::canFillUpFuel(int position)
{
    
}


void PortSupplyLayer::callBack(Ref* pSender)
{
    
}

