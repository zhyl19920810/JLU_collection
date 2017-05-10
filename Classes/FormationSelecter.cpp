//
//  FormationSelecter.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#include "FormationSelecter.hpp"


NS_KCL_BEGIN

bool FormationSelecter::init()
{
    bool bRet=false;
    
    do
    {
        Formation* danzong=Formation::create(DanZong);
        danzong->setPosition(450, 370);
        danzong->setVisible(false);
        addChild(danzong);
        
        Formation * fuzong = Formation::create(FuZong);
        fuzong->setPosition(580, 370);
        fuzong->setVisible(false);
        this->addChild(fuzong);
        
        Formation * lunxing =Formation::create(LunXing);
        lunxing->setPosition(710, 370);
        lunxing->setVisible(false);
        this->addChild(lunxing);
        
        Formation * tixing =Formation::create(TiXing);
        tixing->setPosition(510, 210);
        tixing->setVisible(false);
        this->addChild(tixing);
        
        Formation * danheng =Formation::create(DanHeng);
        danheng->setPosition(640, 210);
        danheng->setVisible(false);
        this->addChild(danheng);
        
        m_vFormation.push_back(danzong);
        m_vFormation.push_back(fuzong);
        m_vFormation.push_back(lunxing);
        m_vFormation.push_back(tixing);
        m_vFormation.push_back(danheng);
        
        bRet=true;
    }while(0);
    
    return bRet;
}

void FormationSelecter::ShowSelecter(int kantaiSize)
{
    m_iKantaiSize=kantaiSize;
    for(Formation* formation:m_vFormation)
    {
        formation->UpdateInfo(m_iKantaiSize);
        formation->ShowPoints();
        formation->setVisible(true);
    }
}

void FormationSelecter::HideSelecter()
{
    for(Formation* formation:m_vFormation)
    {
        formation->HidePoints();
        formation->setVisible(true);
    }
}


NS_KCL_END
