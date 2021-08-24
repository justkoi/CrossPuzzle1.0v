#include "stdafx.h"

#define RadToDeg(x) (57.29577951f * x)
#define DegToRad(x) (0.017453293f * x)

USING_NS_CC;

bool bCheat = true;

stStageInfo g_StageInfo[3][D_STAGE_MAX] = 
{
	{
		{ 5 , 400 }, //!< 1Stage
		{ 6 , 550 }, //!< 2Stage
		{ 6 , 750 }, //!< 3Stage
		{ 7 , 1150 }, //!< 4Stage
		{ 7 , 1250 }, //!< 5Stage
		{ 8 , 1350 }, //!< 6Stage
		{ 8 , 1650 }, //!< 7Stage
		{ 8 , 1850 }, //!< 8Stage
		{ 8 , 2150 }, //!< 9Stage
		{ 8 , 2550 }, //!< 10Stage
		{ 9 , 2950 }, //!< 11Stage
		{ 9 , 3350 }, //!< 12Stage
		{ 9 , 3650 }, //!< 13Stage
		{ 10 , 4050 }, //!< 14Stage
		{ 10 , 4650 }, //!< 15Stage
		{ 11 , 5150 }, //!< 16Stage
		{ 12 , 5650 }, //!< 17Stage
		{ 13 , 6100 }, //!< 18Stage
		{ 14, 6550 }, //!< 19Stage
		{ 15 , 6850 }, //!< 20Stage
		{ 16 , 7050 }, //!< 21Stage
		{ 16 , 7050 }, //!< 22Stage
		{ 16 , 7050 }, //!< 23Stage
		{ 16 , 7050 }, //!< 24Stage
		{ 16 , 7050 }, //!< 25Stage
		{ 16 , 7050 }, //!< 26Stage
		{ 16 , 7050 }, //!< 27Stage
		{ 16 , 7050 }, //!< 28Stage
		{ 16 , 7050 }, //!< 29Stage
		{ 16 , 7050 }, //!< 30Stage
		{ 16 , 7050 }, //!< 31Stage
	},
	{
		{ 5 , 600 }, //!< 1Stage
		{ 6 , 750 }, //!< 2Stage
		{ 6 , 950 }, //!< 3Stage
		{ 7 , 1450 }, //!< 4Stage
		{ 7 , 1650 }, //!< 5Stage
		{ 8 , 1950 }, //!< 6Stage
		{ 8 , 2150 }, //!< 7Stage
		{ 8 , 2350 }, //!< 8Stage
		{ 8 , 2650 }, //!< 9Stage
		{ 8 , 3250 }, //!< 10Stage
		{ 9 , 3550 }, //!< 11Stage
		{ 9 , 3850 }, //!< 12Stage
		{ 9 , 4250 }, //!< 13Stage
		{ 9 , 4550 }, //!< 14Stage
		{ 9 , 5850 }, //!< 15Stage
		{ 10 , 6550 }, //!< 16Stage
		{ 11 , 7050 }, //!< 17Stage
		{ 12 , 7400 }, //!< 18Stage
		{ 13 , 7850 }, //!< 19Stage
		{ 14 , 8350 }, //!< 20Stage
		{ 15 , 9050 }, //!< 21Stage
		{ 15 , 9050 }, //!< 22Stage
		{ 15 , 9050 }, //!< 23Stage
		{ 15 , 9050 }, //!< 24Stage
		{ 15 , 9050 }, //!< 25Stage
		{ 15 , 9050 }, //!< 26Stage
		{ 15 , 9050 }, //!< 27Stage
		{ 15 , 9050 }, //!< 28Stage
		{ 15 , 9050 }, //!< 29Stage
		{ 15 , 9050 }, //!< 30Stage
		{ 15 , 9050 }, //!< 31Stage
	},
	{
		{ 5 , 1000 }, //!< 1Stage
		{ 5 , 1550 }, //!< 2Stage
		{ 6 , 1750 }, //!< 3Stage
		{ 7 , 2150 }, //!< 4Stage
		{ 8 , 2650 }, //!< 5Stage
		{ 9 , 3150 }, //!< 6Stage
		{ 9 , 3450 }, //!< 7Stage
		{ 9 , 3850 }, //!< 8Stage
		{ 9 , 4250 }, //!< 9Stage
		{ 9 , 4650 }, //!< 10Stage
		{ 10 , 5050 }, //!< 11Stage
		{ 10, 5450 }, //!< 12Stage
		{ 10 , 5850 }, //!< 13Stage
		{ 10 , 6250 }, //!< 14Stage
		{ 10 , 6650 }, //!< 15Stage
		{ 12 , 7450 }, //!< 16Stage
		{ 13 , 8050 }, //!< 17Stage
		{ 14 , 8600 }, //!< 18Stage
		{ 15 , 9250 }, //!< 19Stage
		{ 16 , 9950 }, //!< 20Stage
		{ 17 , 10450 }, //!< 21Stage
		{ 17 , 10450 }, //!< 22Stage
		{ 17 , 10450 }, //!< 23Stage
		{ 17 , 10450 }, //!< 24Stage
		{ 17 , 10450 }, //!< 25Stage
		{ 17 , 10450 }, //!< 26Stage
		{ 17 , 10450 }, //!< 27Stage
		{ 17 , 10450 }, //!< 28Stage
		{ 17 , 10450 }, //!< 29Stage
		{ 17 , 10450 }, //!< 30Stage
		{ 17 , 10450 }, //!< 31Stage
	}
};
bool g_bStageLock[D_STAGE_MAX];



