#pragma once

#include "stdafx.h"
USING_NS_CC;
using namespace std;

typedef struct 
{
	float m_nActPoint;  //!< 행동력
	float m_nTargetScore; //!< 목표점수
}stStageInfo;



class StageMenuScene : public cocos2d::CCLayer
{
public:
	

	CCSprite* m_pBackGround;
	CCSprite* m_pBackGroundLight;


	CNumber m_CNumber[D_STAGE_MAX];


	CCMenuItemImage* m_pPlayItem[D_STAGE_MAX];
	//CCMenu* m_pPlay[D_STAGE_MAX];
	CMStyleButton m_pPlay[D_STAGE_MAX];

	CCSprite* m_pLock[D_STAGE_MAX];

	
	CMStyleButton m_pReset;
	CMStyleButton m_pNext;
	CMStyleButton m_pBack;
/*
	CCMenuItemImage* m_pBackItem;
	CCMenu* m_pBack;

	CCMenuItemImage* pResetItem;
	CCMenu* pReset;
	
	CCMenuItemImage* pNextItem;
	CCMenu* pNext;*/

	float m_fTimer;
	float m_fLightTimer;

	float m_fScroll_Y_Vector; //!< 스크롤변화량
	float m_fScroll_Y_All; //!< 총변화량
	float m_fScroll_Y_Smooth;
	float m_fStart_Y;

public:
	void SaveStage();
	void LoadStage();

	void		BackCallback(CCObject* pSender);
public:
	void ShowUpdateLock();
	
    void ResetCallback(CCObject* pSender);
    void NextCallback(CCObject* pSender);

	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void EasyCallback(CCObject* pSender);

    void CancelCallback(CCObject* pSender);

    LAYER_CREATE_FUNC(StageMenuScene);

    void Update(float dt);

	void StageCallBack(int nStage);
/*
	void StageCallback1(CCObject* pSender);
	void StageCallback2(CCObject* pSender);
	void StageCallback3(CCObject* pSender);
	
	void StageCallback4(CCObject* pSender);
	void StageCallback5(CCObject* pSender);
	void StageCallback6(CCObject* pSender);
	
	void StageCallback7(CCObject* pSender);
	void StageCallback8(CCObject* pSender);
	void StageCallback9(CCObject* pSender);
	
	void StageCallback10(CCObject* pSender);
	void StageCallback11(CCObject* pSender);
	void StageCallback12(CCObject* pSender);

	void StageCallback13(CCObject* pSender);
	void StageCallback14(CCObject* pSender);
	void StageCallback15(CCObject* pSender);
	
	void StageCallback16(CCObject* pSender);
	void StageCallback17(CCObject* pSender);
	void StageCallback18(CCObject* pSender);

	void StageCallback19(CCObject* pSender);
	void StageCallback20(CCObject* pSender);
	void StageCallback21(CCObject* pSender);
*/
	virtual void  registerWithTouchDispatcher();

	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
};
