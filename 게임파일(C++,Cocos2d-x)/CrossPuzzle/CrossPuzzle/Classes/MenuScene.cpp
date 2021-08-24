#include "stdafx.h"

USING_NS_CC;
float m_fX = 100;
float m_fY = 0;
float m_fR = 100;

float g_fBGM_Volume = 1.0f;
float g_fEFFECT_Volume = 1.0f;

unsigned int g_unMenu_BGM = 0;
bool	g_bFirstPlayed = false;

CCScene* MenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MenuScene *layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float MenuScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float MenuScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}

void MenuScene::SaveOption()
{
	CCFileUtils FileUitil;
	string strTemp = FileUitil.getWriteablePath();
	strTemp.append("option.sav");
	
	FILE* fpw = fopen(strTemp.c_str(),"wb");
	
	fwrite(&g_bBGM_Sound,sizeof(bool),1,fpw);
	fwrite(&g_bEFFECT_Sound,sizeof(bool),1,fpw);


	fclose(fpw);
}
bool MenuScene::LoadOption()
{
	CCFileUtils FileUitil;
	string strTemp = FileUitil.getWriteablePath();
	strTemp.append("option.sav");

	FILE* fpr = fopen(strTemp.c_str(),"rb");

	if(fpr == NULL)
		return false;
	
	fread(&g_bBGM_Sound,sizeof(bool),1,fpr);
	fread(&g_bEFFECT_Sound,sizeof(bool),1,fpr);

	fclose(fpr);

	return true;
}
// on "init" you need to initialize your instance
bool MenuScene::init()
{
	


    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();

	bool bLoadResult = true;

	bLoadResult = LoadOption();

	if(bLoadResult == false)
	{
		SaveOption();
	}
	int nSygwin = 0;
	//g_EffectManager.Init(this);
	//
	//g_EffectManager.Exit();
	//g_LineManager.Exit();
	//g_PlaneManager.Exit();
	//g_NumberManager.Exit();
	//// g_ComboManager.Exit();

	//g_EffectManager.m_pEffectList.clear();
	//g_LineManager.m_pEffectList.clear();
	//g_PlaneManager.m_pPlaneList.clear();
	//g_NumberManager.m_pNumberList.clear();
	//// g_ComboManager.m_ComboList.clear();

	this->setTouchEnabled(true);

	//!< 게임시작시 로딩
	g_EffectManager.Init(this);
	g_EffectManager.Insert(1,-100,-100);
	g_EffectManager.Insert(2,-100,-100);
	g_EffectManager.Insert(3,-100,-100);
	g_EffectManager.Insert(4,-100,-100);
	g_EffectManager.Insert(5,-100,-100);
	g_EffectManager.Insert(6,-100,-100);
	g_EffectManager.Exit();
	g_EffectManager.m_pEffectList.clear();



    m_pSprite = CCSprite::create("MainMenu.png");
	m_pSprite->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pSprite->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pSprite->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pSprite[0]->setColor(ccc3(255 * 0.9f, 255 * 1.0f, 255 * 0.9f));
    this->addChild(m_pSprite, 0);
	


	m_pTitle = CCSprite::create("Title.png");
	m_pTitle->setPosition( ccp( D_MENU_TITLE_X * D_SCALE_WIDTH, D_MENU_TITLE_Y  * D_SCALE_HEIGHT) );
	m_pTitle->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pTitle->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pTitle, 12);





	m_pPopUp = CCSprite::create("PopUp_Option.png");
	m_pPopUp->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pPopUp->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pPopUp->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pPopUp->setVisible(false);
    this->addChild(m_pPopUp, 31);
	

	m_pBlind = CCSprite::create("Blind.png");
	m_pBlind->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBlind->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBlind->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBlind->setOpacity(255 * 0.8f);
	m_pBlind->setVisible(false);
    this->addChild(m_pBlind, 30);



	//m_pGameStartItem = CCMenuItemImage::create(
 //                                       "Button_Start_1.png",
 //                                       "Button_Start_3.png",
 //                                       this,
 //                                       menu_selector(MenuScene::GameStartCallback) );
	//m_pGameStartItem->setPosition( ccp(ReturnWidth(240), ReturnHeight(500) ) );

 //   // create menu, it's an autorelease object
 //   m_pGameStart = CCMenu::create(m_pGameStartItem, NULL);
	//m_pGameStart->setPosition( CCPointZero );
	//m_pGameStart->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pGameStart->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pGameStart->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pGameStart, 3);

	m_pGameStart.Init(this,3,"Button_Start_1.png","Button_Start_3.png",ccp(240 * D_SCALE_WIDTH, 500 * D_SCALE_HEIGHT));
	m_pOption.Init(this,3,"Button_Option_1.png","Button_Option_3.png",ccp(240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	m_pCredit.Init(this,3,"Button_Credit_1.png","Button_Credit_3.png",ccp(240 * D_SCALE_WIDTH, 300 * D_SCALE_HEIGHT));
	m_pExit.Init(this,3,"Button_Exit_1.png","Button_Exit_3.png",ccp(240 * D_SCALE_WIDTH, 200 * D_SCALE_HEIGHT));
	m_pCancel.Init(this,32,"Button_Cancel_1.png","Button_Cancel_3.png",ccp(360 * D_SCALE_WIDTH, 500 * D_SCALE_HEIGHT));
	m_pEffect.Init(this,32,"Button_Effect_1.png","Button_Effect_3.png",ccp(290 * D_SCALE_WIDTH, 360 * D_SCALE_HEIGHT));
	m_pBGM.Init(this,32,"Button_BGM_1.png","Button_BGM_3.png",ccp(190 * D_SCALE_WIDTH, 360 * D_SCALE_HEIGHT));
	


	//
	//m_pOptionItem = CCMenuItemImage::create(
 //                                       "Button_Option_1.png",
 //                                       "Button_Option_3.png",
 //                                       this,
 //                                       menu_selector(MenuScene::OptionCallback) );
	//m_pOptionItem->setPosition( ccp(ReturnWidth(240), ReturnHeight(400) ));

 //   // create menu, it's an autorelease object
 //   m_pOption = CCMenu::create(m_pOptionItem, NULL);
	//m_pOption->setPosition( CCPointZero );
	//m_pOption->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pOption->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pOption->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pOption, 3);
	//


	//
	//
	//m_pCreditItem = CCMenuItemImage::create(
 //                                       "Button_Credit_1.png",
 //                                       "Button_Credit_3.png",
 //                                       this,
 //                                       menu_selector(MenuScene::CreditCallback) );
	//m_pCreditItem->setPosition( ccp(ReturnWidth(240), ReturnHeight(300)) );
 //   m_pCredit = CCMenu::create(m_pCreditItem, NULL);
	//m_pCredit->setPosition( CCPointZero );
	//m_pCredit->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pCredit->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pCredit->setAnchorPoint(ccp(0.5f,0.5f));
 //   this->addChild(m_pCredit, 3);


	//
	//m_pExitItem = CCMenuItemImage::create(
 //                                       "Button_Exit_1.png",
 //                                       "Button_Exit_3.png",
 //                                       this,
 //                                       menu_selector(MenuScene::ExitCallback) );
	//m_pExitItem->setPosition( ccp(ReturnWidth(240), ReturnHeight(200)) );

 //   // create menu, it's an autorelease object
 //   m_pExit = CCMenu::create(m_pExitItem, NULL);
	//m_pExit->setPosition( CCPointZero );
	//m_pExit->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pExit->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pExit->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pExit, 3);

	//
	//m_pCancelItem = CCMenuItemImage::create(
 //                                       "Button_Cancel_1.png",
 //                                       "Button_Cancel_3.png",
 //                                       this,
 //                                       menu_selector(MenuScene::CancelCallback) );
	//m_pCancelItem->setPosition( ccp(ReturnWidth(360), ReturnHeight(500)) );

 //   // create menu, it's an autorelease object
	//m_pCancel = CCMenu::create(m_pCancelItem, NULL);
	//m_pCancel->setPosition( CCPointZero );
	//m_pCancel->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pCancel->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pCancel->setVisible(false);
	//m_pCancel->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pCancel, 32);

	//
	//
	//m_pEffectItem = CCMenuItemImage::create(
 //                                       "Button_Effect_1.png",
 //                                       "Button_Effect_3.png",
 //                                       this,
 //                                       menu_selector(MenuScene::EFFECT_Callback) );
	//m_pEffectItem->setPosition( ccp(ReturnWidth(290), ReturnHeight(360)) );

 //   // create menu, it's an autorelease object
 //   m_pEffect = CCMenu::create(m_pEffectItem, NULL);
	//m_pEffect->setPosition( CCPointZero );
	//m_pEffect->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pEffect->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pEffect->setVisible(false);
	//m_pEffect->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pEffect, 32);

	//
	//
	//m_pBGMItem = CCMenuItemImage::create(
 //                                       "Button_BGM_1.png",
 //                                       "Button_BGM_3.png",
 //                                       this,
 //                                       menu_selector(MenuScene::BGM_Callback) );
	//m_pBGMItem->setPosition( ccp(ReturnWidth(190), ReturnHeight(360)) );

 //   // create menu, it's an autorelease object
 //   m_pBGM = CCMenu::create(m_pBGMItem, NULL);
	//m_pBGM->setPosition( CCPointZero );
	//m_pBGM->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pBGM->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pBGM->setVisible(false);
	//m_pBGM->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pBGM, 32);

	m_bPopUp = false;

	

	D_SOUNDMNG->preloadEffect("BlockPop_1.mp3");
	D_SOUNDMNG->preloadEffect("Line.mp3");
	D_SOUNDMNG->preloadEffect("Triangle.mp3");
	D_SOUNDMNG->preloadEffect("Square.mp3");
	D_SOUNDMNG->preloadEffect("Pentagon.mp3");
	D_SOUNDMNG->preloadEffect("Hexagon.mp3");
	D_SOUNDMNG->preloadEffect("Lightning.mp3");
	D_SOUNDMNG->preloadEffect("Bomb.mp3");
	D_SOUNDMNG->preloadEffect("Fever.mp3");
	D_SOUNDMNG->preloadEffect("Combo.mp3");
	D_SOUNDMNG->preloadEffect("Select.mp3");
	D_SOUNDMNG->preloadEffect("BlockSelect.mp3");
	D_SOUNDMNG->preloadEffect("Clear.mp3");
	D_SOUNDMNG->preloadEffect("Over.mp3");
	D_SOUNDMNG->preloadEffect("Out.mp3");
	D_SOUNDMNG->preloadEffect(D_BUTTON_SOUND);

	D_SOUNDMNG->preloadBackgroundMusic("Menu_BGM.mp3");
	//D_SOUNDMNG->playBackgroundMusic("Game_BGM_1.mp3",true);

	//D_SOUNDMNG->preloadBackgroundMusic("Menu_BGM.mp3");
	if(g_bBGM_Sound == true)
	{
		//D_SOUNDMNG->playBackgroundMusic("Menu_BGM.mp3", true);
		if(g_bFirstPlayed == false)
		{
			g_bFirstPlayed = true;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
			D_SOUNDMNG->playBackgroundMusic("Menu_BGM.mp3",true);
		}
	}

	
	CCParticleSystem *emitter3;
	emitter3 = CCParticleGalaxy::node();
    emitter3->setTexture(CCTextureCache::sharedTextureCache()->addImage("Particle1.png"));
	emitter3->setTotalParticles(150);
    emitter3->setAutoRemoveOnFinish(true);
	emitter3->setLife(5.0f);
	emitter3->setLifeVar(2.5f);
	emitter3->setPosition(ccp( 240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	emitter3->setGravity(ccp(0,0));
	emitter3->setStartColor(ccc4f(1.0f, 1.0f, 1.0f, 1.0f));
	emitter3->setEndColor(ccc4f(1.0f, 1.0f, 1.0f, 0.0f));
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter3->setScale(1.0f);
    emitter3->setStartSize(15.0f);
    emitter3->setEndSize(15.0f);
    emitter3->setDuration(60.0f);
    emitter3->setSpeed(200);
    emitter3->setSpeedVar(100);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter3->setEmissionRate(250.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
    this->addChild(emitter3);
	//CCParticleSystem *emitter;
	//emitter = CCParticleFire::node();
 //   emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	//emitter->setTotalParticles(250);
 //   emitter->setAutoRemoveOnFinish(true);
	//emitter->setLife(1.0f);
	//emitter->setLifeVar(0.5f);
	//emitter->setPosition(ccp( 220 * D_SCALE_WIDTH, 300 * D_SCALE_HEIGHT));
	//emitter->setGravity(ccp(0,0));
	////emitter->setRotatePerSecond(10.0f);
	////emitter->setRotatePerSecondVar(20.0f);
	//emitter->setScale(1.0f);
 //   emitter->setStartSize(30.0f);
 //   emitter->setEndSize(30.0f);
 //   emitter->setDuration(60.0f);
 //   emitter->setSpeed(100);
 //   emitter->setSpeedVar(25);
	////emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	//emitter->setEmissionRate(500.0f);
	////emitter->setAngle(0.0f);
	////emitter->setAngleVar(360.0f);
 //   //this->addChild(emitter);

	//CCParticleSystem *emitter2;
	//emitter2 = CCParticleFire::node();
 //   emitter2->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	//emitter2->setTotalParticles(250);
 //   emitter2->setAutoRemoveOnFinish(true);
	//emitter2->setLife(1.0f);
	//emitter2->setLifeVar(0.5f);
	//emitter2->setPosition(ccp( 260 * D_SCALE_WIDTH, 300 * D_SCALE_HEIGHT));
	//emitter2->setGravity(ccp(0,0));
	////emitter->setRotatePerSecond(10.0f);
	////emitter->setRotatePerSecondVar(20.0f);
	//emitter2->setScale(1.0f);
 //   emitter2->setStartSize(30.0f);
 //   emitter2->setEndSize(30.0f);
 //   emitter2->setDuration(60.0f);
 //   emitter2->setSpeed(100);
 //   emitter2->setSpeedVar(25);
	////emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	//emitter2->setEmissionRate(500.0f);
	////emitter->setAngle(0.0f);
	////emitter->setAngleVar(360.0f);
 //   //this->addChild(emitter2);

	//CCParticleSystem *emitter3;
	//emitter3 = CCParticleSnow::node();
 //   emitter3->setTexture(CCTextureCache::sharedTextureCache()->addImage("Particle1.png"));
	//emitter3->setTotalParticles(20);
 //   emitter3->setAutoRemoveOnFinish(true);
	//emitter3->setLife(30.0f);
	//emitter3->setLifeVar(2.5f);
	//emitter3->setPosition(ccp( 240 * D_SCALE_WIDTH, 900 * D_SCALE_HEIGHT));
	//emitter3->setGravity(ccp(0,0));
	////emitter->setRotatePerSecond(10.0f);
	////emitter->setRotatePerSecondVar(20.0f);
	//emitter3->setScale(1.0f);
 //   emitter3->setStartSize(25.0f);
 //   emitter3->setEndSize(25.0f);
 //   emitter3->setDuration(60.0f);
 //   emitter3->setSpeed(20);
 //   emitter3->setSpeedVar(2);
	//emitter3->setStartColor(ccc4f(1.0f,1.0f,1.0f,0.6f));
	//emitter3->setEndColor(ccc4f(1.0f,1.0f,1.0f,0.6f));
	////emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	//emitter3->setEmissionRate(0.6f);
	////emitter->setAngle(0.0f);
	////emitter->setAngleVar(360.0f);
 //  // this->addChild(emitter3);

	


	this->schedule(schedule_selector(MenuScene::Update), 0.0);

	m_fTimer = 0.0f;
	m_fRotationTimer = 0.0f;
	m_fBackGroundTimer = 0.0f;
    return true;
}

void MenuScene::Update(float dt)
{
	m_fTimer += dt;
	m_fRotationTimer += dt;
	m_fBackGroundTimer += dt;

	m_pPopUp->setVisible(m_bPopUp);
	m_pBlind->setVisible(m_bPopUp);

	m_pCancel.setVisible(m_bPopUp);
	m_pEffect.setVisible(m_bPopUp);
	m_pBGM.setVisible(m_bPopUp);

	m_pGameStart.Update(dt);
	m_pOption.Update(dt);
	m_pCredit.Update(dt);
	m_pExit.Update(dt);
	m_pCancel.Update(dt);
	m_pBGM.Update(dt);
	m_pEffect.Update(dt);


	if(m_pGameStart.CheckAction() == true)
	{
		GameStartCallback(NULL);
		m_pGameStart.CheckActioned();
	}
	if(m_pOption.CheckAction() == true)
	{
		m_pOption.Reset();
		OptionCallback(NULL);
		//m_pOption.CheckActioned();
	}
	if(m_pCredit.CheckAction() == true)
	{
		CreditCallback(NULL);
		m_pCredit.CheckActioned();
	}
	if(m_pExit.CheckAction() == true)
	{
		ExitCallback(NULL);
		m_pExit.CheckActioned();
	}
	if(m_pCancel.CheckAction() == true)
	{
		m_pCancel.Reset();
		CancelCallback(NULL);
		//m_pCancel.CheckActioned();
	}
	if(m_pBGM.CheckAction() == true)
	{
		m_pBGM.Reset();
		BGM_Callback(NULL);
		//m_pBGM.CheckActioned();
	}
	
	if(m_pEffect.CheckAction() == true)
	{
		m_pEffect.Reset();
		EFFECT_Callback(NULL);
		//m_pEffect.CheckActioned();
	}



	//m_pGameStart->setVisible(!m_bPopUp);
	//m_pOption->setVisible(!m_bPopUp);

	if(g_bBGM_Sound == true)
	{
		m_pBGM.setColor(ccc3(255 * 1.0f,255 * 1.0f,255 * 1.0f));
	}
	else
	{
		m_pBGM.setColor(ccc3(255 * 0.3f,255 * 0.5f,255 * 0.3f));
	}

	if(g_bEFFECT_Sound == true)
	{
		m_pEffect.setColor(ccc3(255 * 1.0f,255 * 1.0f,255 * 1.0f));
	}
	else
	{
		m_pEffect.setColor(ccc3(255 * 0.3f,255 * 0.5f,255 * 0.3f));
	}




	if(m_fBackGroundTimer >= 4.0f)
	{
		m_fBackGroundTimer -= 4.0f;
	}
	if(m_fTimer <= 1.0f)
	{
		
		m_pTitle->setScaleX((1.0f + (m_fTimer/10)) * D_SCALE_WIDTH);
		m_pTitle->setScaleY((1.0f + (m_fTimer/10)) * D_SCALE_HEIGHT);

	}
	else
	{
		
		m_pTitle->setScaleX((1.1f - ((m_fTimer-1.0f)/20))  * D_SCALE_WIDTH);
		m_pTitle->setScaleY((1.1f - ((m_fTimer-1.0f)/20))  * D_SCALE_HEIGHT);
	}
		if(m_fTimer >= 3.0f)
	{
		m_fTimer -= 3.0f;
	}
}

void MenuScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MenuScene::GameStartCallback(CCObject* pSender)
{
   if(m_bPopUp == false)
   {
		//g_EffectManager.Exit();
		//g_EffectManager.m_pEffectList.clear();

		//char frameName[256];
		//CCAnimation* m_pBlockAni;
		//CCActionInterval * m_pBlockAnt;
		//CCSprite * m_pBlock;
		//stAnimation* pTempAni;

		//m_pBlockAni = CCAnimation::animation();
		//for(int j=2; j<46; j++) {
		//		sprintf(frameName, "Transport/Transport_00%d.png",j);
		//		m_pBlockAni->addSpriteFrameWithFileName(frameName);
		//}
		//m_pBlockAni->setDelayPerUnit(2.0f/60.0f);
		//m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		//m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		//m_pBlock->setPosition( ccp(240.0f * D_SCALE_WIDTH, 280.0f * D_SCALE_HEIGHT));
		//m_pBlock->setScaleX( 1.2f * D_SCALE_WIDTH);
		//m_pBlock->setScaleY( 1.2f * D_SCALE_HEIGHT);
		////m_pBlock->setColor(ccc3(125 * 1.0f, 52 * 1.0f, 6 * 1.0f));
	
		////m_pBlock->runAction(m_pBlockAnt);
		//m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		//m_pBlock->setAnchorPoint(ccp(0.5,0.5));
		//addChild(m_pBlock, 2);
		D_SCENE_CHANGE_EFFECT_DOWN(LevelMenuScene::scene());
		CCDirector::sharedDirector()->replaceScene(pScene);
		if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
	}
}


void MenuScene::CreditCallback(CCObject* pSender)
{
  if(m_bPopUp == false)
  {
	D_SCENE_CHANGE_EFFECT_DOWN(CreditScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
  }
}

void MenuScene::ExitCallback(CCObject* pSender)
{
	if(m_bPopUp == false)
    {
	
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
	}
}

void MenuScene::OptionCallback(CCObject* pSender)
{
  if(m_bPopUp == false)
  {
	  m_bPopUp = true;
	  if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect("Select.mp3"); }
  }
}

void MenuScene::CancelCallback(CCObject* pSender)
{
  if(m_bPopUp == true)
  {
	  m_bPopUp = false;
	  SaveOption();
	  if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect("Select.mp3"); }
  }
}
void MenuScene::BGM_Callback(CCObject* pSender)
{
	g_bBGM_Sound = !g_bBGM_Sound;
	if(g_bBGM_Sound == false)
	{
		D_SOUNDMNG->pauseBackgroundMusic();
	}
	else if(g_bBGM_Sound == true)
	{
		D_SOUNDMNG->resumeBackgroundMusic();
	}
	if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect("Select.mp3"); }
	SaveOption();
}
void MenuScene::EFFECT_Callback(CCObject* pSender)
{
	g_bEFFECT_Sound = !g_bEFFECT_Sound;
	SaveOption();
	if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect("Select.mp3"); }
}


void MenuScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool MenuScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());

	if(m_bPopUp == false)
	{
		m_pGameStart.TouchBegan(stPos);
		m_pOption.TouchBegan(stPos);
		m_pCredit.TouchBegan(stPos);
		m_pExit.TouchBegan(stPos);
	}
	else if(m_bPopUp == true)
	{
		m_pCancel.TouchBegan(stPos);
		m_pBGM.TouchBegan(stPos);
		m_pEffect.TouchBegan(stPos);
	}
	/*if(stPos.y >= 487.5f && stPos.y <= 512.5f)
	{
		if(stPos.x >= 115.0f && stPos.x <= 365.0f)
		{
			g_fBGM_Volume = ((stPos.x - 115.0f) / 250.0f);
			if(g_fBGM_Volume <= 0.02f)
				g_fBGM_Volume = 0.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
		else if(stPos.x < 115.0f)
		{
			g_fBGM_Volume = 0.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
		else if(stPos.x > 365.0f)
		{
			g_fBGM_Volume = 1.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
	}
	else if(stPos.y >= 387.5f && stPos.y <= 412.5f)
	{
		if(stPos.x >= 115.0f && stPos.x <= 365.0f)
		{
			g_fEFFECT_Volume = ((stPos.x - 115.0f) / 250.0f);
			if(g_fEFFECT_Volume <= 0.02f)
				g_fEFFECT_Volume = 0.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
		else if(stPos.x < 115.0f)
		{
			g_fEFFECT_Volume = 0.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
		else if(stPos.x > 365.0f)
		{
			g_fEFFECT_Volume = 1.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
	}*/
	return true;
}
void   MenuScene::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
	
	/*if(stPos.y >= 475.0f && stPos.y <= 525.0f)
	{
		if(stPos.x >= 115.0f && stPos.x <= 365.0f)
		{
			g_fBGM_Volume = ((stPos.x - 115.0f) / 250.0f);
			if(g_fBGM_Volume <= 0.02f)
				g_fBGM_Volume = 0.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
		else if(stPos.x < 115.0f)
		{
			g_fBGM_Volume = 0.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
		else if(stPos.x > 365.0f)
		{
			g_fBGM_Volume = 1.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
	}
	else if(stPos.y >= 375.0f && stPos.y <= 425.0f)
	{
		if(stPos.x >= 115.0f && stPos.x <= 365.0f)
		{
			g_fEFFECT_Volume = ((stPos.x - 115.0f) / 250.0f);
			if(g_fEFFECT_Volume <= 0.02f)
				g_fEFFECT_Volume = 0.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
		else if(stPos.x < 115.0f)
		{
			g_fEFFECT_Volume = 0.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
		else if(stPos.x > 365.0f)
		{
			g_fEFFECT_Volume = 1.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
	}*/
}

