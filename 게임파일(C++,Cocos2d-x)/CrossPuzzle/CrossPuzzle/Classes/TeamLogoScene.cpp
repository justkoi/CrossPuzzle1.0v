#include "stdafx.h"

USING_NS_CC;
CCScene* TeamLogoScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TeamLogoScene *layer = TeamLogoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float TeamLogoScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float TeamLogoScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}
// on "init" you need to initialize your instance
bool TeamLogoScene::init()
{

    


    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();
	
	
	char frameName[256];

	m_fTimer = 0.0f;

	/*

    m_pLogo = CCSprite::create("TeamLogo.png");

	m_pLogo->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pLogo->setScaleX(1.05f * D_SCALE_WIDTH);
	m_pLogo->setScaleY(1.05f * D_SCALE_HEIGHT);
*/
	/////////////////////////////////////////////////////
	m_pLogoAni = CCAnimation::animation();
	for(int j=0; j<19; j++) {
			sprintf(frameName, "TeamLogo_%d.png",j+1);
			m_pLogoAni->addSpriteFrameWithFileName(frameName);
	}
	m_pLogoAni->setDelayPerUnit(0.07f);
	m_pLogoAnt = CCAnimate::create(m_pLogoAni);
	m_pLogo = CCSprite::spriteWithFile("NewSprite.png");
	m_pLogo->setPosition( ccp(240.0f * D_SCALE_WIDTH, 400.0f * D_SCALE_HEIGHT));
	this->addChild(m_pLogo, 0);
	//m_pBlock->runAction(m_pBlockAnt);
	//CCAction::actionWithAction(m_pLogoAnt)
	m_pLogo->runAction(m_pLogoAnt);//CCRepeatForever::actionWithAction(m_pLogoAnt)
	m_pLogo->setAnchorPoint(ccp(0.5,0.5));
	m_pLogo->setScaleX(1.2f * D_SCALE_WIDTH);
	m_pLogo->setScaleY(1.2f * D_SCALE_HEIGHT);
	//////////////////////////////////////////////////////

    // this->addChild(m_pLogo, 0);
    
	
	
	this->schedule(schedule_selector(TeamLogoScene::Update), 0.0);

    return true;
}

void TeamLogoScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TeamLogoScene::Update(float dt)
{
	m_fTimer += dt;
	if(m_fTimer >= 2.0f && m_fTimer <= 10.0f)
	{
		m_fTimer = 11.0f;
		CCScene *pScene = CCTransitionFade::transitionWithDuration(1.0f,MenuScene::scene());
		//CCScene *pScene = CCTransitionCrossFade();
		CCDirector::sharedDirector()->replaceScene(pScene);
	
	}
	
}