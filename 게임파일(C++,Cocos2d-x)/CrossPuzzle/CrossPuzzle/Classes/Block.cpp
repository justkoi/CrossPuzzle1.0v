#include "stdafx.h"

USING_NS_CC;
static int Random = 0;
void CBlock::Init(CCLayer* pThisScene, int nId)
{
	char frameName[256];
	m_pThisScene = pThisScene;

	m_bLive = false;

	m_nId = nId;
	m_fNextDistance = 64.0f;
	m_stOffsetPos = ccp(0,0);

	m_stIndex.m_nX = 0;
	m_stIndex.m_nY = 0;
	m_fEyeContact = 0.0f;

	m_stIndex = m_stIndex;

	m_stPos.x = D_LINE_START_X + (m_stIndex.m_nX * 64);
	m_stPos.y = D_LINE_START_Y - (m_stIndex.m_nY * 64);

	Random = rand()%E_BLOCKNUMBER_MAX;
	m_eBlockNumber = (E_BLOCKNUMBER)Random;

	m_eBlockItem = E_BLOCKITEM_NONE;


	m_fStartY			= m_stPos.y;
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_FALL_NONE;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;
	m_bNoSelect = true;

	m_bChecked = false;
	m_bFocused = false;
	
	m_fTargetColorAlpha = 0.0f;
	m_fNowColorAlpha = 0.0f;

	m_fTargetAlpha = 1.0f;
	m_fNowAlpha = 1.0f;
	
	m_pNoSelect = CCSprite::create("Block_Select.png");
	m_pNoSelect->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pNoSelect->setScaleX(1.30f * D_SCALE_WIDTH);
	m_pNoSelect->setScaleY(1.30f * D_SCALE_HEIGHT);
	m_pNoSelect->setOpacity(255 * 0.0f);
	m_pNoSelect->setVisible(true);
	m_pNoSelect->setAnchorPoint(ccp(0.5f,0.5f));
	m_pThisScene->addChild(m_pNoSelect, 21);


	m_bFallFinished = false;
	m_fGPM = 0.0f;

	
	m_nBounceLevel = 0;
	m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
	m_fBounceLine = 0.0f;
}
void CBlock::Pause()
{
	if(m_bLive == true)
	{
		if(m_eBlockItem != E_BLOCKITEM_NONE)
		{
			m_pItem->getActionManager()->pauseTarget(m_pItem);
		}
	}
}

