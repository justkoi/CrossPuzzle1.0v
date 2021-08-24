#pragma once

#include "stdafx.h"

USING_NS_CC;

class CreditScene : public cocos2d::CCLayer
{
public:
	
	float		m_fNewTimer;
	float		m_fTimer;
	CCSprite* m_pBackGround;

	CCActionInterval* m_pLogoAnt;//[E_BLOCKNUMBER_MAX];
	CCAnimation* m_pLogoAni;

	vector<CCreditBlock*> m_pCreditBlockList;

	int m_nStep;
	
	CMStyleButton m_pBack;

public:
	



	
	void		BackCallback(CCObject* pSender);
	void Explosion(CCPoint CPos, E_BLOCKNUMBER eBlockNumber);
	
	virtual void  registerWithTouchDispatcher();
	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	
public:
	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(CreditScene);
    void Update(float dt);
	void AddCreditBlock(CCPoint stPos, float fGround, float fDelayTime, string strFilePath);

	CCreditBlock* SearchBlockIndex(int nIndex);
};
