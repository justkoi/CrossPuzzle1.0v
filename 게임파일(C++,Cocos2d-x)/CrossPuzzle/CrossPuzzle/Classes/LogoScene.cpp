#include "stdafx.h"

USING_NS_CC;
CCScene* LogoScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LogoScene *layer = LogoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float LogoScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float LogoScene::ReturnHeight(float fValue)
{
	//LogoScene* Logo = this;

	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}
// on "init" you need to initialize your instance
bool LogoScene::init()
{

    


    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();
	
	


	m_fTimer = 0.0f;

	

    m_pLogo = CCSprite::create("Logo.png");

	m_pLogo->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pLogo->setScaleX(1.05f * D_SCALE_WIDTH);
	m_pLogo->setScaleY(1.05f * D_SCALE_HEIGHT);

    this->addChild(m_pLogo, 0);
    
	
	
	this->schedule(schedule_selector(LogoScene::Update), 0.0);

    return true;
}

void LogoScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == popCC_PLATFORM_IOS)
    exit(0);
#endif
}

void LogoScene::Update(float dt)
{
	m_fTimer += dt;
	
	if(m_fTimer >= 1.5f && m_fTimer <= 10.0f)
	{
		m_fTimer = 11.0f;
		CCScene *pScene = CCTransitionFade::transitionWithDuration(1.0f,TeamLogoScene::scene());
		//CCScene *pScene = CCTransitionCrossFade();
		CCDirector::sharedDirector()->replaceScene(pScene);
	
	}
	
}