#include "stdafx.h"

USING_NS_CC;

CMap	g_Map; //!< 맵 0과 1로 체크 동적할당
CBlock g_BlockList[D_BLOCKMAP_MAX]; //!< 모든 블록 동적할당
int	g_nBlockMax; //!< 최대 블록 수
CEffectManager g_EffectManager;
CEffectManager g_LineManager;
CPlaneManager g_PlaneManager;
CNumberManager g_NumberManager;
CComboManager g_ComboManager;
int g_nScore = 0; //!< 점수
int g_nCombo = 0; //!< 콤보

int g_nStage = 1; //!< 스테이지

float g_fFevergauge = 0.0f; //!< 피버게이지 100이 최대 콤보마다 10씩 차오름 우선
bool g_bFever = false; //!< 피버 모드 true false
 
bool g_bPause = false; //!< 일시정지 여부
bool g_bBGM_Sound = true;
bool g_bEFFECT_Sound = true;

CCSize g_PhoneSize;

CCScene* GameScene::scene()                                                                                                                                                                                                                                                                                                                                                                
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float GameScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float GameScene::ReturnHeight(float fValue)
{
	//LogoScene* Logo = this;

	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}


void GameScene::SaveStage()
{
	char strFilePath[256];
	sprintf(strFilePath,"stagelock_%d.sav",g_nLevel);
	CCFileUtils FileUitil;
	string strTemp = FileUitil.getWriteablePath();
	strTemp.append(strFilePath);

	FILE* fpw = fopen(strTemp.c_str(),"wb");
	
	
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		fwrite(&g_bStageLock[i],sizeof(bool),1,fpw);
	}

	fclose(fpw);
}


void GameScene::LoadStage()
{
	char strFilePath[256];
	sprintf(strFilePath,"stagelock_%d.sav",g_nLevel);
	CCFileUtils FileUitil;
	string strTemp = FileUitil.getWriteablePath();
	strTemp.append(strFilePath);

	FILE* fpr = fopen(strTemp.c_str(),"rb");
	
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		fread(&g_bStageLock[i],sizeof(bool),1,fpr);
	}
	
	fclose(fpr);
}


void GameScene::CreateBlock(int nX, int nY)
{
	for(int i=0; i<g_nBlockMax; i++)
	{
		if(g_BlockList[i].m_bLive == true)
			continue;

		g_BlockList[i].Create(stVec2i(nX,nY));
		g_Map.m_nBlockMap[nY][nX] = 1;
		break;
	}
}

