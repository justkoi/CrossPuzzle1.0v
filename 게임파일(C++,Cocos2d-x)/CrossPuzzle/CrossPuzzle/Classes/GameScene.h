#pragma once

#include "stdafx.h"

USING_NS_CC;

typedef enum
{
	E_BLOCKACT_NONE,
	E_BLOCKACT_MOVE,
	E_BLOCKACT_DRAG,
	E_BLOCKACT_NOT
}E_BLOCKACT;

typedef enum
{
	E_GAMERESULT_NONE,
	E_GAMERESULT_VICTORY,
	E_GAMERESULT_DEFEAT,

}E_GAMERESULT;

typedef enum
{
	E_GAMESTEP_READY,
	E_GAMESTEP_PLAY,
	E_GAMESTEP_END,

}E_GAMESTEP;

typedef enum
{
	E_PLAYSTEP_BLOCKSET,
	E_PLAYSTEP_PLAY,
	E_PLAYSTEP_BLOCKALPHA,
	E_PLAYSTEP_BLOCKPOP,
	E_PLAYSTEP_BLOCKPOPLINE,
	E_PLAYSTEP_BLOCKPOPITEM,
	E_PLAYSTEP_BLOCKPOPSET,

}E_PLAYSTEP;

typedef struct stParticleTimer
{
	float m_fTargetTime;
	float m_fTime;
	CCParticleSystem *emitter3;
	stParticleTimer(float fTargetTime, float fTime, CCParticleSystem * emitter)
	{
		m_fTargetTime = fTargetTime;
		m_fTime = fTime;
		emitter3 = emitter;
	};
}stParticleTimer;


class GameScene : public cocos2d::CCLayer
{
public:

	bool m_bChangeScene;
	//!< ������ Vector
	vector<stVec2i> m_Item_Lightning; //!< ������ ����Ʈ��
	vector<stVec2i> m_Item_Bomb; //!< ������ ��
	vector<stVec2i> m_Item_Space; //!< ������ �����̽�

	vector<CDot*> m_Block_PopPoint; //!< ���� ��ϸ���Ʈ�� �߾��� size�� ���������� �ȴ�

	vector<stParticleTimer*> m_ParticleList; //!< ��ƼŬ�� ��Ƽ� ����
	
	bool m_bFillBlockCheck; //!< ����ִ°��� ������ ����� ������� üũ

	CCSprite* m_pBackGround[4]; //!< ��� �� UI�������̽�

	CCSprite* m_pBlind; //!< ����ε� ���
	
	CCSprite* m_pPause; //!< �Ͻ����� ȭ��
	
	CCSprite* m_pReady; //!< Ready Sprite
	CCSprite* m_pGo; //!< Go Sprite

	
	CCSprite* m_pFevergauge; //!< �ǹ������� Sprite
	CCSprite* m_pFeverOn; //!< �ǹ��� On�������� Sprite

	CCLabelTTF* m_pTwittMsg;
	CCSprite* m_pTwittMsg_Bg; //!< Ʈ���� �޼��� ���


	float m_fFeverTimer; //!< �ǹ� Timer
	
	float m_fFeverSmooth; //!< �ǹ� Smooth
	

	float		m_fTimer; //!< ��������ð�
	float		m_fReadyTimer; //!< ReadyTimer

	E_GAMERESULT m_eGameResult; //!< ���� ���
	E_GAMESTEP m_eGameStep; //!< ���� ����
	E_PLAYSTEP m_ePlayStep; //!< �÷��� ���� ����


	int m_nStartLineStep; //!< �������� ���� �� ��
	float m_fStartLineTimer;//!< �������� ���� �� Ÿ�̸�
	float m_fStartLineTime;//!< �������� ���� �� ���޽ð�

	int m_nPopStep; //!< ��Ʈ���� �ܰ�

