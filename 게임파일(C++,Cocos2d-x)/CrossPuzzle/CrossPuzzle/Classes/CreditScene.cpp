#include "stdafx.h"

USING_NS_CC;
CCScene* CreditScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CreditScene *layer = CreditScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float CreditScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float CreditScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}
// on "init" you need to initialize your instance
bool CreditScene::init()
{

    


    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	this->setTouchEnabled(true);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();
	
	
	
	D_SOUNDMNG->preloadBackgroundMusic("Credit.mp3");
	if(g_bBGM_Sound == true)
	{
		D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		D_SOUNDMNG->playBackgroundMusic("Credit.mp3",true);
		g_bFirstPlayed = false;
	}


    m_pBackGround = CCSprite::create("LevelMenu.png");
	m_pBackGround->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGround->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGround->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pBackGround, 0);


	m_pBack.Init(this,31,"Button_Back_1.png","Button_Back_3.png",ccp(60 * D_SCALE_WIDTH, 35 * D_SCALE_HEIGHT));
	
	g_EffectManager.Init(this);

	m_fTimer = 0.0f;
	g_nIndex = 0;


	
    AddCreditBlock(ccp(25.6f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),0.5f,"CreditBlock_1.png"); //0
    AddCreditBlock(ccp(99.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),0.7f,"CreditBlock_2.png"); //1
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),0.9f,"CreditBlock_3.png");//2
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),1.1f,"CreditBlock_4.png");//3
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),1.3f,"CreditBlock_5.png");//4

	
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),1.6f,"CreditBlock2_1.png");//5
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),1.8f,"CreditBlock2_2.png");//6
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),2.0f,"CreditBlock2_3.png");//7

	
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),4.0f,"CreditBlock3_1.png");//8
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),4.2f,"CreditBlock3_2.png");//9
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),4.4f,"CreditBlock3_3.png");//10
	
    AddCreditBlock(ccp(25.6f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),6.0f,"CreditBlock4_1.png");//11
    AddCreditBlock(ccp(99.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),6.2f,"CreditBlock4_2.png");//12
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),6.4f,"CreditBlock4_3.png");//13
	
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),6.7f,"CreditBlock5_1.png");//14
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),6.9f,"CreditBlock5_2.png");//15
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),7.1f,"CreditBlock5_3.png");//16
	
    AddCreditBlock(ccp(99.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),8.7f,"CreditBlock6_1.png");//17
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(300.0f),8.9f,"CreditBlock6_2.png");//18
	
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),9.2f,"CreditBlock7_1.png");//19
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),9.4f,"CreditBlock7_2.png");//20
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(450.0f),9.6f,"CreditBlock7_3.png");//21
	
	//////////////

	//프밍
    AddCreditBlock(ccp(25.6f + 32.0f,950.0f),D_PHOTOSHOP_Y(70.0f - 32.0f),11.0f,"CreditBlock_1.png"); //0
    AddCreditBlock(ccp(99.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(70.0f - 32.0f),11.0f,"CreditBlock_2.png"); //1
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(70.0f - 32.0f),11.0f,"CreditBlock_3.png");//2
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(70.0f - 32.0f),11.0f,"CreditBlock_4.png");//3
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(70.0f - 32.0f),11.0f,"CreditBlock_5.png");//4

	
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(170.0f - 32.0f),11.0f,"CreditBlock2_1.png");//5
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(170.0f - 32.0f),11.0f,"CreditBlock2_2.png");//6
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(170.0f - 32.0f),11.0f,"CreditBlock2_3.png");//7

	//곽민석
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(270.0f - 32.0f),11.0f,"CreditBlock3_1.png");//8
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(270.0f - 32.0f),11.0f,"CreditBlock3_2.png");//9
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(270.0f - 32.0f),11.0f,"CreditBlock3_3.png");//10
	
	//그래픽
    AddCreditBlock(ccp(25.6f + 32.0f,950.0f),D_PHOTOSHOP_Y(370.0f - 32.0f),11.0f,"CreditBlock4_1.png");//11
    AddCreditBlock(ccp(99.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(370.0f - 32.0f),11.0f,"CreditBlock4_2.png");//12
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(370.0f - 32.0f),11.0f,"CreditBlock4_3.png");//13
	//김소원
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(470.0f - 32.0f),11.0f,"CreditBlock5_1.png");//14
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(470.0f - 32.0f),11.0f,"CreditBlock5_2.png");//15
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(470.0f - 32.0f),11.0f,"CreditBlock5_3.png");//16
	
    AddCreditBlock(ccp(99.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(570.0f - 32.0f),11.0f,"CreditBlock6_1.png");//17
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(570.0f - 32.0f),11.0f,"CreditBlock6_2.png");//18
	
    AddCreditBlock(ccp(172.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(670.0f - 32.0f),11.0f,"CreditBlock7_1.png");//19
    AddCreditBlock(ccp(246.7f + 32.0f,950.0f),D_PHOTOSHOP_Y(670.0f - 32.0f),11.0f,"CreditBlock7_2.png");//20
    AddCreditBlock(ccp(320.2f + 32.0f,950.0f),D_PHOTOSHOP_Y(670.0f - 32.0f),11.0f,"CreditBlock7_3.png");//21
	
	m_fNewTimer = 10001.0f;
	
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
    this->addChild(emitter3, 0);

	this->schedule(schedule_selector(CreditScene::Update), 0.0);

	m_nStep = 0;

	if(g_bEFFECT_Sound == true)
	{
		D_SOUNDMNG->playEffect("Out.mp3");
	}

    return true;
}