void GameScene::CreateLine()
{
	for(int i=0; i<D_BLOCKMAP_WIDTH; i++)
	{
		CreateBlock(i,0);
	}
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	m_bChangeScene = false;


	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();
	
	g_bFirstPlayed = false;

	g_EffectManager.Init(this);
	g_LineManager.Init(this);
	g_PlaneManager.Init(this);
	g_NumberManager.Init(this);
	g_ComboManager.Init(this);

	m_nTwittLoopCount = 0;


	m_fGameOverTimer = 0.0f;
	g_bFever = true;
	m_fPopTimer = 0.0f;
	m_fPopDelayTimer = 0.0f;
	m_nPopLoopCount = D_POP_LOOP;
	g_fFevergauge = 0.0f;
	m_fFeverSmooth = 0.0f;
	m_nPopBlockNumber = 4; //!< 몇개이상 터지는가
	g_nScore = 0;
	this->setTouchEnabled(true); //!< 터치 사용 가능
	m_fTimer = 0.0f;
	m_nFocusBlock = 0;

	m_nActPoint = g_StageInfo[g_nLevel-1][g_nStage-1].m_nActPoint;
	m_nTargetScore = g_StageInfo[g_nLevel-1][g_nStage-1].m_nTargetScore;


	m_eGameStep = E_GAMESTEP_READY;
	m_eGameResult = E_GAMERESULT_NONE;
	m_ePlayStep = E_PLAYSTEP_BLOCKPOP;


	g_Map.Init(); //!< 맵 요소 0 으로 초기화.

	g_nBlockMax = D_BLOCKMAP_WIDTH * D_BLOCKMAP_HEIGHT;

		
	for(int i=0; i<g_nBlockMax; i++)
	{
		g_BlockList[i].Init(this, i);
	}


	//!< 라벨을 만듭니다. (텍스트내용,글씨체,글씨크기)
	m_pTwittMsg = CCLabelTTF::create("[CrossPuzzle] <Normal> 10Stage Clear!", "돋움체", 18);
	//!< 위치설정
	m_pTwittMsg->setPosition(ccp( 266 * D_SCALE_WIDTH , 150 * D_SCALE_HEIGHT));
	//!< 색깔설정
	m_pTwittMsg->setColor(ccc3(0,0,0));
	m_pTwittMsg->setOpacity(255 * 0.0f);
	m_pTwittMsg->setVisible(false);
	//!< 등록
	this->addChild(m_pTwittMsg,41);
	//!<PC버전에서 라벨의 뒷배경색과 글씨색이 같아서 보이지 않는 에러가 있습니다.
	//!< 고치는법을 모르겠지만 폰에서는 잘 구동됩니다.

	m_pTwittMsg_Bg = CCSprite::create("TwittMsg.png");
	m_pTwittMsg_Bg->setPosition( ccp( 240 * D_SCALE_WIDTH, 150  * D_SCALE_HEIGHT) );
	m_pTwittMsg_Bg->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pTwittMsg_Bg->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pTwittMsg_Bg->setOpacity(255 * 0.0f);
	m_pTwittMsg_Bg->setVisible(false);
	this->addChild(m_pTwittMsg_Bg, 40);


	char strFilePath[256];
	sprintf(strFilePath,"Game_BackGround_1_%d.png",g_nLevel);
	//!< 게임 배경이미지 (1) 뒷배경 (2) 블라인드 (3) 인터페이스 ///////////////////////////////////////////////////////////////////////////////////

	m_pBackGround[0] = CCSprite::create(strFilePath);
	m_pBackGround[0]->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGround[0]->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGround[0]->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBackGround[0]->setColor(ccc3(255 * 1.0f, 255 * 1.0f, 255 * 1.0f));
	this->addChild(m_pBackGround[0], 0);

	m_pBackGround[1] = CCSprite::create("Game_BackGround_2.png");
	m_pBackGround[1]->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGround[1]->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGround[1]->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pBackGround[1]->setVisible(false);
	//m_pBackGround[1]->setColor(ccc3(255 * 0.3f, 255 * 0.3f, 255 * 0.3f));
	m_pBackGround[1]->setOpacity(255 * 0.5f); //!< DevOption
	this->addChild(m_pBackGround[1], 20);

	
	m_pBackGround[2] = CCSprite::create("Game_BackGround_3.png");
	m_pBackGround[2]->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGround[2]->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGround[2]->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pBackGround[2]->setColor(ccc3(255 * 0.0f, 255 * 0.0f, 255 * 0.0f));
	this->addChild(m_pBackGround[2], 31);

	
	
	m_pBackGround[3] = CCSprite::create("Game_BackGround_4.png");
	m_pBackGround[3]->setPosition( ccp( -2400 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(35.0f)  * D_SCALE_HEIGHT) );
	m_pBackGround[3]->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGround[3]->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBackGround[3]->setAnchorPoint(ccp(0.5f,1.0f));
	//m_pBackGround[2]->setColor(ccc3(255 * 0.0f, 255 * 0.0f, 255 * 0.0f));
	//m_pBackGround[3]->setTextureRect(CCRect(0,35,480,115));
	this->addChild(m_pBackGround[3], 32);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	//!< 팝 대기 타이머

	m_pPopTimer = CCSprite::create("PopTimer1.png");
	m_pPopTimer->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pPopTimer->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pPopTimer->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pPopTimer->setVisible(false);
	this->addChild(m_pPopTimer, 25);

	///////////////////////////////////
	m_NumberPopStep.Init(this,ccp(1.0f * D_SCALE_WIDTH,1.0f * D_SCALE_HEIGHT),0,ccp(0 * D_SCALE_WIDTH,0  * D_SCALE_HEIGHT),26);
	m_NumberPopStep.SetVisible(false);

	
	m_NumberStage.Init(this,ccp(1.0f * D_SCALE_WIDTH,1.0f * D_SCALE_HEIGHT),g_nStage,ccp(396 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(70)  * D_SCALE_HEIGHT),33);
	//m_NumberStage.SetColor(ccc3(255 * 1.0f, 255 * 1.0f, 255 * 1.0f));
	m_NumberScore.Init(this,ccp(0.65f * D_SCALE_WIDTH,0.65f * D_SCALE_HEIGHT),0,ccp(115 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(50)  * D_SCALE_HEIGHT),33);
	m_NumberTargetScore.Init(this,ccp(0.65f * D_SCALE_WIDTH,0.65f * D_SCALE_HEIGHT),0,ccp(100 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(80)  * D_SCALE_HEIGHT),33);
	//m_NumberTargetScore.SetColor(ccc3(255 * 0.0f, 255 * 0.0f, 255 * 1.0f));
	// m_NumberCombo.Init(this,ccp(1.0f,1.0f),0,ccp(240 * D_SCALE_WIDTH,  D_PHOTOSHOP_Y(765)  * D_SCALE_HEIGHT),31);
	m_NumberActPoint.Init(this,ccp(1.0f * D_SCALE_WIDTH,1.0f * D_SCALE_HEIGHT),0,ccp(255 * D_SCALE_WIDTH,  D_PHOTOSHOP_Y(77)  * D_SCALE_HEIGHT),33);
	m_NumberActPoint.SetColor(ccc3(255 * 0.0f, 255 * 0.0f, 255 * 1.0f));

	m_pBlind = CCSprite::create("Blind.png");
	m_pBlind->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBlind->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pBlind->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pBlind->setOpacity(255 * 0.8f);
	m_pBlind->setVisible(false);
    this->addChild(m_pBlind, 39);
	
	m_pPause = CCSprite::create("Pause.png");
	m_pPause->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pPause->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pPause->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pPause->setOpacity(255 * 1.0f);
	m_pPause->setVisible(false);
    this->addChild(m_pPause, 40);
	
	m_pFevergauge = CCSprite::create("Fever.png");
	m_pFevergauge->setTextureRect(CCRect(0,0,g_fFevergauge,40));
	m_pFevergauge->setPosition( ccp( 10 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(35)  * D_SCALE_HEIGHT) );
	m_pFevergauge->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pFevergauge->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pFevergauge->setVisible(true);
	m_pFevergauge->setAnchorPoint(ccp(0,0.5f));
   // this->addChild(m_pFevergauge, 32);
	
	m_pFeverOn = CCSprite::create("FeverOn.png");
	m_pFeverOn->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pFeverOn->setScaleX(1.02f * D_SCALE_WIDTH);
	m_pFeverOn->setScaleY(1.02f * D_SCALE_HEIGHT);
	m_pFeverOn->setVisible(false);
	m_pFeverOn->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(m_pFeverOn, 36);
	



	m_pGameOver = CCSprite::create("PopUp_StageFail.png");
	m_pGameOver->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pGameOver->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pGameOver->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pGameOver->setVisible(false);
    this->addChild(m_pGameOver, 40);





	//m_pRetry.Init(this,41,"Button_Retry_1.png","Button_Retry_3.png",ccp(290 * D_SCALE_WIDTH, 365 * D_SCALE_HEIGHT));
	//m_pNext.Init(this,41,"Button_Next_1.png","Button_Next_3.png",ccp(290 * D_SCALE_WIDTH, 365 * D_SCALE_HEIGHT));
	m_pResume.Init(this,41,"Button_Resume_1.png","Button_Resume_3.png",ccp(360 * D_SCALE_WIDTH, 500 * D_SCALE_HEIGHT));
	m_pPauseButton.Init(this,33,"Button_Pause_1.png","Button_Pause_3.png",ccp(442 * D_SCALE_WIDTH, 700 * D_SCALE_HEIGHT));
	//m_pMenu.Init(this,41,"Button_Menu_1.png","Button_Menu_3.png",ccp(190 * D_SCALE_WIDTH, 365 * D_SCALE_HEIGHT));
	
	//m_pMenu.setVisible(false);
	//m_pNext.setVisible(false);
	//m_pRetry.setVisible(false);
	m_pResume.setVisible(false);


	
	
	m_pMenuItem = CCMenuItemImage::create(
                                        "Button_Menu_1.png",
                                        "Button_Menu_3.png",
                                        this,
                                        menu_selector(GameScene::MenuCallback) );
	m_pMenuItem->setPosition( CCPointZero );
    // create menu, it's an autorelease object
    m_pMenu = CCMenu::create(m_pMenuItem, NULL);
	m_pMenu->setPosition( ccp(ReturnWidth(190) * D_SCALE_WIDTH, ReturnHeight(365) * D_SCALE_HEIGHT) );
	m_pMenu->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pMenu->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pMenu->setAnchorPoint(ccp(0.5f,0.5f));
	m_pMenu->setVisible(false);
    this->addChild(m_pMenu, 41);


	m_pRetryItem = CCMenuItemImage::create(
                                        "Button_Retry_1.png",
                                        "Button_Retry_3.png",
                                        this,
                                        menu_selector(GameScene::RetryCallback) );
	m_pRetryItem->setPosition( CCPointZero );
    // create menu, it's an autorelease object
    m_pRetry = CCMenu::create(m_pRetryItem, NULL);
	m_pRetry->setPosition( ccp(ReturnWidth(290)  * D_SCALE_WIDTH, ReturnHeight(365) * D_SCALE_HEIGHT ) );
	m_pRetry->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pRetry->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pRetry->setAnchorPoint(ccp(0.5f,0.5f));
	m_pRetry->setVisible(false);
    this->addChild(m_pRetry, 41);
	
	m_pNextItem = CCMenuItemImage::create(
                                        "Button_Next_1.png",
                                        "Button_Next_3.png",
                                        this,
                                        menu_selector(GameScene::NextCallback) );
	m_pNextItem->setPosition( CCPointZero );
    // create menu, it's an autorelease object
    m_pNext = CCMenu::create(m_pNextItem, NULL);
	m_pNext->setPosition(  ccp(ReturnWidth(290), ReturnHeight(365) ));
	m_pNext->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pNext->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pNext->setAnchorPoint(ccp(0.5f,0.5f));
	m_pNext->setVisible(false);
    this->addChild(m_pNext, 41);

	//
	//m_pResumeItem = CCMenuItemImage::create(
 //                                       "Button_Resume_1.png",
 //                                       "Button_Resume_3.png",
 //                                       this,
 //                                       menu_selector(GameScene::ResumeCallBack) );
	//m_pResumeItem->setPosition(CCPointZero );
 //   // create menu, it's an autorelease object
 //   m_pResume = CCMenu::create(m_pResumeItem, NULL);
	//m_pResume->setPosition(  ccp(ReturnWidth(360)  * D_SCALE_WIDTH, ReturnHeight(500) * D_SCALE_HEIGHT ) );
	//m_pResume->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pResume->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pResume->setAnchorPoint(ccp(0.5f,0.5f));
	//m_pResume->setVisible(false);
 //   this->addChild(m_pResume, 41);
	//
	//m_pPauseItem = CCMenuItemImage::create(
 //                                       "Button_Pause_1.png",
 //                                       "Button_Pause_3.png",
 //                                       this,
 //                                       menu_selector(GameScene::PauseCallBack) );
	//m_pPauseItem->setPosition( ccp(ReturnWidth(442), ReturnHeight(700) ) );
 //   // create menu, it's an autorelease object
 //   m_pPauseButton = CCMenu::create(m_pPauseItem, NULL);
	//m_pPauseButton->setPosition( CCPointZero );
	//m_pPauseButton->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pPauseButton->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pPauseButton->setAnchorPoint(ccp(0.5f,0.5f));
	//m_pPauseButton->setVisible(true);
 //   this->addChild(m_pPauseButton, 33);

	



     
	m_pGameClear = CCSprite::create("PopUp_StageClear.png");
	m_pGameClear->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pGameClear->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pGameClear->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pGameClear->setVisible(false);
    this->addChild(m_pGameClear, 40);


	
	

	m_pReady = CCSprite::create("Ready.png");
	m_pReady->setPosition( ccp( 240 * D_SCALE_WIDTH, 900  * D_SCALE_HEIGHT) );
	m_pReady->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pReady->setScaleY(1.0f * D_SCALE_HEIGHT);
    this->addChild(m_pReady, 33);

	m_pGo = CCSprite::create("Go.png");
	m_pGo->setPosition( ccp( 240 * D_SCALE_WIDTH, 900  * D_SCALE_HEIGHT) );
	m_pGo->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pGo->setScaleY(1.0f * D_SCALE_HEIGHT);
    this->addChild(m_pGo, 33);

	m_fFeverTimer = 0.0f;

	
	m_fStartLineTimer = 0.0f;
	m_nStartLineStep = 0;
	m_fStartLineTime = 0.5f;

	m_nPopStep = 0;

	m_fReadyTimer = 0.0f;

	m_fPopLineTimer = 0.0f;
	
	g_bPause = false;
	m_bFillBlockCheck = false;

	//D_SOUNDMNG->setBackgroundMusicVolume(0.7f);
	

	D_SOUNDMNG->preloadBackgroundMusic("Game_BGM_1.mp3");
	if(g_bBGM_Sound == true)
	{
		D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		D_SOUNDMNG->playBackgroundMusic("Game_BGM_1.mp3", true);
	}

	


	//
	//CCParticleSystem *emitter3;
	//emitter3 = CCParticleGalaxy::node();
 //   emitter3->setTexture(CCTextureCache::sharedTextureCache()->addImage("Particle1.png"));
	//emitter3->setTotalParticles(150);
 //   emitter3->setAutoRemoveOnFinish(true);
	//emitter3->setLife(5.0f);
	//emitter3->setLifeVar(2.5f);
	//emitter3->setPosition(ccp( 240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	//emitter3->setGravity(ccp(0,0));
	//emitter3->setStartColor(ccc4f(1.0f, (1.0f/255) * 165, 1.0f, 1.0f));
	//emitter3->setEndColor(ccc4f(1.0f, (1.0f/255) * 165, 1.0f, 0.0f));
	////emitter->setRotatePerSecond(10.0f);
	////emitter->setRotatePerSecondVar(20.0f);
	//emitter3->setScale(1.0f);
 //   emitter3->setStartSize(15.0f);
 //   emitter3->setEndSize(15.0f);
 //   emitter3->setDuration(600.0f);
 //   emitter3->setSpeed(200);
 //   emitter3->setSpeedVar(100);
	////emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	//emitter3->setEmissionRate(250.0f);
	////emitter->setAngle(0.0f);
	////emitter->setAngleVar(360.0f);
 //   this->addChild(emitter3);

	this->schedule(schedule_selector(GameScene::Update), 0.0);


    return true;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == popCC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::Update(float dt)
{
	m_fTimer += dt;

	if(m_bChangeScene == false)
	{
		//m_pRetry.Update(dt);
		//m_pNext.Update(dt);
		m_pResume.Update(dt);
		m_pPauseButton.Update(dt);
		//m_pMenu.Update(dt);


		/*if(m_pRetry.CheckAction() == true)
		{
			m_pRetry.CheckActioned();
			RetryCallback(NULL);
			m_bChangeScene = true;
		}
		if(m_pNext.CheckAction() == true)
		{
			m_pNext.CheckActioned();
			NextCallback(NULL);
			m_bChangeScene = true;
		}*/
		if(m_pResume.CheckAction() == true)
		{
			m_pResume.Reset();
			ResumeCallBack(NULL);
		}
		if(m_pPauseButton.CheckAction() == true)
		{
			m_pPauseButton.Reset();
			PauseCallBack(NULL);
		}
		/*if(m_pMenu.CheckAction() == true)
		{
			m_pMenu.CheckActioned();
			MenuCallback(NULL);
			m_bChangeScene = true;
		}*/
	}

	if(g_bPause == false)
	{
		
		switch(m_eGameStep)
		{
		
		case E_GAMESTEP_READY:

			if(m_fTimer >= 0.5f)
				m_fReadyTimer += dt;

			Logic_StartLine(dt);
			Logic_BlockUpdate(dt);
			Logic_BlockFall();

			if(m_fReadyTimer <= 1.0f)
			{
				m_pReady->setPositionY( ((900 ) - (m_fReadyTimer * 500)) * D_SCALE_HEIGHT);
				m_pReady->setScaleX((m_fReadyTimer+0.2f) * D_SCALE_WIDTH);
				m_pReady->setScaleY((m_fReadyTimer+0.2f) * D_SCALE_HEIGHT);
			}

			else if(m_fReadyTimer <= 2.0f)
			{
				m_pReady->setOpacity(255 * (1.0f - (m_fReadyTimer - 1.0f)));
				m_pReady->setScaleX((1.2f - (m_fReadyTimer - 1.0f)) * D_SCALE_WIDTH);
				m_pReady->setScaleY((1.2f - (m_fReadyTimer - 1.0f)) * D_SCALE_HEIGHT);
				
				m_pGo->setPositionY( ((900 ) - ((m_fReadyTimer - 1.0f) * 500)) * D_SCALE_HEIGHT);
				//m_pGo->setPositionX( ((-100) + ((m_fReadyTimer - 1.0f) * 340)) * D_SCALE_WIDTH);
				
				m_pGo->setScaleX(((m_fReadyTimer - 1.0f) + 0.2f) * D_SCALE_WIDTH);
				m_pGo->setScaleY(((m_fReadyTimer - 1.0f) + 0.2f) * D_SCALE_HEIGHT);
			}

			else if(m_fReadyTimer <= 3.0f)
			{
				m_pGo->setOpacity(255 * (1.0f - (m_fReadyTimer - 2.0f)));
				m_pGo->setScaleX((1.2f - (m_fReadyTimer - 2.0f)) * D_SCALE_WIDTH);
				m_pGo->setScaleY((1.2f - (m_fReadyTimer - 2.0f)) * D_SCALE_HEIGHT);
			}
			

			break;
		case E_GAMESTEP_PLAY:
			m_fFeverTimer += dt;

			if(m_fFeverTimer >= 2.0f)
				m_fFeverTimer = 0.0f;

			g_EffectManager.Update(dt);
			g_LineManager.Update(dt);
			g_PlaneManager.Update(dt);
			g_NumberManager.Update(dt);
			g_ComboManager.Update(dt, g_nCombo);

			if(g_ComboManager.m_bPlayEffect == true)
			{
				if(g_bEFFECT_Sound == true)
				{
					D_SOUNDMNG->playEffect("Combo.mp3");
				}
				g_ComboManager.m_bPlayEffect = false;
			}

			m_pPopTimer->setRotation((m_fPopTimer/D_POPTIME_MAX) * 90.0f);

			m_NumberScore.Update(dt);
			m_NumberTargetScore.Update(dt);

			m_pFeverOn->setVisible(g_bFever);

			if(m_fFeverTimer <= 1.0f)
			{
				m_pFeverOn->setOpacity(255 * m_fFeverTimer);
			}
			else if(m_fFeverTimer <= 2.0f)
			{
				m_pFeverOn->setOpacity(255 * (2.0f - m_fFeverTimer));
			}
			                 
			if( g_fFevergauge >= 0.0f)
			{
				m_fFeverSmooth += g_fFevergauge * dt;
				g_fFevergauge -= g_fFevergauge * dt;

				m_fFeverSmooth += 3.0f * dt;
				g_fFevergauge -= 3.0f * dt;
				if(g_fFevergauge <= 0)
				{
					m_fFeverSmooth += g_fFevergauge;
					g_fFevergauge = 0;
				}
				if(m_fFeverSmooth >= 100.0f)
					m_fFeverSmooth = 100.0f;
			}

			m_pBackGround[3]->setTextureRect(CCRect(0,110 - (0.75f * m_fFeverSmooth),480,110));
			m_pBackGround[3]->setPosition( ccp( 240 * D_SCALE_WIDTH, D_PHOTOSHOP_Y((110 - (0.75f * m_fFeverSmooth)))  * D_SCALE_HEIGHT) );
			//m_pFevergauge->setTextureRect(CCRect(0,0,m_fFeverSmooth*4,40));

			//m_pBackGround[3]->setTextureRect(CCRect(0,85,480,110));
			//m_pBackGround[3]->setTextureRect(CCRect(0,55,480,115));
			//m_pBackGround[3]->setPosition( ccp( 240 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(85)  * D_SCALE_HEIGHT) );
			

			m_NumberActPoint.Update(dt);
			
			m_NumberScore.EffectNumber(g_nScore);
			m_NumberTargetScore.EffectNumber(m_nTargetScore);
			// m_NumberCombo.SetNumber(g_nCombo);
			m_NumberActPoint.SetNumber(m_nActPoint);
			m_NumberActPoint.SetColor(ccc3(255 * 0.0f, 255 * 0.0f, 255 * 1.0f));

			m_NumberPopStep.Update(dt);
			Logic_BlockUpdate(dt);

			
			// printf("PlayStep(%d) ",int(m_ePlayStep));
			if(m_ePlayStep == E_PLAYSTEP_PLAY)
			{
				if(m_fFeverSmooth >= 100.0f)
				{
					m_fFeverSmooth = 0.0f;
					g_fFevergauge = 0.0f;
					g_bFever = true;
					if(g_bEFFECT_Sound == true)
					{
						 
						D_SOUNDMNG->playEffect("Fever.mp3");
					}
				}
				
				// !< DevOption Logic_BlockFall();
			
				//!< 게임 승패조건 탐색
				if( m_nActPoint <= 0 )
				{
					if( g_nScore < m_nTargetScore )
					{
						m_eGameResult = E_GAMERESULT_DEFEAT;
						m_pGameOver->setVisible(true);
						m_pRetry->setVisible(true);
						if(g_bEFFECT_Sound == true)
						{
							D_SOUNDMNG->playEffect("Over.mp3");
						}
					}
					else if( g_nScore >= m_nTargetScore )
					{
						m_eGameResult = E_GAMERESULT_VICTORY;
						m_pGameClear->setVisible(true);

						if(g_nStage != D_STAGE_MAX)
							g_bStageLock[g_nStage] = true;
						SaveStage();
						m_pNext->setVisible(true);
						if(g_bEFFECT_Sound == true)
						{
							D_SOUNDMNG->playEffect("Clear.mp3");
						}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		

		

		char strTMsg[256];
		if(g_nLevel == 1)
		{
			sprintf(strTMsg,"[CrossPuzzle] <Easy> %dStage Clear!",g_nStage);
		}
		else if(g_nLevel == 2)
		{
			sprintf(strTMsg,"[CrossPuzzle] <Normal> %dStage Clear!",g_nStage);
		}
		else if(g_nLevel == 3)
		{
			sprintf(strTMsg,"[CrossPuzzle] <Hard> %dStage Clear!",g_nStage);
		}
		m_pTwittMsg->setString(strTMsg);
		m_pTwittMsg->setVisible(true);
		m_pTwittMsg_Bg->setVisible(true);
		m_nTwittLoopCount = 1;
	}
#endif
					}

					m_pBlind->setVisible(true);
					m_pMenu->setVisible(true);
					m_eGameStep = E_GAMESTEP_END;
					g_ComboManager.Exit();

				}
				else
				{
					if( g_nScore >= m_nTargetScore )
					{
						m_eGameResult = E_GAMERESULT_VICTORY;
						m_pGameClear->setVisible(true);
						m_pBlind->setVisible(true);
						m_pMenu->setVisible(true);
						m_pNext->setVisible(true);
						m_eGameStep = E_GAMESTEP_END;
						g_ComboManager.Exit();

						if(g_nStage != D_STAGE_MAX)
							g_bStageLock[g_nStage] = true;
						SaveStage();
						if(g_bEFFECT_Sound == true)
						{
							D_SOUNDMNG->playEffect("Clear.mp3");
						}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		

		

		char strTMsg[256];
		if(g_nLevel == 1)
		{
			sprintf(strTMsg,"[CrossPuzzle] <Easy> %dStage Clear!",g_nStage);
		}
		else if(g_nLevel == 2)
		{
			sprintf(strTMsg,"[CrossPuzzle] <Normal> %dStage Clear!",g_nStage);
		}
		else if(g_nLevel == 3)
		{
			sprintf(strTMsg,"[CrossPuzzle] <Hard> %dStage Clear!",g_nStage);
		}
		m_pTwittMsg->setString(strTMsg);
		m_pTwittMsg->setVisible(true);
		m_pTwittMsg_Bg->setVisible(true);
		m_nTwittLoopCount = 1;
	}
#endif
					}
				}

				

				//!< 게임 플레이 타이머 확인
				if(m_nPopStep > 0)
				{
					m_fPopTimer += dt;
					if(m_fPopTimer >= D_POPTIME_MAX) //!< 팝 타이머 완료
					{
						m_fPopTimer = 0.0f;

						PopCheck();//!< 선택된 블록을 찾아서 알파값감소단계 돌입
						m_nPopStep = 0;
						m_nActPoint--;
						m_NumberPopStep.SetVisible(false);
						m_pPopTimer->setVisible(false);
						m_ePlayStep = E_PLAYSTEP_BLOCKALPHA;
						m_bFillBlockCheck = false;
						// FillBlockCheck();
						// printf("PlayStep(%d) ",int(m_ePlayStep));
					}
				}

			}
			else if(m_ePlayStep == E_PLAYSTEP_BLOCKALPHA)
			{
				for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
				{
					if( g_BlockList[nBlock].m_bLive == true && g_BlockList[nBlock].m_fNowAlpha <= 0.0f)
					{
						g_BlockList[nBlock].Die();
						g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
					}
				}
				int nBlock2 = 0;
				for( nBlock2 = 0; nBlock2 < g_nBlockMax; nBlock2++)
				{
					if( g_BlockList[nBlock2].m_fNowAlpha < 1.0f && g_BlockList[nBlock2].m_bLive == true)
						break;
				}
				if(nBlock2 >= g_nBlockMax)
				{
					if(m_bFillBlockCheck == false)
					{
						m_bFillBlockCheck = true;
						FillBlockCheck();
						m_ePlayStep = E_PLAYSTEP_BLOCKSET;
					}
				}
			}
			else if(m_ePlayStep == E_PLAYSTEP_BLOCKSET)
			{
				Logic_BlockFall();
				if(FillBlockEnd() == true)
				{
					m_ePlayStep = E_PLAYSTEP_BLOCKPOP;
				}
			}
			else if(m_ePlayStep == E_PLAYSTEP_BLOCKPOP)
			{
				Logic_Pop(); //!< 블록 터트리는 로직 갱신

				if(m_Block_PopPoint.size() >= 2) //!< 두개이상의 PopPoint가 남으면 Line으로 보내고
				{
					m_ePlayStep = E_PLAYSTEP_BLOCKPOPLINE;
					m_fPopLineTimer = 0.0f;
				}
				else //!< 그게 아니면 
				{
					vector<CDot*>::iterator it;

					for(it = m_Block_PopPoint.begin(); it != m_Block_PopPoint.end(); )
					{
						if((*it)->m_bItem == false) //!< 아이템이 아니면 지우고
						{
							delete (*it);
							it = m_Block_PopPoint.erase(it);
						}
						else //!< 아이템이면 살린다
						{
							it++;
						}
					}

					m_fPopLineTimer = 0.0f;

					if(ItemNothing() == true) //!< 아이템이 없으면 다시 로직을 돌건지 플레이할건지를 결정하는 빈블록을 채워서 POPSET으로 보내고
					{
						FillBlockCheck();
						m_bFillBlockCheck = true;
						m_ePlayStep = E_PLAYSTEP_BLOCKPOPSET;
					}
					else //!< 아이템이 있으면 아이템으로 보낸다
					{
						m_ePlayStep = E_PLAYSTEP_BLOCKPOPITEM;
					}
				}
				
				
				// printf("PlayStep(%d) ",int(m_ePlayStep));
			}
			else if(m_ePlayStep == E_PLAYSTEP_BLOCKPOPLINE)
			{
				m_fPopLineTimer += dt;

				if(m_fPopLineTimer >= 0.5f) //!< 0.5초의 대기시간후에
				{
					Logic_LinePop(); //!< LinePop을 갱신하고
					if(ItemNothing() == true) //!< 아이템이 없으면 빈블록을 채워서 POPSET으로 보낸다
					{
						FillBlockCheck();
						m_ePlayStep = E_PLAYSTEP_BLOCKPOPSET;
					}
					else //!< 아이템이 있으면 아이템으로 보낸다
					{
						m_ePlayStep = E_PLAYSTEP_BLOCKPOPITEM;
					}
				}
			}
			else if(m_ePlayStep == E_PLAYSTEP_BLOCKPOPITEM)
			{
				m_fPopLineTimer += dt;
				
				if(m_fPopLineTimer >= 0.5f) //!< 0.5초의 대기시간후에 아이템을 빈블록을 채워서 POPSET으로 보낸다
				{
					Logic_Lightning();
					Logic_Bomb();
					Logic_Space();
					FillBlockCheck();
					m_ePlayStep = E_PLAYSTEP_BLOCKPOPSET;
					m_fPopLineTimer = 0.0f;
				}
			}
			else if(m_ePlayStep == E_PLAYSTEP_BLOCKPOPSET)
			{
				m_fPopDelayTimer += dt;

				if(g_EffectManager.m_pEffectList.size() <= 0)
				{
					Logic_BlockFall();

					if(FillBlockEnd() == true)
					{
						if(m_bPoped == false)
						{
							//printf("E_PLAYSTEP_PLAY Enterd\n");
							if(m_nPopLoopCount == 0)
							{
								m_fPopDelayTimer = 0.0f;
								m_ePlayStep = E_PLAYSTEP_PLAY;
								// printf("PlayStep(%d) ",int(m_ePlayStep));
								g_nCombo = 0;
								g_ComboManager.m_nCombo = 0;
								m_nPopLoopCount = D_POP_LOOP;
							}
							else if(m_nPopLoopCount > 0)
							{
								m_fPopDelayTimer = 0.0f;
								m_nPopLoopCount--;
								m_ePlayStep = E_PLAYSTEP_BLOCKPOP;
								//if(g_bFever == true)
									//g_bFever = false;
							}
						}
						else if(m_bPoped == true)
						{
							m_fPopDelayTimer = 0.0f;
							//printf("E_PLAYSTEP_BLOCKPOP Enterd\n");
							m_ePlayStep = E_PLAYSTEP_BLOCKPOP;
							//if(g_bFever == true)
							//	g_bFever = false;
							// printf("PlayStep(%d) ",int(m_ePlayStep));
						}
					}
				}
			}
			


			break;
		case E_GAMESTEP_END:
			if(m_nTwittLoopCount == 2)
			{
				m_fGameOverTimer = 0;
				m_nTwittLoopCount++;
			}
			else
			{
				m_fGameOverTimer += dt;
			}
			if(m_fGameOverTimer >= 0.5f)
				m_fGameOverTimer = 0.5f;
			
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
{
		if(m_nTwittLoopCount == 1)
		{
			JniMethodInfo t;
			/*
			JniHelper를 통해 org/cocos2dx/application/에 있는 ApplicationDemo class의 JavaJniTestFunc함수 정보를 가져온다.
			*/
				if (JniHelper::getStaticMethodInfo(t
					, "com/starry/crosspuzzle/game"
					, "Twitt"
					, "(II)V"))
				{
			///< 함수 호출
					t.env->CallStaticVoidMethod(t.classID, t.methodID, g_nLevel, g_nStage);
			///< Release
					t.env->DeleteLocalRef(t.classID);
				}
				m_fGameOverTimer = 0.0f;
				m_nTwittLoopCount = 2;
		}
			m_pTwittMsg->setOpacity(255 * (m_fGameOverTimer * 2));
			m_pTwittMsg_Bg->setOpacity(255 * (m_fGameOverTimer * 2));
}
#endif
			g_EffectManager.Update(dt);
			g_LineManager.Update(dt);
			g_PlaneManager.Update(dt);
			g_NumberManager.Update(dt);
			//g_ComboManager.Update(dt, g_nCombo);
			break;
			
		}
	}
}
void GameScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
	if(m_bChangeScene == false)
	{
		if(g_bPause == true)
		{
			//m_pNext.TouchBegan(stPos);
			//m_pRetry.TouchBegan(stPos);
			m_pResume.TouchBegan(stPos);
			//m_pMenu.TouchBegan(stPos);
		}
		else if(g_bPause == false)
		{
			m_pPauseButton.TouchBegan(stPos);
		}
	}
	
	

	
	
	stVec2i stBlockIndex = stVec2i(0,0);
	int		nIndex = 0;
	int		nBlock = 0;

	//printf("(%f,%f)\n",stPos.x,stPos.y);
	if(g_bPause == false)
	{
		if(m_eGameStep == E_GAMESTEP_PLAY)
		{
			if(m_ePlayStep == E_PLAYSTEP_PLAY)
			{
				if(m_nPopStep == 0 && m_nActPoint >= 1) //!< 클릭 처음 단계 일 경우
				{
					//!< 선택된 놈을 찾는다
					for(nBlock = 0; nBlock < g_nBlockMax; nBlock++)
					{
						if( g_BlockList[nBlock].m_bLive == false)
							continue;
						if( g_BlockList[nBlock].m_stIndex.m_nY == 0 )
							continue;
						if( g_BlockList[nBlock].HitTest(stPos.x, stPos.y) == true && g_BlockList[nBlock].m_eBlockState != E_BLOCKSTATE_FALL_FALLING)
						{
							
							m_fPopTimer = 0.0f;
							m_pPopTimer->setVisible(true);
							m_pPopTimer->setScaleX(1.0f * D_SCALE_WIDTH);
							m_pPopTimer->setScaleY(1.0f * D_SCALE_HEIGHT);

							stBlockIndex = g_BlockList[nBlock].m_stIndex; //!< 마지막 인덱스 저장 후 해당 블록들 전부 선택 표시

							m_NumberPopStep.SetVisible(true);
							m_pPopTimer->setPosition( CCPoint((g_BlockList[nBlock].m_stPos.x - 10) * D_SCALE_WIDTH, g_BlockList[nBlock].m_stPos.y * D_SCALE_HEIGHT));
							m_NumberPopStep.SetPos(CCPoint((g_BlockList[nBlock].m_stPos.x )  * D_SCALE_WIDTH, g_BlockList[nBlock].m_stPos.y * D_SCALE_HEIGHT));
							m_NumberPopStep.SetNumber(m_nPopStep+1);
							m_nFocusBlock = nBlock;
							// g_BlockList[nBlock].m_bNoSelect = false;
							break;
						}
					}
					if(nBlock < g_nBlockMax)
					{
						m_nPopStep++;
						if(g_bEFFECT_Sound == true)
						{
							D_SOUNDMNG->playEffect("BlockSelect.mp3");
						}
						//!< 십자모양 선택
						SelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY));


						SelectBlock(stVec2i(stBlockIndex.m_nX-1,stBlockIndex.m_nY));
						SelectBlock(stVec2i(stBlockIndex.m_nX-2,stBlockIndex.m_nY));

						/*if(m_Block_LeftList[0] == NULL)
						{
							CBlock* TempBlock = new TempBlock();
							TempBlock->Init(this,0);
							TempBlock->Create(stVec2i(0,0));
							m_Block_LeftList[0] = 
						}*/


						SelectBlock(stVec2i(stBlockIndex.m_nX+1,stBlockIndex.m_nY));
						SelectBlock(stVec2i(stBlockIndex.m_nX+2,stBlockIndex.m_nY));
						/*m_Block_RightList.push_back(SearchBlock(stVec2i(stBlockIndex.m_nX+1,stBlockIndex.m_nY)));
						m_Block_RightList.push_back(SearchBlock(stVec2i(stBlockIndex.m_nX+2,stBlockIndex.m_nY)));
*/

						SelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY-1));
						SelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY-2));
						/*m_Block_DownList.push_back(SearchBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY-1)));
						m_Block_DownList.push_back(SearchBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY-2)));

*/
						SelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY+1));
						SelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY+2));
						/*m_Block_UpList.push_back(SearchBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY+1)));
						m_Block_UpList.push_back(SearchBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY+2)));
*/
						//!< 선택 리스트 추가
						// m_Block_Center = SearchBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY));
						
						// ChangeBlock(SearchBlock(stVec2i(stBlockIndex.m_nX-1,stBlockIndex.m_nY)) , SearchBlock(stVec2i(stBlockIndex.m_nX+1,stBlockIndex.m_nY)) );
					}


					
				}
				else if(m_nPopStep == 1) //!< 클릭 1단계 일 경우
				{
					//!< 선택된 놈을 찾는다
					if( g_BlockList[m_nFocusBlock].HitTest(stPos.x, stPos.y) == true)
					{
						m_fPopTimer = 0.0f;
						m_pPopTimer->setScaleX(0.6f * D_SCALE_WIDTH);
						m_pPopTimer->setScaleY(0.6f * D_SCALE_HEIGHT);
							m_pPopTimer->setPosition( CCPoint((g_BlockList[m_nFocusBlock].m_stPos.x - 6) * D_SCALE_WIDTH, g_BlockList[m_nFocusBlock].m_stPos.y * D_SCALE_HEIGHT));
						stBlockIndex = g_BlockList[m_nFocusBlock].m_stIndex; //!< 마지막 인덱스 저장 후 해당 블록들 전부 선택 표시

						//m_NumberPopStep.SetVisible(true);
						//m_NumberPopStep.SetPos(g_BlockList[m_nFocusBlock].m_stPos);

						m_NumberPopStep.SetNumber(m_nPopStep+1);

						// g_BlockList[nBlock].m_bNoSelect = false;
						if(g_bEFFECT_Sound == true)
						{
							D_SOUNDMNG->playEffect("BlockSelect.mp3");
						}
						m_nPopStep++;
						//!< 이전 십자 비선택
						UnSelectBlock(stVec2i(stBlockIndex.m_nX+2,stBlockIndex.m_nY));
						UnSelectBlock(stVec2i(stBlockIndex.m_nX-2,stBlockIndex.m_nY));
						UnSelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY+2));
						UnSelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY-2));
					}

				}
				else if(m_nPopStep == 2) //!< 클릭 2단계 일 경우
				{
					//!< 선택된 놈을 찾는다
					if( g_BlockList[m_nFocusBlock].HitTest(stPos.x, stPos.y) == true)
					{
						m_fPopTimer = 0.0f;
						m_pPopTimer->setScaleX(0.2f * D_SCALE_WIDTH);
						m_pPopTimer->setScaleY(0.2f * D_SCALE_HEIGHT);
							m_pPopTimer->setPosition( CCPoint((g_BlockList[m_nFocusBlock].m_stPos.x - 2) * D_SCALE_WIDTH, g_BlockList[m_nFocusBlock].m_stPos.y * D_SCALE_HEIGHT));
						stBlockIndex = g_BlockList[m_nFocusBlock].m_stIndex; //!< 마지막 인덱스 저장 후 해당 블록들 전부 선택 표시

						//m_NumberPopStep.SetVisible(true);
						//m_NumberPopStep.SetPos(g_BlockList[m_nFocusBlock].m_stPos);
						m_NumberPopStep.SetNumber(m_nPopStep+1);
						// g_BlockList[nBlock].m_bNoSelect = false;

						m_nPopStep++;
						if(g_bEFFECT_Sound == true)
						{
							D_SOUNDMNG->playEffect("BlockSelect.mp3");
						}
						//!< 이전 십자 비선택
						UnSelectBlock(stVec2i(stBlockIndex.m_nX+1,stBlockIndex.m_nY));
						UnSelectBlock(stVec2i(stBlockIndex.m_nX-1,stBlockIndex.m_nY));
						UnSelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY+1));
						UnSelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY-1));

						////!< 십자모양 선택
						//SelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY));
					}

				}
				else if(m_nPopStep == 3) //!< 클릭 3단계 일 경우
				{
					if( g_BlockList[m_nFocusBlock].HitTest(stPos.x, stPos.y) == true)
					{
						m_pPopTimer->setVisible(false);
						m_nPopStep = 0;
						m_fPopTimer = 0.0f;
						stBlockIndex = g_BlockList[m_nFocusBlock].m_stIndex; //!< 마지막 인덱스 저장 후 해당 블록들 전부 선택 표시


						m_NumberPopStep.SetVisible(false);
						UnSelectBlock(stVec2i(stBlockIndex.m_nX,stBlockIndex.m_nY));

						if(g_bEFFECT_Sound == true)
						{
							D_SOUNDMNG->playEffect("BlockSelect.mp3");
						}
						//m_Block_UpList.clear();
						//m_Block_RightList.clear();
						//m_Block_DownList.clear();
						//m_Block_LeftList.clear();
						//m_Block_Center = NULL;

					}
				}
			}

		}
		else if(m_eGameStep == E_GAMESTEP_END)
		{
			// D_SCENE_CHANGE_EFFECT_DOWN(StageMenuScene::scene());
			// CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}



	return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());

}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	if(m_bChangeScene == false)
	{
		if(g_bPause == true)
		{
			//m_pNext.TouchEnded(stPos);
			//m_pRetry.TouchEnded(stPos);
			m_pResume.TouchEnded(stPos);
			//m_pMenu.TouchEnded(stPos);
		}
		else if(g_bPause == false)
		{
			m_pPauseButton.TouchEnded(stPos);
		}
	}