void StageMenuScene::SaveStage()
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
void StageMenuScene::LoadStage()
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

CCScene* StageMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StageMenuScene *layer = StageMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float StageMenuScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float StageMenuScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}

// on "init" you need to initialize your instance
bool StageMenuScene::init()
{
	


    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();

	

	g_EffectManager.Exit();
	g_LineManager.Exit();
	g_PlaneManager.Exit();
	g_NumberManager.Exit();

	g_EffectManager.m_pEffectList.clear();
	g_LineManager.m_pEffectList.clear();
	g_PlaneManager.m_pPlaneList.clear();
	g_NumberManager.m_pNumberList.clear();

	// g_ComboManager.Exit();
	// g_ComboManager.m_ComboList.clear();

	this->setTouchEnabled(true);


	char strFilePath[256];
	sprintf(strFilePath,"stagelock_%d.sav",g_nLevel);
	CCFileUtils FileUitil;
	string strTemp = FileUitil.getWriteablePath();
	strTemp.append(strFilePath);

	FILE* fpr = fopen(strTemp.c_str(),"rb");
	if(fpr == NULL)
	{
		for(int i=0; i<D_STAGE_MAX; i++)
		{
			g_bStageLock[i] = false;
		}
		g_bStageLock[0] = true;
		SaveStage();
	}
	
	LoadStage();

	int nStageCount = 0;
	m_fLightTimer = 0.0f;

	char strFilePath2[256];
	char strFilePath3[256];
	
	sprintf(strFilePath,"MenuLight_%d.png",g_nLevel);
	sprintf(strFilePath2,"Button_SelectMenu_1_%d.png",g_nLevel);
	sprintf(strFilePath3,"Button_SelectMenu_3_%d.png",g_nLevel);

    m_pBackGround = CCSprite::create("LevelMenu.png");
	m_pBackGround->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGround->setScaleX(1.05f * D_SCALE_WIDTH);
	m_pBackGround->setScaleY(1.05f * D_SCALE_HEIGHT);
	//m_pBackGround->setColor(ccc3(255 * 0.3f, 255 * 0.3f, 255 * 0.3f));
    this->addChild(m_pBackGround, 0);

	
    m_pBackGroundLight = CCSprite::create(strFilePath);
	m_pBackGroundLight->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGroundLight->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBackGroundLight->setScaleY(1.00f * D_SCALE_HEIGHT);
	//m_pBackGroundLight->setColor(ccc3(255 * 0.5f,255 * 0.5f,255 * 0.5f));
    this->addChild(m_pBackGroundLight, 1);

	//D_SOUNDMNG->preloadBackgroundMusic("Menu_BGM.mp3");
	//if(g_bBGM_Sound == true)
	if(g_bFirstPlayed == false)
	{
		g_bFirstPlayed = true;
		D_SOUNDMNG->setBackgroundMusicVolume(g_fBGM_Volume);
		D_SOUNDMNG->playBackgroundMusic("Menu_BGM.mp3",true);
		//D_SOUNDMNG->playBackgroundMusic("Menu_BGM.mp3", true);
	}
	m_pReset.Init(this,1,"Reset_1.png","Reset_3.png",ccp(35 * D_SCALE_WIDTH, 730 * D_SCALE_HEIGHT));
	m_pNext.Init(this,1,"Next_1.png","Next_3.png",ccp(445 * D_SCALE_WIDTH, 730 * D_SCALE_HEIGHT));
	
	//pResetItem = CCMenuItemImage::create(
 //                                       "Reset_1.png",
 //                                       "Reset_3.png",
 //                                       this,
 //                                       menu_selector(StageMenuScene::ResetCallback) );
 //   pResetItem->setPosition( ccp( ReturnWidth(35), ReturnHeight(730)) );
 //   pReset = CCMenu::create(pResetItem, NULL);

	//
	//pReset->setPosition( CCPointZero );
	//pReset->setScaleX(1.00f * D_SCALE_WIDTH);
	//pReset->setScaleY(1.00f * D_SCALE_HEIGHT);
 //   this->addChild(pReset, 1);

	//// add a "close" icon to exit the progress. it's an autorelease object
 //   pNextItem = CCMenuItemImage::create(
 //                                       "Next_1.png",
 //                                       "Next_3.png",
 //                                       this,
 //                                       menu_selector(StageMenuScene::NextCallback) );
 //   pNextItem->setPosition( ccp( ReturnWidth(445),  ReturnHeight(730)) );
 //   pNext = CCMenu::create(pNextItem, NULL);
	//pNext->setColor(ccc3(255 * 0.5f,255 * 0.9f,255 * 0.9f));
	//
	//pNext->setPosition( CCPointZero );
	//pNext->setScaleX(1.00f * D_SCALE_WIDTH);
	//pNext->setScaleY(1.00f * D_SCALE_HEIGHT);

 //   this->addChild(pNext, 1);
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		int nStageCount = i;

		m_pPlay[i].Init(this,1,strFilePath2,strFilePath3,ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))));
		
		
		if(g_nLevel == 1)
			m_pPlay[i].setColor(ccc3(255 *  (1.0f - ((float)((float)nStageCount/(float)D_STAGE_MAX) * 0.7f)),255 * (1.0f - ((float)((float)nStageCount/(float)D_STAGE_MAX) * 0.7f)),255 * 1.0f));
		else if(g_nLevel == 2)
			m_pPlay[i].setColor(ccc3(255 *  (((float)((float)nStageCount/(float)D_STAGE_MAX) * 1.0f)),255 *  (1.0f - ((float)((float)nStageCount/(float)D_STAGE_MAX) * 0.7f)),255 *  (((float)((float)nStageCount/(float)D_STAGE_MAX) * 1.0f)))); // m_pPlay[i].setColor(ccc3(255 * 0.7f,(200 * ((float)((float)nStageCount/(float)D_STAGE_MAX)))+55,255 * 0.7f));
		else if(g_nLevel == 3)
			m_pPlay[i].setColor(ccc3(255 *  (1.0f - ((float)((float)nStageCount/(float)D_STAGE_MAX) * 0.7f)),255 *  (((float)((float)nStageCount/(float)D_STAGE_MAX) * 1.0f)),255 *  (((float)((float)nStageCount/(float)D_STAGE_MAX) * 1.0f))));//m_pPlay[i].setColor(ccc3((200 * ((float)((float)nStageCount/(float)D_STAGE_MAX)))+55,255 * 0.7f,255 * 0.7f));
		
		
		m_pLock[i] = CCSprite::create("Lock.png");
		m_pLock[i]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
		m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
		this->addChild(m_pLock[i], 3);
	}

	/*
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback1 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    
	m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );
	m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

	m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
	this->addChild(m_pPlay[nStageCount], 1);

	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback2 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback3 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback4 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback5 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback6 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////


	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback7 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback8 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback9 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback10 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback11 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback12 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback13 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback14 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback15 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback16 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback17 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback18 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback19 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback20 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									strFilePath2,
									strFilePath3,
									this,
									menu_selector( StageMenuScene::StageCallback21 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	nStageCount++;

	*/
	///////////////////////////////////////////////////////////////////////////////
	/*m_pBackItem = CCMenuItemImage::create(
                                        "Button_Back_1.png",
                                        "Button_Back_3.png",
                                        this,
                                        menu_selector(StageMenuScene::BackCallback) );
    m_pBackItem->setPosition( ccp( ReturnWidth(50), ReturnHeight(25)) );
    m_pBack = CCMenu::create(m_pBackItem, NULL);

	m_pBack->setPosition( CCPointZero );
	m_pBack->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBack->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pBack, 31);
*/
	m_pBack.Init(this,31,"Button_Back_1.png","Button_Back_3.png",ccp(60 * D_SCALE_WIDTH, 35 * D_SCALE_HEIGHT));
	

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

	this->schedule(schedule_selector(StageMenuScene::Update), 0.0);

	m_fTimer = 0.0f;

    return true;
}