void CreditScene::BackCallback(CCObject* pSender)
{
	D_SCENE_CHANGE_EFFECT_UP(MenuScene::scene());

	g_EffectManager.Exit();
	g_EffectManager.m_pEffectList.clear();

	//vector<CCreditBlock*>::iterator it;
	//for(it = m_pCreditBlockList.begin(); it != m_pCreditBlockList.end(); it++)
	//{
	//	//(*it)->Exit();
	//	delete (*it);
	//}
	//m_pCreditBlockList.clear();

	//CCScene *pScene = CCTransitionCrossFade();
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}

void CreditScene::Update(float dt)
{
	m_fTimer += dt;
	m_fNewTimer += dt;
	if(m_fNewTimer >= 0.3f && m_fNewTimer <= 10000.0f)
	{
		if(g_bEFFECT_Sound == true)
		{
			D_SOUNDMNG->playEffect("Out.mp3");
		}
		m_fNewTimer = 10001.0f;
	}
	m_pBack.Update(dt);
	if(m_pBack.CheckAction() == true)
	{
		BackCallback(NULL);
		m_pBack.CheckActioned();
	}
	g_EffectManager.Update(dt);
	

	vector<CCreditBlock*>::iterator it;
	for(it = m_pCreditBlockList.begin(); it != m_pCreditBlockList.end(); it++)
	{
		(*it)->Update(dt, m_fTimer);
	}

	if(m_nStep == 0 && SearchBlockIndex(5)->m_nState == 3 && SearchBlockIndex(6)->m_nState == 3 && SearchBlockIndex(7)->m_nState == 3)
	{
		Explosion(SearchBlockIndex(5)->m_stPos,(E_BLOCKNUMBER)5);
		Explosion(SearchBlockIndex(6)->m_stPos,(E_BLOCKNUMBER)5);
		Explosion(SearchBlockIndex(7)->m_stPos,(E_BLOCKNUMBER)5);

		g_EffectManager.Insert(3,SearchBlockIndex(5)->m_stPos.x,SearchBlockIndex(5)->m_stPos.y);
		g_EffectManager.Insert(3,SearchBlockIndex(6)->m_stPos.x,SearchBlockIndex(6)->m_stPos.y);
		g_EffectManager.Insert(3,SearchBlockIndex(7)->m_stPos.x,SearchBlockIndex(7)->m_stPos.y);


		// SearchBlockIndex(5);
		//delete SearchBlockIndex(6);
		//delete SearchBlockIndex(7);

		for(it = m_pCreditBlockList.begin(); it != m_pCreditBlockList.end(); )
		{
			if( (*it)->m_nIndex == 5 || (*it)->m_nIndex == 6 || (*it)->m_nIndex == 7 )
			{
				(*it)->Exit();
				delete (*it);
				it = m_pCreditBlockList.erase(it);
			}
			else
			{
				it++;
			}
		}
		SearchBlockIndex(0)->Reset(0.2f);
		SearchBlockIndex(1)->Reset(0.4f);
		SearchBlockIndex(2)->Reset(0.6f);
		SearchBlockIndex(3)->Reset(0.8f);
		SearchBlockIndex(4)->Reset(1.0f);

		if(g_bEFFECT_Sound == true)
		{
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		
		m_nStep++;
	}
	else if(m_nStep == 1 && 
		SearchBlockIndex(8)->m_nState == 3 && 
		SearchBlockIndex(9)->m_nState == 3 && 
		SearchBlockIndex(10)->m_nState == 3 )
	{
		Explosion(SearchBlockIndex(0)->m_stPos,(E_BLOCKNUMBER)1);
		Explosion(SearchBlockIndex(1)->m_stPos,(E_BLOCKNUMBER)1);
		Explosion(SearchBlockIndex(2)->m_stPos,(E_BLOCKNUMBER)1);
		Explosion(SearchBlockIndex(3)->m_stPos,(E_BLOCKNUMBER)1);
		Explosion(SearchBlockIndex(4)->m_stPos,(E_BLOCKNUMBER)1);

		Explosion(SearchBlockIndex(8)->m_stPos,(E_BLOCKNUMBER)2);
		Explosion(SearchBlockIndex(9)->m_stPos,(E_BLOCKNUMBER)2);
		Explosion(SearchBlockIndex(10)->m_stPos,(E_BLOCKNUMBER)2);

		
		g_EffectManager.Insert(4,SearchBlockIndex(0)->m_stPos.x,SearchBlockIndex(0)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(1)->m_stPos.x,SearchBlockIndex(1)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(2)->m_stPos.x,SearchBlockIndex(2)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(3)->m_stPos.x,SearchBlockIndex(3)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(4)->m_stPos.x,SearchBlockIndex(4)->m_stPos.y);
		
		g_EffectManager.Insert(5,SearchBlockIndex(8)->m_stPos.x,SearchBlockIndex(8)->m_stPos.y);
		g_EffectManager.Insert(5,SearchBlockIndex(9)->m_stPos.x,SearchBlockIndex(9)->m_stPos.y);
		g_EffectManager.Insert(5,SearchBlockIndex(10)->m_stPos.x,SearchBlockIndex(10)->m_stPos.y);

		for(it = m_pCreditBlockList.begin(); it != m_pCreditBlockList.end(); )
		{
			if( (*it)->m_nIndex == 0 || 
				(*it)->m_nIndex == 1 || 
				(*it)->m_nIndex == 2 || 
				(*it)->m_nIndex == 3 || 
				(*it)->m_nIndex == 4 || 
				(*it)->m_nIndex == 8 || 
				(*it)->m_nIndex == 9 || 
				(*it)->m_nIndex == 10 )
			{
				(*it)->Exit();
				delete (*it);
				it = m_pCreditBlockList.erase(it);
			}
			else
			{
				it++;
			}
		}
		if(g_bEFFECT_Sound == true)
		{
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		
		m_fNewTimer = 0.0f;
		m_nStep++;
	}
	else if(m_nStep == 2 && 
		SearchBlockIndex(14)->m_nState == 3 && 
		SearchBlockIndex(15)->m_nState == 3 && 
		SearchBlockIndex(16)->m_nState == 3 )
	{
		Explosion(SearchBlockIndex(11)->m_stPos,(E_BLOCKNUMBER)3);
		Explosion(SearchBlockIndex(12)->m_stPos,(E_BLOCKNUMBER)3);
		Explosion(SearchBlockIndex(13)->m_stPos,(E_BLOCKNUMBER)3);

		Explosion(SearchBlockIndex(14)->m_stPos,(E_BLOCKNUMBER)4);
		Explosion(SearchBlockIndex(15)->m_stPos,(E_BLOCKNUMBER)4);
		Explosion(SearchBlockIndex(16)->m_stPos,(E_BLOCKNUMBER)4);

		
		g_EffectManager.Insert(4,SearchBlockIndex(11)->m_stPos.x,SearchBlockIndex(11)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(12)->m_stPos.x,SearchBlockIndex(12)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(13)->m_stPos.x,SearchBlockIndex(13)->m_stPos.y);
		
		g_EffectManager.Insert(2,SearchBlockIndex(14)->m_stPos.x,SearchBlockIndex(14)->m_stPos.y);
		g_EffectManager.Insert(2,SearchBlockIndex(15)->m_stPos.x,SearchBlockIndex(15)->m_stPos.y);
		g_EffectManager.Insert(2,SearchBlockIndex(16)->m_stPos.x,SearchBlockIndex(16)->m_stPos.y);

		for(it = m_pCreditBlockList.begin(); it != m_pCreditBlockList.end(); )
		{
			if( (*it)->m_nIndex == 11 || 
				(*it)->m_nIndex == 12 || 
				(*it)->m_nIndex == 13 || 
				(*it)->m_nIndex == 14 || 
				(*it)->m_nIndex == 15 || 
				(*it)->m_nIndex == 16  )
			{
				(*it)->Exit();
				delete (*it);
				it = m_pCreditBlockList.erase(it);
			}
			else
			{
				it++;
			}
		}
		if(g_bEFFECT_Sound == true)
		{
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		m_fNewTimer = 0.0f;
		m_nStep++;
	}
	else if(m_nStep == 3 && 
		SearchBlockIndex(19)->m_nState == 3 && 
		SearchBlockIndex(20)->m_nState == 3 && 
		SearchBlockIndex(21)->m_nState == 3 )
	{
		Explosion(SearchBlockIndex(17)->m_stPos,(E_BLOCKNUMBER)3);
		Explosion(SearchBlockIndex(18)->m_stPos,(E_BLOCKNUMBER)3);

		Explosion(SearchBlockIndex(19)->m_stPos,(E_BLOCKNUMBER)4);
		Explosion(SearchBlockIndex(20)->m_stPos,(E_BLOCKNUMBER)4);
		Explosion(SearchBlockIndex(21)->m_stPos,(E_BLOCKNUMBER)4);

		
		g_EffectManager.Insert(1,SearchBlockIndex(17)->m_stPos.x,SearchBlockIndex(17)->m_stPos.y);
		g_EffectManager.Insert(1,SearchBlockIndex(18)->m_stPos.x,SearchBlockIndex(18)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(19)->m_stPos.x,SearchBlockIndex(19)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(20)->m_stPos.x,SearchBlockIndex(20)->m_stPos.y);
		g_EffectManager.Insert(4,SearchBlockIndex(21)->m_stPos.x,SearchBlockIndex(21)->m_stPos.y);

		for(it = m_pCreditBlockList.begin(); it != m_pCreditBlockList.end(); )
		{
			if( (*it)->m_nIndex == 17 || 
				(*it)->m_nIndex == 18 || 
				(*it)->m_nIndex == 19 || 
				(*it)->m_nIndex == 20 || 
				(*it)->m_nIndex == 21  )
			{
				(*it)->Exit();
				delete (*it);
				it = m_pCreditBlockList.erase(it);
			}
			else
			{
				it++;
			}
		}
		if(g_bEFFECT_Sound == true)
		{
			D_SOUNDMNG->playEffect("BlockPop_1.mp3");
		}
		m_fNewTimer = 0.0f;
		m_nStep++;
	}
	
}

CCreditBlock* CreditScene::SearchBlockIndex(int nIndex)
{
	vector<CCreditBlock*>::iterator it;
	for(it = m_pCreditBlockList.begin(); it != m_pCreditBlockList.end(); it++)
	{
		if(nIndex == (*it)->m_nIndex)
		{
			return (*it);
		}
	}
	return NULL;
}

void CreditScene::AddCreditBlock(CCPoint stPos, float fGround, float fDelayTime, string strFilePath)
{
	CCreditBlock * pTempBlock = new CCreditBlock(this,stPos,fGround,fDelayTime,strFilePath);
	m_pCreditBlockList.push_back(pTempBlock);
}


void CreditScene::Explosion(CCPoint CPos, E_BLOCKNUMBER eBlockNumber)
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


	
}
void CreditScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}




void CreditScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool CreditScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());

	m_pBack.TouchBegan(stPos);
	
	
	return true;
}
void   CreditScene::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
}

void  CreditScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
	m_pBack.TouchEnded(stPos);
	
}