/*
	m_pNext.TouchEnded(stPos);
	m_pRetry.TouchEnded(stPos);
	m_pResume.TouchEnded(stPos);
	m_pMenu.TouchEnded(stPos);
	m_pPauseButton.TouchEnded(stPos);*/
}

void GameScene::Explosion(CCPoint CPos, E_BLOCKNUMBER eBlockNumber)
{

	

	CCParticleSystem *emitter3;
	emitter3 = CCParticleSun::node();
	emitter3->setTexture(CCTextureCache::sharedTextureCache()->addImage("snow.png"));
	emitter3->setTotalParticles(9);
	//!< 주의 다시 메모리 해제해주는 방법 찾을것
	emitter3->setAutoRemoveOnFinish(false);
	emitter3->setLife(1.5f);
	emitter3->setLifeVar(0.0f);
	emitter3->setPosition(ccp( CPos.x * D_SCALE_WIDTH, CPos.y * D_SCALE_HEIGHT));
	emitter3->setGravity(ccp(0,0));
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter3->setScale(1.0f);
	emitter3->setStartSize(16.0f);
	emitter3->setStartSizeVar(4.0f);
	emitter3->setEndSize(16.0f);
	emitter3->setEndSizeVar(4.0f);
	emitter3->setDuration(1.5f);
	emitter3->setSpeed(160);
	emitter3->setSpeedVar(0);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter3->setEmissionRate(100.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
	switch(eBlockNumber)
	{
	case E_BLOCKNUMBER_RED:
		emitter3->setStartColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 0, (1.0f/255) * 0, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 0, (1.0f/255) * 0, 0.0f));
		break;
	case E_BLOCKNUMBER_YELLOW:
		emitter3->setStartColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 255, (1.0f/255) * 0, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 255, (1.0f/255) * 0, 0.0f));
		break;
	case E_BLOCKNUMBER_BLUE:
		emitter3->setStartColor(ccc4f((1.0f/255) * 0, (1.0f/255) * 0, (1.0f/255) * 255, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 0, (1.0f/255) * 0, (1.0f/255) * 255, 0.0f));
		break;
	case E_BLOCKNUMBER_GREEN:
		emitter3->setStartColor(ccc4f((1.0f/255) * 0, (1.0f/255) * 255, (1.0f/255) * 0, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 0, (1.0f/255) * 255, (1.0f/255) * 0, 0.0f));
		break;
	case E_BLOCKNUMBER_PURPLE:
		emitter3->setStartColor(ccc4f((1.0f/255) * 153, (1.0f/255) * 0, (1.0f/255) * 255, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 153, (1.0f/255) * 0, (1.0f/255) * 255, 0.0f));
		break;
	case E_BLOCKNUMBER_ORANGE:
		emitter3->setStartColor(ccc4f((1.0f/255) * 168, (1.0f/255) * 168, (1.0f/255) * 168, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 168, (1.0f/255) * 168, (1.0f/255) * 168, 0.0f));
		break;
	}
	this->addChild(emitter3,23);

	stParticleTimer* stTempTimer = new stParticleTimer(1.5f + ((float)(rand()%300) / 100.0f),0.0f,emitter3);


	m_ParticleList.push_back(stTempTimer);

	
}