void StageMenuScene::Update(float dt)
{
	m_fTimer += dt;

	m_pReset.Update(dt);
	m_pNext.Update(dt);

	m_pBack.Update(dt);
	if(m_pBack.CheckAction() == true)
	{
		BackCallback(NULL);
		m_pBack.CheckActioned();
	}

	if(m_pReset.CheckAction() == true)
	{
		ResetCallback(NULL);
		m_pReset.Reset();
	}
	if(m_pNext.CheckAction() == true)
	{
		NextCallback(NULL);
		m_pNext.Reset();
	}
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		m_pPlay[i].Update(dt);
	}

	for(int i=0; i<D_STAGE_MAX; i++)
	{
		if(m_pPlay[i].CheckAction() == true)
		{
			StageCallBack(i+1);
			m_pPlay[i].Reset();
		}
	}
	
	m_fScroll_Y_Smooth += m_fScroll_Y_Vector/30;
	m_fScroll_Y_Vector -= m_fScroll_Y_Smooth;

	m_fScroll_Y_All += m_fScroll_Y_Smooth;
	if(m_fScroll_Y_All >= 0.0f && m_fScroll_Y_All <= (D_STAGEMENU_HEGIHT * ((int)(D_STAGE_MAX/3) - 4)))
	{
		//m_fScroll_Y_Vector = -(m_fScroll_Y_Vector - m_fScroll_Y_All);
		for(int i=0; i<D_STAGE_MAX; i++)
		{
			//for(int j=0; j<3; j++)
			//{
			//	m_pStar[i][j]->setPositionY(m_pStar[i][j]->getPositionY() + m_fScroll_Y_Smooth);
			//}
			m_CNumber[i].SetPositionY(m_CNumber[i].m_stPos.y + m_fScroll_Y_Smooth);
		
			m_pLock[i]->setPositionY(m_pLock[i]->getPositionY() + m_fScroll_Y_Smooth);
			
			m_pPlay[i].setPositionY(m_pPlay[i].m_CPoint.y + m_fScroll_Y_Smooth);
		}
		m_fScroll_Y_Smooth = 0.0f;
	}
	/*else if( m_fScroll_Y_All >= (D_STAGEMENU_HEGIHT * 2))
	{
		m_fScroll_Y_Smooth = 0.0f;
		m_fScroll_Y_Vector = 0.0f;
	}*/
	else if(m_fScroll_Y_All < 0.0f)
	{
		m_fScroll_Y_All = 0.0f;
		m_fScroll_Y_Smooth = 0.0f;
		m_fScroll_Y_Vector = 0.0f;
	}
	else if(m_fScroll_Y_All > (D_STAGEMENU_HEGIHT * ((int)(D_STAGE_MAX/3) - 4)))
	{
		m_fScroll_Y_All = (D_STAGEMENU_HEGIHT * ((int)(D_STAGE_MAX/3) - 4));
		m_fScroll_Y_Smooth = 0.0f;
		m_fScroll_Y_Vector = 0.0f;
	}

	ShowUpdateLock();

}

void StageMenuScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void StageMenuScene::EasyCallback(CCObject* pSender)
{
	D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect("StageStart.mp3"); }
}


void StageMenuScene::BackCallback(CCObject* pSender)
{
	D_SCENE_CHANGE_EFFECT_UP(LevelMenuScene::scene());
	//CCScene *pScene = CCTransitionCrossFade();
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}


void StageMenuScene::ShowUpdateLock()
{
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		if(g_bStageLock[i] == true)
		{
			//m_pPlayItem[i]->setVisible(true);
			m_pPlay[i].setVisible(true);
			m_pLock[i]->setVisible(false);
		}
		else if(g_bStageLock[i] == false)
		{
			//m_pPlayItem[i]->setVisible(false);
			m_pPlay[i].setVisible(false);
			m_pLock[i]->setVisible(true);
		}
	}
}

void StageMenuScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool StageMenuScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	m_fStart_Y = stPos.y;

	m_pReset.TouchBegan(stPos);
	m_pNext.TouchBegan(stPos);
	m_pBack.TouchBegan(stPos);
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		m_pPlay[i].TouchBegan(stPos);
	}
	return true;
}
void   StageMenuScene::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	m_fScroll_Y_Vector += -(m_fStart_Y - stPos.y) * 1.1f;
	m_fStart_Y = stPos.y;
}

