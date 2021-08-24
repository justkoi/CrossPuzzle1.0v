#include "stdafx.h" 

void CEffectManager::Init(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;

}

void CEffectManager::Pause()
{
	if(m_pEffectList.size() >= 1)
	{
		list<stAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end(); it++)
		{
			(*it)->m_pBlock->getActionManager()->pauseTarget((*it)->m_pBlock);
		}
	}
}

void CEffectManager::Resume()
{
	if(m_pEffectList.size() >= 1)
	{
		list<stAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end(); it++)
		{
			(*it)->m_pBlock->getActionManager()->resumeTarget((*it)->m_pBlock);
		}
	}
}
void CEffectManager::Exit()
{
	if(m_pEffectList.size() >= 1)
	{
		list<stAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end();)
		{
			m_pThisScene->removeChild((*it)->m_pBlock,true);
			delete (*it);
			it = m_pEffectList.erase(it);
		}
	}
}
void CEffectManager::Update(float dt)
{
	if(m_pEffectList.size() >= 1)
	{
		list<stAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end();)
		{
			(*it)->m_fTimer += dt;
			if((*it)->m_nIndex == 7)// || (*it)->m_nIndex == 8)
			{
				if((*it)->m_fTimer >= 0.5f)
					(*it)->m_pBlock->setOpacity(255 * (1.0f - (((*it)->m_fTimer - 0.5f)*2)));
			}
			if((*it)->m_nIndex < 7 && (*it)->m_fTimer >= 0.5f)
			{
				m_pThisScene->removeChild((*it)->m_pBlock,true);
				delete (*it);
				it = m_pEffectList.erase(it);
			}
			else if((*it)->m_nIndex == 7 && (*it)->m_fTimer >= 1.0f)
			{
				
				m_pThisScene->removeChild((*it)->m_pBlock,true);
				delete (*it);
				it = m_pEffectList.erase(it);
			}
			else if((*it)->m_nIndex == 8 && (*it)->m_fTimer >= 1.0f)
			{
				
				m_pThisScene->removeChild((*it)->m_pBlock,true);
				delete (*it);
				it = m_pEffectList.erase(it);
			}
			else if((*it)->m_nIndex == 9 && (*it)->m_fTimer >= 0.49f)
			{
				
				m_pThisScene->removeChild((*it)->m_pBlock,true);
				delete (*it);
				it = m_pEffectList.erase(it);
			}
			else if((*it)->m_nIndex == 10 && (*it)->m_fTimer >= 0.81f)
			{
				
				m_pThisScene->removeChild((*it)->m_pBlock,true);
				delete (*it);
				it = m_pEffectList.erase(it);
			}
			else
			{
				it++;
			}
		
		}
	}
}
void CEffectManager::Insert(int nIndex, float fX, float fY, float fSizeW , float fSizeH, float fAngle)
{
	char frameName[256];
	CCAnimation* m_pBlockAni;
	CCActionInterval * m_pBlockAnt;
	CCSprite * m_pBlock;
	stAnimation* pTempAni;
	switch(nIndex)
	{
	case 1:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<10; j++) {
				sprintf(frameName, "Block_Pop_%d_%d.png",nIndex,j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.05f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		m_pThisScene->addChild(m_pBlock, 22);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 1;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 2:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<10; j++) {
				sprintf(frameName, "Block_Pop_%d_%d.png",nIndex,j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.05f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		m_pThisScene->addChild(m_pBlock, 22);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 1;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 3:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<10; j++) {
				sprintf(frameName, "Block_Pop_%d_%d.png",nIndex,j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.05f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		m_pThisScene->addChild(m_pBlock, 22);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 1;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 4:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<10; j++) {
				sprintf(frameName, "Block_Pop_%d_%d.png",nIndex,j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.05f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		m_pThisScene->addChild(m_pBlock, 22);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 1;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 5:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<10; j++) {
				sprintf(frameName, "Block_Pop_%d_%d.png",nIndex,j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.05f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		m_pThisScene->addChild(m_pBlock, 22);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 1;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 6:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<10; j++) {
				sprintf(frameName, "Block_Pop_%d_%d.png",nIndex,j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.05f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		m_pThisScene->addChild(m_pBlock, 22);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 1;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 7:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<1; j++) {
				sprintf(frameName, "LineEffect3_%d.png",j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.07f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		//m_pBlock->setColor(ccc3(255 * 0.8f,255 * 0.3f,255 * 0.3f));
		m_pBlock->setRotation(fAngle);
		m_pThisScene->addChild(m_pBlock, 25);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.0,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 7;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 8:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<1; j++) {
				sprintf(frameName, "Circle_%d.png",j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.07f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		//m_pBlock->setColor(ccc3(255 * 0.8f,255 * 0.3f,255 * 0.3f));
		m_pBlock->setRotation(fAngle);
		m_pThisScene->addChild(m_pBlock, 25);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 8;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 9:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<7; j++) {
				sprintf(frameName, "LineEffect_%d.png",j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.07f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
		m_pBlock->setRotation(fAngle);
		m_pThisScene->addChild(m_pBlock, 25);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 9;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	case 10:
		m_pBlockAni = CCAnimation::animation();
		for(int j=0; j<9; j++) {
				sprintf(frameName, "FireEffect_%d.png",j+1);
				m_pBlockAni->addSpriteFrameWithFileName(frameName);
		}
		m_pBlockAni->setDelayPerUnit(0.09f);
		m_pBlockAnt = CCAnimate::create(m_pBlockAni);
		m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
		m_pBlock->setPosition( ccp(fX * D_SCALE_WIDTH, fY * D_SCALE_HEIGHT));
		m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH * 0.8f);
		m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT * 0.8f);
		m_pBlock->setRotation(fAngle);
		m_pThisScene->addChild(m_pBlock, 25);
		//m_pBlock->runAction(m_pBlockAnt);
		m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
		m_pBlock->setAnchorPoint(ccp(0.5,0.5));

		pTempAni = new stAnimation();
		pTempAni->m_pBlockAni = m_pBlockAni;
		pTempAni->m_pBlock = m_pBlock;
		pTempAni->m_nIndex = 10;
		pTempAni->m_fTimer = 0.0f;
		m_pEffectList.push_back(pTempAni);
		break;
	}
	
}