void GameScene::Fire(CCPoint CPos)
{

	CCParticleSystem *emitter3;
	emitter3 = CCParticleFire::node();
	emitter3->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	emitter3->setTotalParticles(45);
	//!< 주의 다시 메모리 해제해주는 방법 찾을것
	emitter3->setAutoRemoveOnFinish(false);
	emitter3->setLife(0.5f);
	emitter3->setLifeVar(0.0f);
	emitter3->setPosition(ccp( CPos.x * D_SCALE_WIDTH, CPos.y * D_SCALE_HEIGHT));
	emitter3->setGravity(ccp(0,0));
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter3->setScale(0.5f);
	emitter3->setStartSize(32.0f);
	emitter3->setStartSizeVar(4.0f);
	emitter3->setEndSize(32.0f);
	emitter3->setEndSizeVar(4.0f);
	emitter3->setDuration(1.5f);
	emitter3->setSpeed(120);
	emitter3->setSpeedVar(0);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter3->setEmissionRate(100.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
	emitter3->setStartColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 0, (1.0f/255) * 0, 1.0f));
	emitter3->setEndColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 0, (1.0f/255) * 0, 0.0f));
	this->addChild(emitter3,23);

	stParticleTimer* stTempTimer = new stParticleTimer(1.5f + ((float)(rand()%300) / 100.0f),0.0f,emitter3);

	m_ParticleList.push_back(stTempTimer);

}
void GameScene::DeleteParticleUpdate(float dt)
{
	vector<stParticleTimer*>::iterator it;
	for(it = m_ParticleList.begin(); it != m_ParticleList.end(); )
	{
		(*it)->m_fTime += dt;
		if((*it)->m_fTime >= (*it)->m_fTargetTime)
		{
			(*it)->emitter3->removeFromParentAndCleanup(true);
			delete (*it);
			it = m_ParticleList.erase(it);
		}
		else
		{
			it++;
		}
	}
}
void GameScene::FillBlockCheck()
{
	for(int y=2; y<D_BLOCKMAP_HEIGHT; y++)
	{
		for(int x=0; x<D_BLOCKMAP_WIDTH; x++)
		{
			if(g_Map.m_nBlockMap[y][x] == 0)
			{
				CreateBlock(x,0);
				// printf("(%d,%d) 블록 채워짐\n",x,y);
			}
		}
	}
	
}
bool GameScene::FillBlockEnd()
{
	int nNumber = 0;
	int nBlock = 0;
	for(int y=2; y<D_BLOCKMAP_HEIGHT; y++)
	{
		for(int x=0; x<D_BLOCKMAP_WIDTH; x++)
		{
			if(g_Map.m_nBlockMap[y][x] == 1)
			{
				nNumber++;
			}
		}
	}
	if(nNumber < g_nBlockMax - (D_BLOCKMAP_WIDTH * 2))
		return false;
	else
	{
		for(nBlock=0; nBlock<g_nBlockMax; nBlock++)
		{
			if(g_BlockList[nBlock].m_stIndex.m_nY < 2)
			{
				continue;
			}
			if(g_BlockList[nBlock].m_bLive == true && g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
			{
				return false;
			}
			if(g_BlockList[nBlock].m_bLive == true && g_BlockList[nBlock].m_nBounceLevel > 0)
			{
				return false;
			}
		}
		return true;
	}
}
void GameScene::SelectReset() //!< 해당 블록을 찾아서 NoSelect를 false로 변경
{
	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		g_BlockList[nBlock].m_bNoSelect = true;
	}

	// printf("*** 전체 블록 선택 초기화됨\n");
}