	CNumber m_NumberPopStep; //!< ��Ʈ���� �ܰ� ����
	CNumber m_NumberScore; //!< ����ǥ��
	CNumber m_NumberTargetScore; //!< ��ǥ����ǥ��

	int m_nActPoint;
	CNumber m_NumberActPoint;//!< �ൿ�� ǥ��
	CNumber m_NumberStage;//!< �������� ǥ��

	int	m_nFocusBlock; //!< ���� ��Ŀ�̵� ���
	int m_nTargetScore; //!< ��ǥ ����

	float m_fPopTimer; //!< �� ��� Ÿ�̸�

	bool m_bPoped; //!< �����°�? �������°�?

	CCSprite* m_pPopTimer; //!< �� ��� ȿ�� ���ڰ��� 90�� ���ư���

	

	CCSprite* m_pGameOver; //!< ���� ���� â
	CCSprite* m_pGameClear; //!< ���� Ŭ���� â
	

	//CMStyleButton m_pRetry;
	//CMStyleButton m_pNext;
	CMStyleButton m_pResume;
	CMStyleButton m_pPauseButton;
	//CMStyleButton m_pMenu;

	
	CCMenuItemImage* m_pMenuItem;
	CCMenu* m_pMenu;

	CCMenuItemImage* m_pRetryItem;
	CCMenu* m_pRetry;

	CCMenuItemImage* m_pNextItem;
	CCMenu* m_pNext;
	
	/*
	CCMenuItemImage* m_pResumeItem;
	CCMenu* m_pResume;
	
	CCMenuItemImage* m_pPauseItem;
	CCMenu* m_pPauseButton;*/

	int	m_nPopBlockNumber; //!< ��̻�𿩾� �����°�?

	float m_fPopDelayTimer;
	
	float m_fPopLineTimer;
	int m_nPopLoopCount;

	float m_fGameOverTimer;

	int m_nTwittLoopCount;
public:
	void		Pause();
	void		Resume();

	void PauseCallBack(CCObject* pSender);
	void ResumeCallBack(CCObject* pSender);
	//!< JNI C++ -> Java ȣ�� ����
	
	
	void		Explosion(CCPoint CPos, E_BLOCKNUMBER eBlockNumber);
	void		Fire(CCPoint CPos);

	void		SaveStage();
	void		LoadStage();



	void		CreateBlock(int nX, int nY);
	void		CreateLine();


	void		BackCallback(CCObject* pSender);

	void		MenuCallback(CCObject* pSender);
	void		RetryCallback(CCObject* pSender);
	void		NextCallback(CCObject* pSender);

public:

	void		SelectReset();
	void		SelectBlock(stVec2i stBlockIndex);
	int			SearchBlockIndex(stVec2i stBlockIndex);
	void		UnSelectBlock(stVec2i stBlockIndex);
	
	void		PopCheck();
	void		PopBlock(stVec2i stBlockIndex);
	void		PopBlock(int nIndex);
	
	CBlock*		SearchBlock(stVec2i stBlockIndex); //!< ����� ã�Ƽ� Return;

	void		FillBlockCheck();
	bool		FillBlockEnd();
public:
	void DestroyScene(); //!< �� ����� ȣ�� ��� �޸� ����
	void DeleteParticleUpdate(float dt);

	bool ItemNothing();

	void Logic_StartLine(float dt);
	void Logic_BlockUpdate(float dt);
	void Logic_BlockFall();
	void Logic_Pop();
	void Logic_LinePop(); //!< ���ÿ� �ΰ� �̻������� ���� ����� �� ���� ������ ��� ����� ��Ʈ��


	//!< ������
	void Logic_Lightning();
	void Logic_Bomb();
	void Logic_Space();

	

	bool HitTest_LintToLine(CCPoint p1, CCPoint p2, CCPoint p3, CCPoint p4);
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
    LAYER_CREATE_FUNC(GameScene);

    void Update(float dt);

	virtual void  registerWithTouchDispatcher();

	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	



};