#include "stdafx.h"

#define RadToDeg(x) (57.29577951f * x)
#define DegToRad(x) (0.017453293f * x)

USING_NS_CC;

int g_nLevel = 1; //!< 1 ,2 , 3

CCScene* LevelMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LevelMenuScene *layer = LevelMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float LevelMenuScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float LevelMenuScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}

// on "init" you need to initialize your instance
bool LevelMenuScene::init()
{
	

    if ( !CCLayer::init() )
    {
        return false;
    }

	this->setTouchEnabled(true);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();

	
	
    m_pBackGround = CCSprite::create("LevelMenu.png");
	m_pBackGround->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGround->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGround->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pBackGround, 0);

	
    m_pBackGroundLight = CCSprite::create("MenuLight_1.png");
	m_pBackGroundLight->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGroundLight->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGroundLight->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBackGroundLight->setColor(ccc3(255 * 0.5f,255 * 1.0f,255 * 1.0f));
    this->addChild(m_pBackGroundLight, 1);

	
	
	m_pEasy.Init(this,2,"Button_Easy_1.png","Button_Easy_3.png",ccp(240 * D_SCALE_WIDTH, 650 * D_SCALE_HEIGHT));
	m_pNormal.Init(this,2,"Button_Normal_1.png","Button_Normal_3.png",ccp(240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	m_pHard.Init(this,2,"Button_Hard_1.png","Button_Hard_3.png",ccp(240 * D_SCALE_WIDTH, 150 * D_SCALE_HEIGHT));
	m_pBack.Init(this,31,"Button_Back_1.png","Button_Back_3.png",ccp(60 * D_SCALE_WIDTH, 35 * D_SCALE_HEIGHT));
	
	/*
	m_pBackItem = CCMenuItemImage::create(
                                        "Button_Back_1.png",
                                        "Button_Back_3.png",
                                        this,
                                        menu_selector(LevelMenuScene::BackCallback) );
    m_pBackItem->setPosition( ccp( ReturnWidth(50), ReturnHeight(25)) );
    m_pBack = CCMenu::create(m_pBackItem, NULL);

	m_pBack->setPosition( CCPointZero );
	m_pBack->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBack->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pBack, 31);
*/

	//m_pEasyItem = CCMenuItemImage::create(
 //                                       "Button_Easy_1.png",
 //                                       "Button_Easy_3.png",
 //                                       this,
 //                                       menu_selector(LevelMenuScene::EasyCallback) );
	//m_pEasyItem->setPosition( ccp(ReturnWidth(240), ReturnHeight(650) ) );

 //   // create menu, it's an autorelease object
 //   m_pEasy = CCMenu::create(m_pEasyItem, NULL);
	//m_pEasy->setPosition( CCPointZero );
	//m_pEasy->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pEasy->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pEasy->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pEasy, 2);

	//
	//m_pNormalItem = CCMenuItemImage::create(
 //                                       "Button_Normal_1.png",
 //                                       "Button_Normal_3.png",
 //                                       this,
 //                                       menu_selector(LevelMenuScene::NormalCallback) );
	//m_pNormalItem->setPosition( ccp(ReturnWidth(240), ReturnHeight(400) ) );

 //   // create menu, it's an autorelease object
	//m_pNormal = CCMenu::create(m_pNormalItem, NULL);
	//m_pNormal->setPosition( CCPointZero );
	//m_pNormal->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pNormal->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pNormal->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pNormal, 2);


	//
	//m_pHardItem = CCMenuItemImage::create(
 //                                       "Button_Hard_1.png",
 //                                       "Button_Hard_3.png",
 //                                       this,
 //                                       menu_selector(LevelMenuScene::HardCallback) );
	//m_pHardItem->setPosition( ccp(ReturnWidth(240), ReturnHeight(150) ) );

 //   // create menu, it's an autorelease object
 //   m_pHard = CCMenu::create(m_pHardItem, NULL);
	//m_pHard->setPosition( CCPointZero );
	//m_pHard->setScaleX(1.00f * D_SCALE_WIDTH);
	//m_pHard->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pHard->setAnchorPoint(ccp(0.5f,0.5f));

 //   this->addChild(m_pHard, 2);


	//D_SOUNDMNG->preloadBackgroundMusic("Menu_BGM.mp3");
	//if(g_bBGM_Sound == true)
		//D_SOUNDMNG->playBackgroundMusic("Menu_BGM.mp3", true);


	
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

	


	this->schedule(schedule_selector(LevelMenuScene::Update), 0.0);

	m_fTimer = 0.0f;
	m_fLightTimer = 0.0f;
	m_nLightLevel = 1;

    return true;
}

void LevelMenuScene::Update(float dt)
{
	m_fTimer += dt;
	m_fLightTimer += dt * 3;

	static float fR = 1.0f;
	static float fG = 1.0f;
	static float fB = 1.0f;

	m_pEasy.Update(dt);
	m_pNormal.Update(dt);
	m_pHard.Update(dt);

	m_pBack.Update(dt);
	if(m_pBack.CheckAction() == true)
	{
		BackCallback(NULL);
		m_pBack.CheckActioned();
	}

	if(m_pEasy.CheckAction() == true)
	{
		EasyCallback(NULL);
		m_pEasy.CheckActioned();
	}
	if(m_pNormal.CheckAction() == true)
	{
		NormalCallback(NULL);
		m_pNormal.CheckActioned();
	}
	if(m_pHard.CheckAction() == true)
	{
		HardCallback(NULL);
		m_pHard.CheckActioned();
	}
	
	if(m_fLightTimer < 3.0f)
	{
		fR = 0.5f + (m_fLightTimer/6); //1.0f
		fG = 0.5f; //0.5f
		fB = 1.0f - (m_fLightTimer/6); //0.5f
	}
	else if(m_fLightTimer >= 3.0f && m_fLightTimer < 6.0f)
	{
		float m_fLightValue = m_fLightTimer - 3.0f;
		fR = 1.0f - (m_fLightValue/6);// 0.5f
		fG = 0.5f + (m_fLightValue/6);// 1.0f
		fB = 0.5f;					  // 0.5f
	}
	else if(m_fLightTimer >= 6.0f && m_fLightTimer < 9.0f)
	{
		float m_fLightValue = m_fLightTimer - 6.0f;
		fR = 0.5f;// 0.5f
		fG = 1.0f - (m_fLightValue/6);// 0.5f
		fB = 0.5f + (m_fLightValue/6); // 1.0f
	}
	m_pBackGroundLight->setColor(ccc3(255 * fR, 255 * fG, 255 * fB));
	
	
	if(m_fLightTimer >= 9.0f)
	{
		m_fLightTimer = 0.0f;
	}
}

void LevelMenuScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void LevelMenuScene::EasyCallback(CCObject* pSender)
{
	g_nLevel = 1;
	
	D_SCENE_CHANGE_EFFECT_DOWN(StageMenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
}

void LevelMenuScene::NormalCallback(CCObject* pSender)
{
	g_nLevel = 2;
	D_SCENE_CHANGE_EFFECT_DOWN(StageMenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
}

void LevelMenuScene::HardCallback(CCObject* pSender)
{
	g_nLevel = 3;
	D_SCENE_CHANGE_EFFECT_DOWN(StageMenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
}
void LevelMenuScene::BackCallback(CCObject* pSender)
{
   // CCDirector::sharedDirector()->end();
	//CCScene *pScene = CCTransitionEaseScene::transitionWithDuration(1,GameScene::scene());
	D_SCENE_CHANGE_EFFECT_UP(MenuScene::scene());
	//CCScene *pScene = CCTransitionCrossFade();
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect("StageStart.mp3"); }
}

void LevelMenuScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool LevelMenuScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());

	m_pEasy.TouchBegan(stPos);
	m_pNormal.TouchBegan(stPos);
	m_pHard.TouchBegan(stPos);
	m_pBack.TouchBegan(stPos);
	
	
	return true;
}
void   LevelMenuScene::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
}

void  LevelMenuScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
	m_pEasy.TouchEnded(stPos);
	m_pNormal.TouchEnded(stPos);
	m_pHard.TouchEnded(stPos);
	m_pBack.TouchEnded(stPos);
	
}