void GameScene::UnSelectBlock(stVec2i stBlockIndex) //!< 해당 블록을 찾아서 NoSelect를 false로 변경
{
	if(stBlockIndex.m_nX < 0)
		return;
	if(stBlockIndex.m_nX >= D_BLOCKMAP_WIDTH)
		return;
	if(stBlockIndex.m_nY < 2)
		return;
	if(stBlockIndex.m_nY >= D_BLOCKMAP_HEIGHT)
		return;

	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if( g_BlockList[nBlock].m_stIndex  == stBlockIndex )
		{
			g_BlockList[nBlock].m_bNoSelect = true;
			g_BlockList[nBlock].m_fTargetColorAlpha = 0.0f;
			// printf("(%d,%d) 블록 비선택됨\n",stBlockIndex.m_nX,stBlockIndex.m_nY);
			break;
		}
	}
}

void GameScene::SelectBlock(stVec2i stBlockIndex) //!< 해당 블록을 찾아서 NoSelect를 false로 변경
{
	if(stBlockIndex.m_nX < 0)
		return;
	if(stBlockIndex.m_nX >= D_BLOCKMAP_WIDTH)
		return;
	if(stBlockIndex.m_nY < 2)
		return;
	if(stBlockIndex.m_nY >= D_BLOCKMAP_HEIGHT)
		return;

	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if( g_BlockList[nBlock].m_stIndex  == stBlockIndex )
		{
			g_BlockList[nBlock].m_bNoSelect = false;
			g_BlockList[nBlock].m_fTargetColorAlpha = 1.0f;
			// printf("(%d,%d) 블록 선택됨\n",stBlockIndex.m_nX,stBlockIndex.m_nY);
			break;
		}
	}
}

void GameScene::PopCheck()
{
	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if(g_BlockList[nBlock].m_bNoSelect == false)
		{
			PopBlock(nBlock);
		}
	}
}


void GameScene::PopBlock(stVec2i stBlockIndex) //!< 해당 블록을 찾아서 터트림
{
	if(stBlockIndex.m_nX < 0)
		return;
	if(stBlockIndex.m_nX >= D_BLOCKMAP_WIDTH)
		return;
	if(stBlockIndex.m_nY < 2)
		return;
	if(stBlockIndex.m_nY >= D_BLOCKMAP_HEIGHT)
		return;

	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if( g_BlockList[nBlock].m_stIndex == stBlockIndex )
		{
			g_BlockList[nBlock].Alphaing();

			// g_BlockList[nBlock].Die();
			// g_Map.m_nBlockMap[stBlockIndex.m_nY][stBlockIndex.m_nX] = 0;

			// g_EffectManager.Insert(1,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y);
			
			// printf("(%d,%d) 블록 터트림\n",stBlockIndex.m_nX,stBlockIndex.m_nY);
			break;
		}
	}
}


int GameScene::SearchBlockIndex(stVec2i stBlockIndex)
{
	if(stBlockIndex.m_nX < 0)
		return -1;
	if(stBlockIndex.m_nX >= D_BLOCKMAP_WIDTH)
		return -1;
	if(stBlockIndex.m_nY < 2)
		return -1;
	if(stBlockIndex.m_nY >= D_BLOCKMAP_HEIGHT)
		return -1;

	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if( g_BlockList[nBlock].m_stIndex == stBlockIndex )
		{
			return nBlock;
		}
	}
	return -1;
}
CBlock* GameScene::SearchBlock(stVec2i stBlockIndex) //!< 해당 블록을 찾아서 터트림
{
	if(stBlockIndex.m_nX < 0)
		return NULL;
	if(stBlockIndex.m_nX >= D_BLOCKMAP_WIDTH)
		return NULL;
	if(stBlockIndex.m_nY < 2)
		return NULL;
	if(stBlockIndex.m_nY >= D_BLOCKMAP_HEIGHT)
		return NULL;

	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if( g_BlockList[nBlock].m_stIndex == stBlockIndex )
		{
			return &g_BlockList[nBlock];
		}
	}
}


void GameScene::PopBlock(int nIndex) //!< 해당 블록을 찾아서 터트림
{
	// g_EffectManager.Insert(1,g_BlockList[nIndex].m_stPos.x,g_BlockList[nIndex].m_stPos.y);
	g_BlockList[nIndex].Alphaing();

	//g_BlockList[nIndex].Die();
	//g_Map.m_nBlockMap[g_BlockList[nIndex].m_stIndex.m_nY][g_BlockList[nIndex].m_stIndex.m_nX] = 0;

	// printf("%d 블록 터트림\n", nIndex);
}