void  MenuScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
	if(m_bPopUp == false)
	{
		m_pGameStart.TouchEnded(stPos);
		m_pOption.TouchEnded(stPos);
		m_pCredit.TouchEnded(stPos);
		m_pExit.TouchEnded(stPos);
	}
	else if(m_bPopUp == true)
	{
		m_pCancel.TouchEnded(stPos);
		m_pBGM.TouchEnded(stPos);
		m_pEffect.TouchEnded(stPos);
	}

	/*if(stPos.y >= 475.0f && stPos.y <= 525.0f)
	{
		if(stPos.x >= 115.0f && stPos.x <= 365.0f)
		{
			g_fBGM_Volume = ((stPos.x - 115.0f) / 250.0f);
			if(g_fBGM_Volume <= 0.02f)
				g_fBGM_Volume = 0.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
		else if(stPos.x < 115.0f)
		{
			g_fBGM_Volume = 0.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
		else if(stPos.x > 365.0f)
		{
			g_fBGM_Volume = 1.0f;
			D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		}
		SaveOption();
	}
	else if(stPos.y >= 375.0f && stPos.y <= 425.0f)
	{
		if(stPos.x >= 115.0f && stPos.x <= 365.0f)
		{
			g_fEFFECT_Volume = ((stPos.x - 115.0f) / 250.0f);
			if(g_fEFFECT_Volume <= 0.02f)
				g_fEFFECT_Volume = 0.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
		else if(stPos.x < 115.0f)
		{
			g_fEFFECT_Volume = 0.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
		else if(stPos.x > 365.0f)
		{
			g_fEFFECT_Volume = 1.0f;
			D_SOUNDMNG->setEffectsVolume(g_fEFFECT_Volume);
		}
		SaveOption();
	}*/
}