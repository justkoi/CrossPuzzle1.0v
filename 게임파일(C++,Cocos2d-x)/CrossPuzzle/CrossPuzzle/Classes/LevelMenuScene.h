#pragma once

#include "stdafx.h"
USING_NS_CC;
using namespace std;


class LevelMenuScene : public cocos2d::CCLayer
{
public:
	

	CCSprite* m_pBackGround;
	CCSprite* m_pBackGroundLight;

	CMStyleButton m_pEasy;
	CMStyleButton m_pNormal;
	CMStyleButton m_pHard;
	CMStyleButton m_pBack;

	/*CCMenuItemImage* m_pEasyItem;
	CCMenu* m_pEasy;
	CCMenuItemImage* m_pNormalItem;
	CCMenu* m_pNormal;
	CCMenuItemImage* m_pHardItem;
	CCMenu* m_pHard;
*/

	float m_fTimer;
	float m_fLightTimer;
	int m_nLightLevel;
	/*
	CCMenuItemImage* m_pBackItem;
	CCMenu* m_pBack;*/

public:
	void		BackCallback(CCObject* pSender);

public:
	

	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void EasyCallback(CCObject* pSender);
    void NormalCallback(CCObject* pSender);
    void HardCallback(CCObject* pSender);

    void CancelCallback(CCObject* pSender);

    LAYER_CREATE_FUNC(LevelMenuScene);

    void Update(float dt);


	virtual void  registerWithTouchDispatcher();
	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	

};