void GameScene::Logic_StartLine(float dt)
{
	//!< 시작 라인 블록맵세로크기 - 1번을 m_fStartLineTime초 간격으로 내려오게 함 m_fStartLineTime는 개행시마다 일정정도 감소 점차 빠르게 내려오게 함
	if(m_nStartLineStep < D_BLOCKMAP_HEIGHT - 2)
	{
		m_fStartLineTimer += dt;
		if(m_fStartLineTimer >= m_fStartLineTime)
		{
			m_fStartLineTimer = 0.0f;
			m_fStartLineTime -= 0.04f;
			CreateLine();
			m_nStartLineStep++;
			
		}
	}
	if(m_nStartLineStep >= D_BLOCKMAP_HEIGHT - 2)
	{
		if(m_fReadyTimer >= 3.0f)
		{
			m_pReady->setVisible(false);
			m_pGo->setVisible(false);
			m_eGameStep = E_GAMESTEP_PLAY;
		}
	}
}
void GameScene::Logic_BlockUpdate(float dt)
{
	//!< 모든 블록 업데이트 갱신
	for(int i=0; i<g_nBlockMax; i++)
	{
		g_BlockList[i].Update(dt);
	}
}
void GameScene::Logic_BlockFall()
{
	int nBlock = 0; //!< 현재 포커싱된 블록
	//!< 모든 블록 낙하 로직 갱신
	for(nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if(g_BlockList[nBlock].m_bLive == false)
			continue;
		/*if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
			continue;*/
		if(g_BlockList[nBlock].m_bDraged == true)
			continue;
		if(g_BlockList[nBlock].m_stIndex.m_nY != D_BLOCKMAP_HEIGHT - 1)
		{
			if(g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] == 0)
			{
				if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
				{
					if(g_BlockList[nBlock].m_bFallFinished == true)
					{
						g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
						g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] = 1;


						//g_BlockList[nBlock].m_eBlockState = E_BLOCKSTATE_FALL_FALLING;
						g_BlockList[nBlock].m_fStartY = g_BlockList[nBlock].m_stPos.y;
						//g_BlockList[nBlock].m_stPos.y += g_BlockList[nBlock].m_fGPM;
						g_BlockList[nBlock].m_fDistance = g_BlockList[nBlock].m_fNextDistance;
						g_BlockList[nBlock].m_fNextDistance = 64.0f;
						g_BlockList[nBlock].m_stIndex.m_nY += 1;
						g_BlockList[nBlock].m_bFallFinished = false;
					}
				}
				else if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_NONE)
				{
					g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
					g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] = 1;


					g_BlockList[nBlock].m_eBlockState = E_BLOCKSTATE_FALL_FALLING;
					//g_BlockList[nBlock].m_fGPM = 0.0f;
					g_BlockList[nBlock].m_fStartY = g_BlockList[nBlock].m_stPos.y;
					g_BlockList[nBlock].m_fDistance = g_BlockList[nBlock].m_fNextDistance;
					g_BlockList[nBlock].m_fNextDistance = 64.0f;
					g_BlockList[nBlock].m_stIndex.m_nY += 1;
					g_BlockList[nBlock].m_bFallFinished = false;
				}
			}
			else if(g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] == 1)
			{
				if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
				{
					if(g_BlockList[nBlock].m_bFallFinished == true)
					{
						g_BlockList[nBlock].m_fBouncePower		= (g_BlockList[nBlock].m_fSpeed - D_BLOCK_SPEED) * D_BLOCK_BOUNCE_HURISTIC;
						if(g_BlockList[nBlock].m_fBouncePower >= D_BLOCK_BOUNCE_FOWER)
							g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
						if(g_BlockList[nBlock].m_fBouncePower <= D_BLOCK_BOUNCE_FOWER_LOW)
							g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER_LOW;
						g_BlockList[nBlock].m_fSpeed			= D_BLOCK_SPEED;
						g_BlockList[nBlock].m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
						g_BlockList[nBlock].m_fNowDistance		= 0.0f;
						g_BlockList[nBlock].m_fDistance			= 64.0f;
						//g_BlockList[nBlock].m_fGPM = 0.0f;
						g_BlockList[nBlock].m_nBounceLevel		= 1;
						g_BlockList[nBlock].m_fBounceLine		= g_BlockList[nBlock].m_stPos.y;
						
						g_BlockList[nBlock].m_eBlockState		= E_BLOCKSTATE_FALL_NONE;
						
					}
				}
			}
		}
		else if(g_BlockList[nBlock].m_stIndex.m_nY == D_BLOCKMAP_HEIGHT - 1)
		{
			if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
			{
				if(g_BlockList[nBlock].m_bFallFinished == true)
				{
					g_BlockList[nBlock].m_fBouncePower		= (g_BlockList[nBlock].m_fSpeed - D_BLOCK_SPEED) * D_BLOCK_BOUNCE_HURISTIC;
					if(g_BlockList[nBlock].m_fBouncePower >= D_BLOCK_BOUNCE_FOWER)
						g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
					if(g_BlockList[nBlock].m_fBouncePower <= D_BLOCK_BOUNCE_FOWER_LOW)
							g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER_LOW;
					g_BlockList[nBlock].m_fSpeed			= D_BLOCK_SPEED;
					g_BlockList[nBlock].m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
					g_BlockList[nBlock].m_fNowDistance		= 0.0f;
					g_BlockList[nBlock].m_fDistance			= 64.0f;
					//g_BlockList[nBlock].m_fGPM = 0.0f;
					g_BlockList[nBlock].m_nBounceLevel		= 1;
					g_BlockList[nBlock].m_fBounceLine		= g_BlockList[nBlock].m_stPos.y;
					g_BlockList[nBlock].m_eBlockState		= E_BLOCKSTATE_FALL_NONE;
				}
			}
		}
		
	}
}
void GameScene::Logic_Pop()
{
	for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
	{
		g_BlockList[nBlock].CheckReset();
		
		/*if(g_BlockList[nBlock].m_stIndex.m_nY == 0) //!< 쌓여있는놈 지우기
		{
			g_BlockList[nBlock].Die();
		}*/
	}

	m_bPoped = false;
	float m_fCenterX = 0.0f;
	float m_fCenterY = 0.0f;
	
	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if(g_BlockList[nBlock].m_bChecked == true) //!< 이미 포함한 녀석이면 지나감
			continue;

		if(g_BlockList[nBlock].m_bLive == false) //!< 죽어있는 녀석이면 지나감
			continue;

		if(g_BlockList[nBlock].m_stIndex.m_nY < 2) //!< 가장 윗줄에 있는 녀석이면 지나감
			continue;
		
			CPopList* pPopList = new CPopList();
			pPopList->Init(nBlock);

			//!< 진동설정

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	{
//		JniMethodInfo t;
//	/*
//	JniHelper를 통해 org/cocos2dx/application/에 있는 ApplicationDemo class의 JavaJniTestFunc함수 정보를 가져온다.
//	*/
//		if (JniHelper::getStaticMethodInfo(t
//			, "org/cocos2dx/lib/Cocos2dxActivity"
//			, "Vivrate_SHORT_BUZZ"
//			, "()V"))
//		{
//	///< 함수 호출
//			t.env->CallStaticVoidMethod(t.classID, t.methodID);
//	///< Release
//			t.env->DeleteLocalRef(t.classID);
//		}
//	}
//#endif
			m_fCenterX = 0.0f;
			m_fCenterY = 0.0f;

			if(g_bFever == false)
				m_nPopBlockNumber = 4;
			else if (g_bFever == true)
				m_nPopBlockNumber = 3;

			//printf("Logic_Pop Check1 Entered!\n");
			if(pPopList->m_BlockList.size() >= m_nPopBlockNumber)
			{
				//printf("Logic_Pop Poped Entered!\t");
				for(int i=0; i<pPopList->m_BlockList.size(); i++)
				{
					g_Map.m_nBlockMap[pPopList->m_BlockList[i]->m_stIndex.m_nY][pPopList->m_BlockList[i]->m_stIndex.m_nX] = 0;
					g_EffectManager.Insert(((int)pPopList->m_BlockList[i]->m_eBlockNumber) + 1,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y);
					Explosion(ccp(pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y), pPopList->m_BlockList[i]->m_eBlockNumber);
					// printf("(%d,%d) 블록 터트림\n",pPopList->m_BlockList[i]->m_stIndex.m_nY,pPopList->m_BlockList[i]->m_stIndex.m_nX);
				
					if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_LIGHTNING)
					{
						m_Item_Lightning.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}
					else if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_BOMB)
					{
						m_Item_Bomb.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}
					else if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_SPACE)
					{
						m_Item_Space.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}
					m_fCenterX += pPopList->m_BlockList[i]->m_stPos.x;
					m_fCenterY += pPopList->m_BlockList[i]->m_stPos.y;

					//if(g_bFever == true)
					//{
					//	if(i < m_nPopBlockNumber)
					//	{
					//		g_nScore += D_SCORE_POP;
					//	

					//		if(g_nCombo == 0)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 1)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 2)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 3)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 4)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f));
					//		}
					//		else if(g_nCombo == 5)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f));
					//		}
					//		else
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f));
					//		}

					//	}
					//	else if(i >= m_nPopBlockNumber) //!< 5개째 부터
					//	{
					//		g_nScore += (D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1)))) ;
					//	
					//	
					//	
					//		if(g_nCombo == 0)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 1)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 2)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 3)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 4)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 5)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//	}
					//}
					//if(g_bFever == false)
					//{
						if(i < m_nPopBlockNumber)
						{
							g_nScore += D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo));
					


							if(g_nCombo == 0)
							{
								g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
							}
							else if(g_nCombo == 1)
							{
								g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f));
							}
							else if(g_nCombo == 2)
							{
								g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f));
							}
							else if(g_nCombo == 3)
							{
								g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f));
							}
							else if(g_nCombo == 4)
							{
								g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f));
							}
							else if(g_nCombo == 5)
							{
								g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f));
							}
							else
							{
								g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f));
							}

						}
						else if(i >= m_nPopBlockNumber) //!< 5개째 부터
						{
							g_nScore += (D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo));
					
					
					
							if(g_nCombo == 0)
							{
								g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
							}
							else if(g_nCombo == 1)
							{
								g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
							}
							else if(g_nCombo == 2)
							{
								g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
							}
							else if(g_nCombo == 3)
							{
								g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
							}
							else if(g_nCombo == 4)
							{
								g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
							}
							else if(g_nCombo == 5)
							{
								g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
							}
							else
							{
								g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
							}
						}
					//}
					
					pPopList->m_BlockList[i]->Die();

						m_bPoped = true;
				}

				m_fCenterX /= pPopList->m_BlockList.size();
				m_fCenterY /= pPopList->m_BlockList.size();

				CDot* pTemp = new CDot(ccp(m_fCenterX,m_fCenterY));
				m_Block_PopPoint.push_back(pTemp);

			}

			pPopList->m_BlockList.clear();
			delete pPopList;
	}
	
	
	if(m_bPoped == true)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		g_nCombo++;
	}
	if(m_Block_PopPoint.size() >= 5)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Pentagon.mp3");
		}
	}
	else if(m_Block_PopPoint.size() >= 4)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Square.mp3");
		}
	}
	else if(m_Block_PopPoint.size() >= 3)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Triangle.mp3");
		}
	}
	else if(m_Block_PopPoint.size() >= 2)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Line.mp3");
		}
	}

	if(m_Block_PopPoint.size() >= 2)
	{
		for(int i=0; i<m_Block_PopPoint.size(); i++)
		{
			g_nScore += D_SCORE_LINE;
			g_NumberManager.Insert(D_SCORE_LINE ,m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
		}
	}

	if(m_Block_PopPoint.size() >= 3)
	{
		float fWidth = 0.0f;
		float fHeigjt = 0.0f;

		float fDistance = 0.0f;

		float fAngle = 0.0f;

		for(int i=0; i<m_Block_PopPoint.size()-1; i++)
		{
			fWidth = m_Block_PopPoint[i]->m_stPos.x - m_Block_PopPoint[i+1]->m_stPos.x;
			fHeigjt = m_Block_PopPoint[i]->m_stPos.y - m_Block_PopPoint[i+1]->m_stPos.y;

			fDistance = sqrt((fWidth*fWidth) + (fHeigjt*fHeigjt));
		

			fAngle = RadToDeg( atan2(fHeigjt, -fWidth) );
			//!< 선 긋기 
			g_EffectManager.Insert(7,m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y,(fDistance / 200.0f),1.0f,fAngle);


		}

		fWidth = m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x - m_Block_PopPoint[0]->m_stPos.x;
		fHeigjt = m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y - m_Block_PopPoint[0]->m_stPos.y;

		fDistance = sqrt((fWidth*fWidth) + (fHeigjt*fHeigjt));
		

		fAngle = RadToDeg( atan2(fHeigjt, -fWidth) );
		//!< 선 긋기 
		g_LineManager.Insert(7,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y,(fDistance / 200.0f),1.0f,fAngle);
	}
	else if(m_Block_PopPoint.size() >= 2)
	{
		float fWidth = 0.0f;
		float fHeigjt = 0.0f;

		float fDistance = 0.0f;

		float fAngle = 0.0f;
		
		fWidth = m_Block_PopPoint[0]->m_stPos.x - m_Block_PopPoint[1]->m_stPos.x;
		fHeigjt = m_Block_PopPoint[0]->m_stPos.y - m_Block_PopPoint[1]->m_stPos.y;

		fDistance = sqrt((fWidth*fWidth) + (fHeigjt*fHeigjt));
		

		fAngle = RadToDeg( atan2(fHeigjt, -fWidth) );
		g_LineManager.Insert(7,m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y,(fDistance / 200.0f),1.0f,fAngle);
	}
	m_fCenterX = 0.0f;
	m_fCenterY = 0.0f;

	if(m_Block_PopPoint.size() == 1)
	{
		if(m_Block_PopPoint[0]->m_bItem == true)
		{

		}
		else if(m_Block_PopPoint[0]->m_bItem == false)
		{
			for(int i=0; i<m_Block_PopPoint.size(); i++)
			{
				g_LineManager.Insert(8,m_Block_PopPoint[i]->m_stPos.x ,m_Block_PopPoint[i]->m_stPos.y);
		
				m_fCenterX += m_Block_PopPoint[i]->m_stPos.x;
				m_fCenterY += m_Block_PopPoint[i]->m_stPos.y;

			}
		}
	}
	else
	{
		for(int i=0; i<m_Block_PopPoint.size(); i++)
		{
			g_LineManager.Insert(8,m_Block_PopPoint[i]->m_stPos.x ,m_Block_PopPoint[i]->m_stPos.y);
		
			m_fCenterX += m_Block_PopPoint[i]->m_stPos.x;
			m_fCenterY += m_Block_PopPoint[i]->m_stPos.y;

		}
	}
	m_fCenterX /= m_Block_PopPoint.size();
	m_fCenterY /= m_Block_PopPoint.size();

	if(m_Block_PopPoint.size() == 1)
	{
		if(m_Block_PopPoint[0]->m_bItem == true)
		{

		}
		else if(m_Block_PopPoint[0]->m_bItem == false)
		{
			g_PlaneManager.Insert(m_Block_PopPoint.size(),m_fCenterX,m_fCenterY);
		}
	}
	else
	{
		g_PlaneManager.Insert(m_Block_PopPoint.size(),m_fCenterX,m_fCenterY);
	}

	/*for(int i=0; i<m_Block_PopPoint.size(); i++)
	{
		delete m_Block_PopPoint[i];
	}

	m_Block_PopPoint.clear();*/


	// printf("점수 %d , 콤보 %d\b",g_nScore,g_nCombo);
	//printf("Logic_Pop End Entered!\n");
	
}
/*
bool GameScene::BlockPopAble()
{
	for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
	{
		g_BlockList[nBlock].CheckReset();
	}

	for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
	{
		if(g_BlockList[nBlock].m_bChecked == true)
			continue;
		if(g_BlockList[nBlock].m_bLive == false)
			continue;
		if(g_BlockList[nBlock].m_stIndex.m_nY == 0)
			continue;
		CPopList* pPopList = new CPopList();
		pPopList->Init(nBlock);

		if(pPopList->m_BlockList.size() >= m_nPopBlockNumber)
		{
			delete pPopList;
			return true;
		}

		delete pPopList;
	}
	return false;
}*/
bool GameScene::HitTest_LintToLine(CCPoint p1, CCPoint p2, CCPoint p3, CCPoint p4)
{
	 double d = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y)*(p3.x - p4.x);
	 if(d==0) return false;
	  double pre = (p1.x*p2.y - p1.y*p2.x), post = (p3.x*p4.y - p3.y*p4.x);

	  double x = (pre * (p3.x - p4.x) - (p1.x - p2.x) * post) / d;
	  double y = (pre * (p3.y - p4.y) - (p1.y - p2.y) * post) / d;
	
	 if(x < min(p1.x, p2.x) || x > max(p1.x, p2.x) || x < min(p3.x, p4.x) || x > max(p3.x, p4.x))
	  return false;
	 if(y < min(p1.y, p2.y) || y > max(p1.y, p2.y) || y < min(p3.y, p4.y) || y > max(p3.y, p4.y))
	  return false;

	 return true;
}
void GameScene::Logic_LinePop()
{
	bool bPoped = false;
	bool bNowPoped = false;
	if(m_Block_PopPoint.size() >= 3)
	{
		for(int i=0; i<m_Block_PopPoint.size(); i++)
		{
			//m_Block_PopPoint[i]->m_stPos.x 
			for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
			{
				if(g_BlockList[nBlock].m_bLive == false)
					continue;
				bNowPoped = false;
				for(int i=0; i<m_Block_PopPoint.size()-1; i++)
				{
					if( HitTest_LintToLine(ccp(m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y),ccp(m_Block_PopPoint[i+1]->m_stPos.x,m_Block_PopPoint[i+1]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x + 32 ,g_BlockList[nBlock].m_stPos.y - 32)) == true ||
						HitTest_LintToLine(ccp(m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y),ccp(m_Block_PopPoint[i+1]->m_stPos.x,m_Block_PopPoint[i+1]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y + 32), ccp(g_BlockList[nBlock].m_stPos.x + 32,g_BlockList[nBlock].m_stPos.y + 32)) == true ||
  						HitTest_LintToLine(ccp(m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y),ccp(m_Block_PopPoint[i+1]->m_stPos.x,m_Block_PopPoint[i+1]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x - 32 ,g_BlockList[nBlock].m_stPos.y + 32)) == true ||
						HitTest_LintToLine(ccp(m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y),ccp(m_Block_PopPoint[i+1]->m_stPos.x,m_Block_PopPoint[i+1]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x + 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x + 32 ,g_BlockList[nBlock].m_stPos.y + 32)) == true)
					{
						if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_LIGHTNING)
						{
							m_Item_Lightning.push_back(g_BlockList[nBlock].m_stIndex);
						}
						else if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_BOMB)
						{
							m_Item_Bomb.push_back(g_BlockList[nBlock].m_stIndex);
						}
						else if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_SPACE)
						{
							m_Item_Space.push_back(g_BlockList[nBlock].m_stIndex);
						}
						g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
						g_EffectManager.Insert(((int)g_BlockList[nBlock].m_eBlockNumber) + 1,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y);
						Explosion(ccp(g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y), g_BlockList[nBlock].m_eBlockNumber);
				
						g_nScore += D_SCORE_POP;
						g_NumberManager.Insert(D_SCORE_POP ,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f));
						g_BlockList[nBlock].Die();
						bPoped = true;
						bNowPoped = true;
						
						break;
					}
				}
				if(bNowPoped == false)
				{
					if( HitTest_LintToLine(ccp(m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y),ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x + 32 ,g_BlockList[nBlock].m_stPos.y - 32)) == true ||
						HitTest_LintToLine(ccp(m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y),ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y + 32), ccp(g_BlockList[nBlock].m_stPos.x + 32,g_BlockList[nBlock].m_stPos.y + 32)) == true ||
  						HitTest_LintToLine(ccp(m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y),ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x - 32 ,g_BlockList[nBlock].m_stPos.y + 32)) == true ||
						HitTest_LintToLine(ccp(m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y),ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),
										   ccp(g_BlockList[nBlock].m_stPos.x + 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x + 32 ,g_BlockList[nBlock].m_stPos.y + 32)) == true)
					{
						if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_LIGHTNING)
						{
							m_Item_Lightning.push_back(g_BlockList[nBlock].m_stIndex);
						}
						else if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_BOMB)
						{
							m_Item_Bomb.push_back(g_BlockList[nBlock].m_stIndex);
						}
						else if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_SPACE)
						{
							m_Item_Space.push_back(g_BlockList[nBlock].m_stIndex);
						}
						g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
						g_EffectManager.Insert(((int)g_BlockList[nBlock].m_eBlockNumber) + 1,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y);
						Explosion(ccp(g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y), g_BlockList[nBlock].m_eBlockNumber);
				
						g_nScore += D_SCORE_POP;
						g_NumberManager.Insert(D_SCORE_POP ,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f));
						g_BlockList[nBlock].Die();
						bPoped = true;
						
					}
				}
				//g_BlockList[nBlock].CheckReset();
			}
		}
	}
	else if(m_Block_PopPoint.size() >= 2)
	{
		for(int i=0; i<m_Block_PopPoint.size(); i++)
		{
			//m_Block_PopPoint[i]->m_stPos.x 
			for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
			{
				if(g_BlockList[nBlock].m_bLive == false)
					continue;
				if( HitTest_LintToLine(ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),ccp(m_Block_PopPoint[1]->m_stPos.x,m_Block_PopPoint[1]->m_stPos.y),
									   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x + 32 ,g_BlockList[nBlock].m_stPos.y - 32)) == true ||
					HitTest_LintToLine(ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),ccp(m_Block_PopPoint[1]->m_stPos.x,m_Block_PopPoint[1]->m_stPos.y),
									   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y + 32), ccp(g_BlockList[nBlock].m_stPos.x + 32,g_BlockList[nBlock].m_stPos.y + 32)) == true ||
  				    HitTest_LintToLine(ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),ccp(m_Block_PopPoint[1]->m_stPos.x,m_Block_PopPoint[1]->m_stPos.y),
									   ccp(g_BlockList[nBlock].m_stPos.x - 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x - 32 ,g_BlockList[nBlock].m_stPos.y + 32)) == true ||
					HitTest_LintToLine(ccp(m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y),ccp(m_Block_PopPoint[1]->m_stPos.x,m_Block_PopPoint[1]->m_stPos.y),
									   ccp(g_BlockList[nBlock].m_stPos.x + 32,g_BlockList[nBlock].m_stPos.y - 32), ccp(g_BlockList[nBlock].m_stPos.x + 32 ,g_BlockList[nBlock].m_stPos.y + 32)) == true)
				{
					if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_LIGHTNING)
					{
						m_Item_Lightning.push_back(g_BlockList[nBlock].m_stIndex);
					}
					else if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_BOMB)
					{
						m_Item_Bomb.push_back(g_BlockList[nBlock].m_stIndex);
					}
					else if(g_BlockList[nBlock].m_eBlockItem == E_BLOCKITEM_SPACE)
					{
						m_Item_Space.push_back(g_BlockList[nBlock].m_stIndex);
					}
					g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
					g_EffectManager.Insert(((int)g_BlockList[nBlock].m_eBlockNumber) + 1,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y);
					Explosion(ccp(g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y), g_BlockList[nBlock].m_eBlockNumber);
				
					g_nScore += D_SCORE_POP;
					g_NumberManager.Insert(D_SCORE_POP ,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f));
					g_BlockList[nBlock].Die();
					bPoped = true;
					
				}
				//g_BlockList[nBlock].CheckReset();
			}
		}
	}
	if(bPoped == true)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
	}
	else
	{
		 g_LineManager.Exit();
		 g_LineManager.m_pEffectList.clear();
	}
	for(int i=0; i<m_Block_PopPoint.size(); i++)
	{
		if(m_Block_PopPoint[i]->m_bItem == true)
		{
			m_Block_PopPoint[i]->m_pDot->removeFromParentAndCleanup(true);
			delete m_Block_PopPoint[i];
		}
		else if(m_Block_PopPoint[i]->m_bItem == false)
		{
			delete m_Block_PopPoint[i];
		}

	}

	m_Block_PopPoint.clear();
}

