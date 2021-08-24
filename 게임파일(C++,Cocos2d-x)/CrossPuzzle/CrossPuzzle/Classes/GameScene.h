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
	//!< 아이템 Vector
	vector<stVec2i> m_Item_Lightning; //!< 아이템 라이트닝
	vector<stVec2i> m_Item_Bomb; //!< 아이템 불
	vector<stVec2i> m_Item_Space; //!< 아이템 스페이스

	vector<CDot*> m_Block_PopPoint; //!< 터진 블록리스트의 중앙점 size는 터진개수가 된다

	vector<stParticleTimer*> m_ParticleList; //!< 파티클을 담아서 해제
	
	bool m_bFillBlockCheck; //!< 비어있는곳에 새로이 블록을 만들건지 체크

	CCSprite* m_pBackGround[4]; //!< 배경 및 UI인터페이스

	CCSprite* m_pBlind; //!< 블라인드 배경
	
	CCSprite* m_pPause; //!< 일시정지 화면
	
	CCSprite* m_pReady; //!< Ready Sprite
	CCSprite* m_pGo; //!< Go Sprite

	
	CCSprite* m_pFevergauge; //!< 피버게이지 Sprite
	CCSprite* m_pFeverOn; //!< 피버가 On됬을때의 Sprite

	CCLabelTTF* m_pTwittMsg;
	CCSprite* m_pTwittMsg_Bg; //!< 트위터 메세지 배경


	float m_fFeverTimer; //!< 피버 Timer
	
	float m_fFeverSmooth; //!< 피버 Smooth
	

	float		m_fTimer; //!< 게임진행시간
	float		m_fReadyTimer; //!< ReadyTimer

	E_GAMERESULT m_eGameResult; //!< 게임 결과
	E_GAMESTEP m_eGameStep; //!< 게임 진행
	E_PLAYSTEP m_ePlayStep; //!< 플레이 루프 순서


	int m_nStartLineStep; //!< 내려오는 시작 줄 수
	float m_fStartLineTimer;//!< 내려오는 시작 줄 타이머
	float m_fStartLineTime;//!< 내려오는 시작 줄 도달시간

	int m_nPopStep; //!< 터트리는 단계

	CNumber m_NumberPopStep; //!< 터트리는 단계 숫자
	CNumber m_NumberScore; //!< 점수표시
	CNumber m_NumberTargetScore; //!< 목표점수표시

	int m_nActPoint;
	CNumber m_NumberActPoint;//!< 행동력 표시
	CNumber m_NumberStage;//!< 스테이지 표시

	int	m_nFocusBlock; //!< 현재 포커싱된 블록
	int m_nTargetScore; //!< 목표 점수

	float m_fPopTimer; //!< 팝 대기 타이머

	bool m_bPoped; //!< 터졌는가? 안터졌는가?

	CCSprite* m_pPopTimer; //!< 팝 대기 효과 십자가가 90도 돌아간다

	

	CCSprite* m_pGameOver; //!< 게임 오버 창
	CCSprite* m_pGameClear; //!< 게임 클리어 창
	

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

	int	m_nPopBlockNumber; //!< 몇개이상모여야 터지는가?

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
	//!< JNI C++ -> Java 호출 구문
	
	
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
	
	CBlock*		SearchBlock(stVec2i stBlockIndex); //!< 블록을 찾아서 Return;

	void		FillBlockCheck();
	bool		FillBlockEnd();
public:
	void DestroyScene(); //!< 씬 종료시 호출 모든 메모리 해제
	void DeleteParticleUpdate(float dt);

	bool ItemNothing();

	void Logic_StartLine(float dt);
	void Logic_BlockUpdate(float dt);
	void Logic_BlockFall();
	void Logic_Pop();
	void Logic_LinePop(); //!< 동시에 두개 이상터져서 선이 생기고 그 선을 지나는 모든 블록을 터트림


	//!< 아이템
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