void CBlock::Resume()
{
	if(m_bLive == true)
	{
		if(m_eBlockItem != E_BLOCKITEM_NONE)
		{
			m_pItem->getActionManager()->resumeTarget(m_pItem);
		}
	}
}
void CBlock::Create(stVec2i stIndex)
{
	
	char frameName[256];

	m_bNoSelect = true;

	m_bLive = true;

	m_bFallFinished = false;
	
	m_bChecked = false;
	m_bFocused = false;

	m_nBounceLevel = 0;
	m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
	m_fBounceLine = 0.0f;

	m_stIndex = stIndex;
	m_fNextDistance = 64.0f;
	m_stOffsetPos = ccp(0,0);

	m_stPos.x = D_LINE_START_X + (stIndex.m_nX * 64);
	m_stPos.y = D_LINE_START_Y - (stIndex.m_nY * 64);
	
	m_eBlockItem = E_BLOCKITEM_NONE;

	Random = rand()%E_BLOCKNUMBER_MAX;
	m_eBlockNumber = (E_BLOCKNUMBER)Random;
	
	m_fStartY			= m_stPos.y;
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_FALL_NONE;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;
	m_pNoSelect->setPosition(ccp(-100.0f,-100.0f));
	m_pNoSelect->setVisible(true);

	sprintf(frameName,"Block_%d.png",(int)m_eBlockNumber + 1);

	m_pBlock = CCSprite::create(frameName);
	m_pBlock->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBlock->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBlock->setColor(ccc3(255 * 1.0f,255 * 1.0f,255 * 1.0f));
	m_pBlock->setAnchorPoint(ccp(0.5f,0.5f));
	m_pThisScene->addChild(m_pBlock, 22);

	m_pBlock->setVisible(true);

	m_fTargetColorAlpha = 0.0f;
	m_fNowColorAlpha = 0.0f;

	m_fTargetAlpha = 1.0f;
	m_fNowAlpha = 1.0f;

	int nBlockItemRandom = rand()%10000; //0 ~ 9999

	
	if(nBlockItemRandom >= 0 && nBlockItemRandom <= 200) //!< 2% È®·ü·Î ¶óÀÌÆ®´×
	{
		if(g_nStage >= 7)
		{
			m_eBlockItem = E_BLOCKITEM_LIGHTNING;

			CCActionInterval * m_pBlockAnt;

			m_pItemAni = CCAnimation::animation();
			for(int j=0; j<4; j++) {
					sprintf(frameName, "Item_%d_%d.png",(int)m_eBlockItem,j+1);
					m_pItemAni->addSpriteFrameWithFileName(frameName);
			}
			m_pItemAni->setDelayPerUnit(0.15f);
			m_pBlockAnt = CCAnimate::create(m_pItemAni);
			m_pItem = CCSprite::spriteWithFile("NewSprite.png");
			m_pItem->setPosition( ccp((m_stPos.x + 10) * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			m_pItem->setScaleX( 0.7f * D_SCALE_WIDTH);
			m_pItem->setScaleY( 0.7f * D_SCALE_HEIGHT);
			m_pItem->setColor(ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f));
			m_pThisScene->addChild(m_pItem, 23);
			//m_pBlock->runAction(m_pBlockAnt);
			m_pItem->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
			m_pItem->setAnchorPoint(ccp(0.5,0.5));

			////////////////////////////////////////////////////// CCSprite
			//sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


			//m_pItem = CCSprite::create(frameName);
			////m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
			//m_pItem->setAnchorPoint(ccp(0.5f,0.5f));
			////m_pItem->setScale(1.0f);

			//m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			//m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
			//m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);

			//m_pThisScene->addChild(m_pItem, 23);
			//////////////////////////////////////////////////////
		}
		else												  //!< 90% È®·ü·Î ±âº»
		{
			m_eBlockItem = E_BLOCKITEM_NONE;
		}
	}
	else if(nBlockItemRandom > 200 && nBlockItemRandom <= 400) //!< 2% È®·ü·Î ÆøÅº
	{
		if(g_nStage >= 10)
		{
			m_eBlockItem = E_BLOCKITEM_BOMB;

			CCActionInterval * m_pBlockAnt;

			m_pItemAni = CCAnimation::animation();
			for(int j=0; j<6; j++) {
					sprintf(frameName, "Item_%d_%d.png",(int)m_eBlockItem,j+1);
					m_pItemAni->addSpriteFrameWithFileName(frameName);
			}
			m_pItemAni->setDelayPerUnit(0.25f);
			m_pBlockAnt = CCAnimate::create(m_pItemAni);
			m_pItem = CCSprite::spriteWithFile("NewSprite.png");
			m_pItem->setPosition( ccp((m_stPos.x + 10) * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			m_pItem->setScaleX( 0.8f * D_SCALE_WIDTH);
			m_pItem->setScaleY( 0.8f * D_SCALE_HEIGHT);
			//m_pItem->setColor(ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
			m_pThisScene->addChild(m_pItem, 23);
			//m_pBlock->runAction(m_pBlockAnt);
			m_pItem->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
			m_pItem->setAnchorPoint(ccp(0.5,0.5));

			////////////////////////////////////////////////////// CCSprite
			//sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


			//m_pItem = CCSprite::create(frameName);
			////m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
			//m_pItem->setAnchorPoint(ccp(0.5f,0.5f));
			////m_pItem->setScale(1.0f);

			//m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			//m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
			//m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);

			//m_pThisScene->addChild(m_pItem, 23);
			//////////////////////////////////////////////////////
		}
		else												  //!< 90% È®·ü·Î ±âº»
		{
			m_eBlockItem = E_BLOCKITEM_NONE;
		}
	}
	else if(nBlockItemRandom > 400 && nBlockItemRandom <= 600) //!< 2% È®·ü·Î ÆøÅº
	{
		if(g_nStage >= 13)
		{
			m_eBlockItem = E_BLOCKITEM_SPACE;

			CCActionInterval * m_pBlockAnt;

			m_pItemAni = CCAnimation::animation();
			for(int j=0; j<3; j++) {
					sprintf(frameName, "Item_%d_%d.png",(int)m_eBlockItem,j+1);
					m_pItemAni->addSpriteFrameWithFileName(frameName);
			}
			m_pItemAni->setDelayPerUnit(0.25f);
			m_pBlockAnt = CCAnimate::create(m_pItemAni);
			m_pItem = CCSprite::spriteWithFile("NewSprite.png");
			m_pItem->setPosition( ccp((m_stPos.x) * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			m_pItem->setScaleX( 1.2f * D_SCALE_WIDTH);
			m_pItem->setScaleY( 1.2f * D_SCALE_HEIGHT);
			//m_pItem->setColor(ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
			m_pThisScene->addChild(m_pItem, 23);
			//m_pBlock->runAction(m_pBlockAnt);
			m_pItem->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
			m_pItem->setAnchorPoint(ccp(0.5,0.5));

			////////////////////////////////////////////////////// CCSprite
			//sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


			//m_pItem = CCSprite::create(frameName);
			////m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
			//m_pItem->setAnchorPoint(ccp(0.5f,0.5f));
			////m_pItem->setScale(1.0f);

			//m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			//m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
			//m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);

			//m_pThisScene->addChild(m_pItem, 23);
			//////////////////////////////////////////////////////
		}
		else												  //!< 90% È®·ü·Î ±âº»
		{
			m_eBlockItem = E_BLOCKITEM_NONE;
		}
	}
	else												  //!< 90% È®·ü·Î ±âº»
	{
		m_eBlockItem = E_BLOCKITEM_NONE;
	}
	m_fGPM = 0.0f;
}

void CBlock::Update(float dt)
{		
	if(m_bLive == true)

	{
		if(m_eBlockState == E_BLOCKSTATE_FALL_FALLING && m_bDraged == false && m_bFallFinished == false)
		{
			if(m_fNowDistance < m_fDistance)
			{
				m_stPos.y -= (m_fSpeed * dt) ;
				m_fNowDistance += (m_fSpeed * dt) ;
				m_fSpeed += (m_fPlusSpeed * dt);
				if(m_fNowDistance >= m_fDistance)
				{
					m_fGPM = (m_fStartY - m_fDistance) - m_stPos.y;
					m_stPos.y		    = m_fStartY - m_fDistance;
					// m_fSpeed			= D_BLOCK_SPEED;
					// m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
					m_fNowDistance		= 0.0f;
					m_fDistance			= 64.0f;
					//m_eBlockState		= E_BLOCKSTATE_FALL_NONE;
					m_bFallFinished = true;
				}
			}
		}

		if(m_nBounceLevel > 0)
		{
			m_stPos.y += m_fBouncePower * dt;
			m_fBouncePower -= 300 * dt;
			if(m_stPos.y <= m_fBounceLine)
			{
				m_nBounceLevel--;
				m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
				m_stPos.y = m_fBounceLine;
			}
		}

		if(m_fNowColorAlpha < m_fTargetColorAlpha)
		{
			m_fNowColorAlpha += dt * 1.5;
			if(m_fNowColorAlpha > m_fTargetColorAlpha)
				m_fNowColorAlpha = m_fTargetColorAlpha;
		}
		else if(m_fNowColorAlpha > m_fTargetColorAlpha)
		{
			m_fNowColorAlpha -= dt * 1.2f ; //!< ¸¶³ª°¡ ºüÁö´Â ¼Óµµ´Â Â÷¿À¸£´Â ¼ÓµµÀÇ 70%
			if(m_fNowColorAlpha < m_fTargetColorAlpha)
				m_fNowColorAlpha = m_fTargetColorAlpha;
		}

		if(m_fNowAlpha > m_fTargetAlpha)
		{
			m_fNowAlpha -= dt * 2.2f;
			if(m_fNowAlpha < m_fTargetAlpha)
				m_fNowAlpha = m_fTargetAlpha;
		}
	
		m_pBlock->setPosition(ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT ));
		//m_pBlock[E_BLOCKSTATE_ACT_NONE]->setColor(ccc3(255 * (1.0f - m_fNowColorAlpha),255 * m_fNowColorAlpha,255 * (1.0f - m_fNowColorAlpha)));
		m_pBlock->setOpacity(255 * m_fNowAlpha);

		if(m_eBlockItem != E_BLOCKITEM_NONE)
			m_pItem->setOpacity(255 * m_fNowAlpha);

		m_pNoSelect->setOpacity(255 * m_fNowColorAlpha);
		
		if(m_fNowAlpha < 1.0f)
			m_pNoSelect->setVisible(false);

		m_pNoSelect->setPosition(ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT ));
		
		if(m_eBlockItem == E_BLOCKITEM_LIGHTNING)
			m_pItem->setPosition( ccp((m_stPos.x + 3) * D_SCALE_WIDTH, (m_stPos.y ) * D_SCALE_HEIGHT) );
		else if(m_eBlockItem == E_BLOCKITEM_BOMB)
		{
			if(m_eBlockNumber == E_BLOCKNUMBER_YELLOW)
				m_pItem->setPosition( ccp((m_stPos.x +1 ) * D_SCALE_WIDTH, (m_stPos.y + 6 )  * D_SCALE_HEIGHT) );
			else if(m_eBlockNumber == E_BLOCKNUMBER_PURPLE)
				m_pItem->setPosition( ccp((m_stPos.x +1 ) * D_SCALE_WIDTH, (m_stPos.y + 0 )  * D_SCALE_HEIGHT) );
			else
				m_pItem->setPosition( ccp((m_stPos.x +1 ) * D_SCALE_WIDTH, (m_stPos.y + 3 )  * D_SCALE_HEIGHT) );
		}
		else if(m_eBlockItem == E_BLOCKITEM_SPACE)
		{
			m_pItem->setPosition( ccp((m_stPos.x ) * D_SCALE_WIDTH, (m_stPos.y )  * D_SCALE_HEIGHT) );
		}
		//m_pNoSelect->setVisible(m_bNoSelect);
	}
	else if(m_bLive == false)
	{
		
	}
}
void CBlock::Alphaing()
{
	m_fTargetAlpha = 0.0f;
}
void CBlock::Die()
{
	if(m_bLive == true)
	{
		m_pThisScene->removeChild(m_pBlock,true);

		if(m_eBlockItem != E_BLOCKITEM_NONE)
			m_pThisScene->removeChild(m_pItem,true);
	}
	// printf("ºí·ÏÀÌ¹ÌÁö»èÁ¦\n");
	
	
	
	m_bLive = false;
//	if(m_bLive == true)
//	{
//		m_pThisScene->removeChild(m_pBlock,true);
//		m_pThisScene->removeChild(m_pBlock_Pause,true);
//		m_pThisScene->removeChild(m_pBlock_Freeze,true);
//		m_pThisScene->removeChild(m_pBlock_Angry,true);
//		if(m_eBlockItem != E_BLOCKITEM_NONE)
//		{
//			m_pThisScene->removeChild(m_pItem,true);
//			m_eBlockItem = E_BLOCKITEM_NONE;
//		}
//	}
//	/*delete m_pBlockAni;
//	delete m_pBlockAnt;*/
//
//	m_bLive = false;
//
//	m_pFreeze->setVisible(false);
//
//
//	
//	//m_pBlockAni->autorelease();
//	//m_pBlockAnt->autorelease();
//	//delete m_pBlockAni;
//	//delete m_pBlockAnt;
//
//	//!< m_pErosoin->setVisible(true);
//	//!< m_pErosoin_Border->setVisible(true);
///*
//	for(int i=0; i<E_BLOCKNUMBER_MAX ; i++)
//	{
//		m_pBlock[i]->setVisible(true);
//		m_pBlock_Pause[i]->setVisible(true);
//	}*/
//	/*m_pBlock->setVisible(true);
//	m_pBlock_Pause->setVisible(true);
//*/
//	m_pSelect->setVisible(false);

}
bool CBlock::HitTest(float nX, float nY)
{
	if(m_bLive == false)
		return false;
	if(nX >= (m_stPos.x - (D_BLOCK_WIDTH/2)) * D_SCALE_WIDTH  && nX <= (m_stPos.x + (D_BLOCK_WIDTH/2)) * D_SCALE_WIDTH  &&
		nY >= (m_stPos.y - (D_BLOCK_HEIGHT/2)) * D_SCALE_HEIGHT  && nY <= (m_stPos.y + (D_BLOCK_HEIGHT/2)) * D_SCALE_HEIGHT )
	{
		return true;
	}
	return false;
}



void CBlock::ShowUpdate()
{
	/*if(m_bLive == false)
	{
		m_pFreeze->setVisible(false);
		m_pSelect->setVisible(false);
	}*/
}

void CBlock::CheckReset()
{
	m_bChecked = false;
	m_bFocused = false;
}
void CBlock::NextBlockNumber()
{
	/*E_BLOCKNUMBER eBlockNumber = (E_BLOCKNUMBER)((int)m_eBlockNumber + 1);
	if((int)eBlockNumber >= (int)E_BLOCKNUMBER_MAX)
	{
		eBlockNumber = E_BLOCKNUMBER_RED;
	}

	SetBlockNumber(eBlockNumber);*/
}
void CBlock::SetBlockNumber(E_BLOCKNUMBER eBlockNumber)
{
	/*char frameName[256];
	m_eBlockNumber = eBlockNumber;

	m_pThisScene->removeChild(m_pBlock,true);

	sprintf(frameName,"Block_%d.png",(int)m_eBlockNumber + 1);
	m_pBlock = CCSprite::create(frameName);
	m_pBlock->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBlock->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBlock->setAnchorPoint(ccp(0.5f,0.5f));
	m_pThisScene->addChild(m_pBlock, 20);*/
}