void GameScene::Logic_Lightning()
{
	if(m_Item_Lightning.size() >= 1)
	{
		for(int i=0; i<m_Item_Lightning.size(); i++)
		{
			for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
			{
				if(g_BlockList[nBlock].m_bLive == false)
					continue;
				if(g_BlockList[nBlock].m_stIndex.m_nY == 0 || g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Lightning[i].m_nY)
					continue;
				if(g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Lightning[i].m_nX)
				{
					g_nScore += D_SCORE_POP_LIGHTNING;
					g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
					g_EffectManager.Insert(((int)g_BlockList[nBlock].m_eBlockNumber) + 1,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y);
					Explosion(ccp(g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y), g_BlockList[nBlock].m_eBlockNumber);
					g_NumberManager.Insert(D_SCORE_POP_LIGHTNING,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f));
					g_BlockList[nBlock].Die();
				}
			}
			g_EffectManager.Insert(9,D_LINE_START_X + (64.0f * m_Item_Lightning[i].m_nX),400.0f,2.0f,1.0f,90.0f);
			g_PlaneManager.Insert(101, D_LINE_START_X + (64.0f * m_Item_Lightning[i].m_nX),400.0f);
		}
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Lightning.mp3");
		}
	}
	m_Item_Lightning.clear();
}

