//
//  Formation.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef Formation_hpp
#define Formation_hpp


#include "cocos2d.h"
#include "SallyInfo.hpp"


NS_KCL_BEGIN


USING_NS_CC;


class SallyPanel;

//TODO Enemy怎么处理
class Formation : public Node{
public:
    
    FormationType GetType() {return m_FormationType;}
    static Formation* create(FormationType _type,bool hasBg);
    virtual bool init(FormationType _type,bool hasBg);
    void ShowPoints();
    void HidePoints();
    void AddBattleBorder();
    void UpdateInfo(int kantaiSize);
    
private:
    void OrganizePoints();
    void Danzong();
    void Fuzong();
    void Tixing();
    void Danheng();
    void Lunxing();
    
    void RotatePoints();
    void InitBg();
    
private:
    std::vector<Sprite*> m_vPoints;
    FormationType        m_FormationType;
    int                  m_iShipCount;
    Sprite*              m_pFormationBg;
    MenuItemImage*       m_pFormationButton;
    SallyPanel*          m_pSallyPanel;
    Sprite*              m_pBorder;
    
    
public:
    //Formation(int shipCount, FormationType type);
    //Formation(int shipCount, FormationType type,bool isEnemy);
    //Formation(FormationType type,SallyScene* parent);//initial with Formation panel with button. Used only in sally scene
    //void initializePanel(SallyScene *parentSallyScene);
    
private:
    //std::string pointUrl;
    //FormationType type;
    //Sprite *border;
    //Sally Panel
    //Sprite* panelBg;
    //MenuItemImage * button;
    
};





NS_KCL_END



#endif /* Formation_hpp */