void  StageMenuScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	
	m_pReset.TouchEnded(stPos);
	m_pNext.TouchEnded(stPos);
	m_pBack.TouchEnded(stPos);
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		m_pPlay[i].TouchEnded(stPos);
	}
}

void StageMenuScene::StageCallBack(int nStage)
{
	g_nStage = nStage;
	
	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
/*
void StageMenuScene::StageCallback1(CCObject* pSender)
{
	g_nStage = 1;
	
	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback2(CCObject* pSender)
{
	g_nStage = 2;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true)
	{
		 
		D_SOUNDMNG->playEffect(D_BUTTON_SOUND);
	}
}
void StageMenuScene::StageCallback3(CCObject* pSender)
{
	g_nStage = 3;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}

void StageMenuScene::StageCallback4(CCObject* pSender)
{
	g_nStage = 4;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback5(CCObject* pSender)
{
	g_nStage = 5;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback6(CCObject* pSender)
{
	g_nStage = 6;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {   D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}


void StageMenuScene::StageCallback7(CCObject* pSender)
{
	g_nStage = 7;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback8(CCObject* pSender)
{
	g_nStage = 8;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback9(CCObject* pSender)
{
	g_nStage = 9;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}


void StageMenuScene::StageCallback10(CCObject* pSender)
{
	g_nStage = 10;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback11(CCObject* pSender)
{
	g_nStage = 11;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback12(CCObject* pSender)
{
	g_nStage = 12;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback13(CCObject* pSender)
{
	g_nStage = 13;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback14(CCObject* pSender)
{
	g_nStage = 14;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback15(CCObject* pSender)
{
	g_nStage = 15;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback16(CCObject* pSender)
{
	g_nStage = 16;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback17(CCObject* pSender)
{
	g_nStage = 17;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback18(CCObject* pSender)
{
	g_nStage = 18;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback19(CCObject* pSender)
{
	g_nStage = 19;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback20(CCObject* pSender)
{
	g_nStage = 20;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
void StageMenuScene::StageCallback21(CCObject* pSender)
{
	g_nStage = 21;

	D_SOUNDMNG->stopBackgroundMusic(); D_SCENE_CHANGE_EFFECT_DOWN(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) {  D_SOUNDMNG->playEffect(D_BUTTON_SOUND); }
}
*/

void StageMenuScene::ResetCallback(CCObject* pSender)
{
	if(bCheat == true)
	{
	   for(int i=0; i<D_STAGE_MAX; i++)
		{
			g_bStageLock[i] = false;
		}
		g_bStageLock[0] = true;
		SaveStage();
	}
}

void StageMenuScene::NextCallback(CCObject* pSender)
{
	if(bCheat == true)
	{
		int nNextStage = -1;
		for(int i=0; i<D_STAGE_MAX; i++)
		{
			if(g_bStageLock[i] == false)
			{
				nNextStage = i;
				break;
			}
		}
		if(nNextStage == -1)
			return;
		g_bStageLock[nNextStage] = true;
		SaveStage();
	}
}