void GameScene::Logic_Bomb()
{
	if(m_Item_Bomb.size() >= 1)
	{
		for(int i=0; i<m_Item_Bomb.size(); i++)
		{
			for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
			{
				if(g_BlockList[nBlock].m_bLive == false)
					continue;
				if(g_BlockList[nBlock].m_stIndex.m_nY == 0)
					continue;
				if(g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX && g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY)
					continue;
				if( ( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX - 1 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY - 1  ) ||
				    ( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX - 0 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY - 1  ) ||
					( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX + 1 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY - 1  ) ||
					( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX - 1 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY - 0  ) ||
					( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX + 1 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY - 0  ) ||
					( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX - 1 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY + 1  ) ||
					( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX - 0 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY + 1  ) ||
					( g_BlockList[nBlock].m_stIndex.m_nX == m_Item_Bomb[i].m_nX + 1 &&
					  g_BlockList[nBlock].m_stIndex.m_nY == m_Item_Bomb[i].m_nY + 1  ) )
				{
					g_nScore += D_SCORE_POP_BOMB;
					g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
					g_EffectManager.Insert(((int)g_BlockList[nBlock].m_eBlockNumber) + 1,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y);
					
					Fire(ccp(g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y));
					//Explosion(ccp(g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y), g_BlockList[nBlock].m_eBlockNumber);
					
					
					g_NumberManager.Insert(D_SCORE_POP_BOMB,g_BlockList[nBlock].m_stPos.x,g_BlockList[nBlock].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f));
					g_BlockList[nBlock].Die();
				}
			}
			
			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64) - 64.0f, D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64) - 64.0f); 
			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64), D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64) - 64.0f);
			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64) + 64.0f, D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64) - 64.0f);

			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64) - 64.0f, D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64));
			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64), D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64));
			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64) + 64.0f, D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64));

			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64) - 64.0f, D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64) + 64.0f);
			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64), D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64) + 64.0f);
			g_EffectManager.Insert(10, D_LINE_START_X + (m_Item_Bomb[i].m_nX * 64) + 64.0f, D_LINE_START_Y - (m_Item_Bomb[i].m_nY * 64) + 64.0f);

			//g_EffectManager.Insert(9,D_LINE_START_X + (64.0f * m_Item_Lightning[i].m_nX),400.0f,2.0f,1.0f,90.0f);
		}
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Bomb.mp3");
		}
	}
	m_Item_Bomb.clear();
}

void GameScene::Logic_Space()
{
	if(m_Item_Space.size() >= 1)
	{
		for(int i=0; i<m_Item_Space.size(); i++)
		{
			CDot* pTemp = new CDot(ccp(D_LINE_START_X + (m_Item_Space[i].m_nX * 64), D_LINE_START_Y - (m_Item_Space[i].m_nY * 64)),this);
			m_Block_PopPoint.push_back(pTemp);
			//g_EffectManager.Insert(9,D_LINE_START_X + (64.0f * m_Item_Lightning[i].m_nX),400.0f,2.0f,1.0f,90.0f);
		}
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Space.mp3");
		}
	}
	m_Item_Space.clear();
}

//!< ButtonCallBack

void GameScene::BackCallback(CCObject* pSender)
{
	if(m_eGameStep < E_GAMESTEP_END)
	{
		m_eGameStep = E_GAMESTEP_END;
		g_ComboManager.Exit();
	}
	DestroyScene();

	D_SCENE_CHANGE_EFFECT_UP(StageMenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
}




void GameScene::MenuCallback(CCObject* pSender)
{
	g_bPause = false;
	/*m_pBlind->setVisible(false);
	m_pPause->setVisible(false);
	m_pMenu->setPosition( ccp(ReturnWidth(120.0f), ReturnHeight(300.0f)));
	m_pMenu->setVisible(false);
	m_pRetry->setPosition(ccp(ReturnWidth(360.0f), ReturnHeight(300.0f)));
	m_pRetry->setVisible(false);
	m_pResume->setVisible(false);
*/

	D_SOUNDMNG->stopBackgroundMusic();
	
	if(m_eGameStep < E_GAMESTEP_END)
	{
		m_eGameStep = E_GAMESTEP_END;
		m_eGameResult = E_GAMERESULT_NONE;
		g_ComboManager.Exit();
	}
	DestroyScene();
	D_SCENE_CHANGE_EFFECT_FADE(StageMenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
}
void	GameScene::RetryCallback(CCObject* pSender)
{

	g_bPause = false;
	/*m_pBlind->setVisible(false);
	m_pPause->setVisible(false);
	m_pMenu->setPosition( ccp(ReturnWidth(120.0f), ReturnHeight(300.0f)));
	m_pMenu->setVisible(false);
	m_pRetry->setPosition(ccp(ReturnWidth(360.0f), ReturnHeight(300.0f)));
	m_pRetry->setVisible(false);
	m_pResume->setVisible(false);
*/
	g_EffectManager.Exit();
	g_LineManager.Exit();
	g_PlaneManager.Exit();
	g_NumberManager.Exit();
	// g_ComboManager.Exit();

	g_EffectManager.m_pEffectList.clear();
	g_LineManager.m_pEffectList.clear();
	g_PlaneManager.m_pPlaneList.clear();
	g_NumberManager.m_pNumberList.clear();
	// g_ComboManager.m_ComboList.clear();

	D_SOUNDMNG->stopBackgroundMusic();
	if(m_eGameStep < E_GAMESTEP_END)
	{
		m_eGameStep = E_GAMESTEP_END;
		m_eGameResult = E_GAMERESULT_NONE;
		g_ComboManager.Exit();
	}
	D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	DestroyScene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
}
void	GameScene::NextCallback(CCObject* pSender)
{
	/*m_pBlind->setVisible(false);
	m_pPause->setVisible(false);
	m_pMenu->setPosition( ccp(ReturnWidth(120.0f), ReturnHeight(300.0f)));
	m_pMenu->setVisible(false);
	m_pRetry->setPosition(ccp(ReturnWidth(360.0f), ReturnHeight(300.0f)));
	m_pRetry->setVisible(false);
	m_pResume->setVisible(false);*/

	if(m_eGameStep < E_GAMESTEP_END)
	{
		m_eGameStep = E_GAMESTEP_END;
		m_eGameResult = E_GAMERESULT_NONE;
		g_ComboManager.Exit();
	}
	D_SOUNDMNG->stopBackgroundMusic();
	DestroyScene();
	if(g_nStage < D_STAGE_MAX)
	{
		g_nStage++;
		D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
		CCDirector::sharedDirector()->replaceScene(pScene);
		if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
	}
}


void GameScene::Pause()
{
	if(g_bPause == false)
	{
		g_bPause = true;
		m_pBlind->setVisible(true);
		m_pPause->setVisible(true);
		//m_pMenu->setPosition(ccp(ReturnWidth(240.0f) * D_SCALE_WIDTH, ReturnHeight(500.0f)  * D_SCALE_HEIGHT));
		m_pMenu->setVisible(true);
		//m_pRetry->setPosition(ccp(ReturnWidth(240.0f) * D_SCALE_WIDTH, ReturnHeight(400.0f) * D_SCALE_HEIGHT));
		m_pRetry->setVisible(true);
		m_pResume.setVisible(true);
		if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect("Select.mp3"); }
		g_EffectManager.Pause();
		for(int i=0; i<g_nBlockMax; i++)
		{
			g_BlockList[i].Pause();
		}
	}
}
void GameScene::Resume()
{
	if(g_bPause == true)
	{
		g_bPause = false;
		m_pBlind->setVisible(false);
		m_pPause->setVisible(false);
		//m_pMenu->setPosition( ccp(ReturnWidth(120.0f) * D_SCALE_WIDTH, ReturnHeight(300.0f) * D_SCALE_HEIGHT));
		m_pMenu->setVisible(false);
		//m_pRetry->setPosition(ccp(ReturnWidth(360.0f) * D_SCALE_WIDTH, ReturnHeight(300.0f) * D_SCALE_HEIGHT));
		m_pRetry->setVisible(false);
		m_pResume.setVisible(false);
		if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect("Select.mp3"); }
		g_EffectManager.Resume();
		for(int i=0; i<g_nBlockMax; i++)
		{
			g_BlockList[i].Resume();
		}
	}
}


void GameScene::PauseCallBack(CCObject* pSender)
{
	if(m_eGameStep < E_GAMESTEP_END)
		Pause();
}
void GameScene::ResumeCallBack(CCObject* pSender)
{
	if(m_eGameStep < E_GAMESTEP_END)
		Resume();
}

bool GameScene::ItemNothing()
{
	if(m_Item_Lightning.size() <= 0 && m_Item_Bomb.size() <= 0 && m_Item_Space.size() <= 0)
		return true;

	return false;
}
void GameScene::DestroyScene()
{
	for(int i=0; i<m_ParticleList.size(); i++)
	{
		
		m_ParticleList[i]->emitter3->removeFromParentAndCleanup(true);
		delete m_ParticleList[i];
	}
	m_ParticleList.clear();

	//g_bPause = true;
	
}