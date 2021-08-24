#include "stdafx.h" 

void CPlaneManager::Init(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;
}
void CPlaneManager::Update(float dt)
{
	if(m_pPlaneList.size() >= 1)
	{
		vector<stPlaneChunk*>::iterator it;
		for(it = m_pPlaneList.begin(); it != m_pPlaneList.end();)
		{
			(*it)->m_fTimer += dt;

			if((*it)->m_nIndex >= 1 && (*it)->m_nIndex <= 100)
			{
				if((*it)->m_fTimer >= 1.0f)
				{
					m_pThisScene->removeChild((*it)->m_pPlane,true);
					delete (*it);
					it = m_pPlaneList.erase(it);
				}
				else
				{
					(*it)->m_pPlane->setPositionY(((*it)->m_fStartY + ((*it)->m_fTimer * 25.0f)) * D_SCALE_HEIGHT);
					//(*it)->m_pPlane->setOpacity(255 * (1.0f - (*it)->m_fTimer) );
					it++;
				}
			}
			else if((*it)->m_nIndex == 101)
			{
				if((*it)->m_fTimer >= 0.49f)
				{
					m_pThisScene->removeChild((*it)->m_pPlane,true);
					delete (*it);
					it = m_pPlaneList.erase(it);
				}
				else
				{
					it++;
				}
			}

		}
	}
}
void CPlaneManager::Insert(int nIndex, float fX, float fY, float fSizeW , float fSizeH)
{

	stPlaneChunk* m_pPlnaeChunk = new stPlaneChunk();
	m_pPlnaeChunk->m_nIndex = nIndex;
	if(nIndex == 101)
	{
		m_pPlnaeChunk->m_pPlane = CCSprite::create("BlackLine.png");
		m_pPlnaeChunk->m_pPlane->setPosition( ccp( fX * D_SCALE_WIDTH, fY  * D_SCALE_HEIGHT) );
		m_pPlnaeChunk->m_pPlane->setScaleX(fSizeW * D_SCALE_WIDTH);
		m_pPlnaeChunk->m_pPlane->setScaleY(fSizeH * D_SCALE_HEIGHT);
		m_pPlnaeChunk->m_pPlane->setOpacity(255 * 0.7f);
		m_pPlnaeChunk->m_pPlane->setVisible(true);
		m_pThisScene->addChild(m_pPlnaeChunk->m_pPlane, 24);

		m_pPlnaeChunk->m_fTimer = 0.0f;
		m_pPlnaeChunk->m_fStartY = fY;
		
		m_pPlaneList.push_back(m_pPlnaeChunk);
	}
	else if(nIndex == 1)
	{
		m_pPlnaeChunk->m_pPlane = CCSprite::create("Line_Dot.png");
		m_pPlnaeChunk->m_pPlane->setPosition( ccp( fX * D_SCALE_WIDTH, fY  * D_SCALE_HEIGHT) );
		m_pPlnaeChunk->m_pPlane->setScaleX(fSizeW * D_SCALE_WIDTH * 0.7f);
		m_pPlnaeChunk->m_pPlane->setScaleY(fSizeH * D_SCALE_HEIGHT * 0.7f);
		m_pPlnaeChunk->m_pPlane->setVisible(true);
		m_pThisScene->addChild(m_pPlnaeChunk->m_pPlane, 33);

		m_pPlnaeChunk->m_fTimer = 0.0f;
		m_pPlnaeChunk->m_fStartY = fY;
		
		m_pPlaneList.push_back(m_pPlnaeChunk);
	}
	else if(nIndex == 2)
	{
		m_pPlnaeChunk->m_pPlane = CCSprite::create("Line_Line.png");
		m_pPlnaeChunk->m_pPlane->setPosition( ccp( fX * D_SCALE_WIDTH, fY  * D_SCALE_HEIGHT) );
		m_pPlnaeChunk->m_pPlane->setScaleX(fSizeW * D_SCALE_WIDTH);
		m_pPlnaeChunk->m_pPlane->setScaleY(fSizeH * D_SCALE_HEIGHT);
		m_pPlnaeChunk->m_pPlane->setVisible(true);
		m_pThisScene->addChild(m_pPlnaeChunk->m_pPlane, 33);

		m_pPlnaeChunk->m_fTimer = 0.0f;
		m_pPlnaeChunk->m_fStartY = fY;
		m_pPlaneList.push_back(m_pPlnaeChunk);
	}
	else if(nIndex == 3)
	{
	m_pPlnaeChunk->m_pPlane = CCSprite::create("Line_Triangle.png");
		m_pPlnaeChunk->m_pPlane->setPosition( ccp( fX * D_SCALE_WIDTH, fY  * D_SCALE_HEIGHT) );
		m_pPlnaeChunk->m_pPlane->setScaleX(fSizeW * D_SCALE_WIDTH * 1.15f);
		m_pPlnaeChunk->m_pPlane->setScaleY(fSizeH * D_SCALE_HEIGHT * 1.15f);
		m_pPlnaeChunk->m_pPlane->setVisible(true);
		m_pThisScene->addChild(m_pPlnaeChunk->m_pPlane, 33);

		m_pPlnaeChunk->m_fTimer = 0.0f;
		m_pPlnaeChunk->m_fStartY = fY;
		m_pPlaneList.push_back(m_pPlnaeChunk);
	}
	else if(nIndex == 4)
	{
		m_pPlnaeChunk->m_pPlane = CCSprite::create("Line_Square.png");
		m_pPlnaeChunk->m_pPlane->setPosition( ccp( fX * D_SCALE_WIDTH, fY  * D_SCALE_HEIGHT) );
		m_pPlnaeChunk->m_pPlane->setScaleX(fSizeW * D_SCALE_WIDTH * 1.3f);
		m_pPlnaeChunk->m_pPlane->setScaleY(fSizeH * D_SCALE_HEIGHT * 1.3f);
		m_pPlnaeChunk->m_pPlane->setVisible(true);
		m_pThisScene->addChild(m_pPlnaeChunk->m_pPlane, 33);

		m_pPlnaeChunk->m_fTimer = 0.0f;
		m_pPlnaeChunk->m_fStartY = fY;
		m_pPlaneList.push_back(m_pPlnaeChunk);
	}
	else if(nIndex >= 5)
	{
		m_pPlnaeChunk->m_pPlane = CCSprite::create("Line_Pentagon.png");
		m_pPlnaeChunk->m_pPlane->setPosition( ccp( fX * D_SCALE_WIDTH, fY  * D_SCALE_HEIGHT) );
		m_pPlnaeChunk->m_pPlane->setScaleX(fSizeW * D_SCALE_WIDTH * 1.45f);
		m_pPlnaeChunk->m_pPlane->setScaleY(fSizeH * D_SCALE_HEIGHT * 1.45f);
		m_pPlnaeChunk->m_pPlane->setVisible(true);
		m_pThisScene->addChild(m_pPlnaeChunk->m_pPlane, 33);

		m_pPlnaeChunk->m_fTimer = 0.0f;
		m_pPlnaeChunk->m_fStartY = fY;
		m_pPlaneList.push_back(m_pPlnaeChunk);
	}
}

void CPlaneManager::Exit()
{
	
	vector<stPlaneChunk*>::iterator it;
	for(it = m_pPlaneList.begin(); it != m_pPlaneList.end();)
	{
		(*it)->m_pPlane->removeFromParentAndCleanup(true);
		delete (*it);
		it = m_pPlaneList.erase(it);
	}
	
}