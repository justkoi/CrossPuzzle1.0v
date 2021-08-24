#pragma once

#include "stdafx.h"
USING_NS_CC;
using namespace std;

typedef enum eDerection
{
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
	E_MAX
}E_DERECTION;

class MenuScene : public cocos2d::CCLayer
{
public:
	

	CCSprite* m_pSprite;
	CCSprite* m_pBlind;


	float m_fBackGroundTimer;

	CCSprite* m_pTitle;

	CCSprite* m_pPopUp;

	CMStyleButton m_pGameStart;
	CMStyleButton m_pOption;
	CMStyleButton m_pCredit;
	CMStyleButton m_pExit;
	CMStyleButton m_pCancel;
	CMStyleButton m_pBGM;
	CMStyleButton m_pEffect;

	 //CCMenuItemImage* m_pGameStartItem;
	// CCMenu* m_pGameStart;
	
	/*CCMenuItemImage* m_pOptionItem;
	CCMenu* m_pOption;

	CCMenuItemImage* m_pCreditItem;
	CCMenu* m_pCredit;
	
	CCMenuItemImage* m_pExitItem;
	CCMenu* m_pExit;*/
/*
	CCMenuItemImage* m_pCancelItem;
	CCMenu* m_pCancel;
	
	
	CCMenuItemImage* m_pBGMItem;
	CCMenu* m_pBGM;
	
	CCMenuItemImage* m_pEffectItem;
	CCMenu* m_pEffect;*/
	


	float m_fTimer;
	float m_fRotationTimer;
	float m_fTitleRotationTimer;

	bool m_bPopUp;

public:
	

public:
	void SaveOption();
	bool LoadOption();
	

	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void GameStartCallback(CCObject* pSender);
    void CreditCallback(CCObject* pSender);
    void ExitCallback(CCObject* pSender);
    void OptionCallback(CCObject* pSender);
    void CancelCallback(CCObject* pSender);
	
    void BGM_Callback(CCObject* pSender);
    void EFFECT_Callback(CCObject* pSender);
    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(MenuScene);

    void Update(float dt);
	
	virtual void  registerWithTouchDispatcher();
	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	


};
