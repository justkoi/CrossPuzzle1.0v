#include "stdafx.h"


void CNumber::Init(CCLayer* pThisScene, CCPoint stSize, int nNumber, CCPoint stPos, int nLayer,int nStyle)
{
	m_nNumber = nNumber;
	m_stPos = stPos;
	m_pThisScene = pThisScene;
	m_nLayer = nLayer;
	m_stSize = stSize;
	m_nStyle = nStyle;

	m_bVisible = true;
	m_fOpacity = 1.0f;
	m_stAnchorPoint = ccp(0.5f,0.5f);

	SetNumber(m_nNumber);
	SetVisible(m_bVisible);
}
void CNumber::Update(float dt)
{
	if(m_nNumber < 0)
	{
		m_nNumber = 0;
	}
	
	if(m_nTargetNumber < 0)
	{
		m_nTargetNumber = 0;
	}

	if(m_nNumber < m_nTargetNumber)
	{
		m_nNumber++;
		m_nNumber += (m_nTargetNumber - m_nNumber) * 0.05f;
		SetNumber(m_nNumber);
		if(m_nNumber > m_nTargetNumber)
		{
			m_nNumber = m_nTargetNumber;
		}
	}

	SetVisible(m_bVisible);
}

void CNumber::SetPositionY(float fPosY)
{
	m_stPos.y = fPosY;
	vector<CCSprite*>::iterator it;
	for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
	{
		(*it)->setPositionY( m_stPos.y );
	}
}

void CNumber::SetPos(CCPoint stPos)
{
	m_stPos = stPos;
	vector<CCSprite*>::iterator it;
	for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
	{
		(*it)->setPosition( m_stPos );
	}
}

void CNumber::SetOpacity(float fOpacity)
{
	m_fOpacity = fOpacity;
	vector<CCSprite*>::iterator it;
	for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
	{
		(*it)->setOpacity(255 * m_fOpacity);
	}
}
void CNumber::SetColor(ccColor3B ccColor)
{
	vector<CCSprite*>::iterator it;
	for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
	{
		(*it)->setColor(ccColor);
	}
}
void CNumber::SetAnchorPoint(CCPoint ccAnchorPoint)
{
	m_stAnchorPoint = ccAnchorPoint;
	vector<CCSprite*>::iterator it;
	for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
	{
		(*it)->setAnchorPoint(m_stAnchorPoint);
	}
}
void CNumber::Exit()
{
	vector<CCSprite*>::iterator it;
	if(m_pNumberList.size() >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end();)
		{
			m_pThisScene->removeChild((*it),true);
			it = m_pNumberList.erase(it);
		}
	}
}

void CNumber::SetNumber(int nNumber)
{
	char strTemp[256];
	int nCount = 0;
	int nCountNumber = 0;

	
	m_nNumber = nNumber;

	if(m_nNumber < 0)
	{
		m_nNumber = 0;
	}


	nCountNumber = m_nNumber;


	vector<CCSprite*>::iterator it;
	if(m_pNumberList.size() >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end();)
		{
			m_pThisScene->removeChild((*it),true);
			it = m_pNumberList.erase(it);
		}
	}
	m_pNumberList.clear();
	do 
	{
		sprintf(strTemp,"%d_%d.png",(int)nCountNumber%10,(int)m_nStyle);
		CCSprite* m_pTemp = CCSprite::create(strTemp);
		m_pTemp->setPositionX( m_stPos.x - ((20*m_stSize.x) * nCount) );
		m_pTemp->setPositionY( m_stPos.y );
		m_pTemp->setScaleX(m_stSize.x);
		m_pTemp->setScaleY(m_stSize.y);
		m_pTemp->setVisible(m_bVisible);
		m_pThisScene->addChild(m_pTemp, m_nLayer); //!>, Àá°ÜÀÕÀ½ 27
		m_pNumberList.push_back(m_pTemp);
		nCount++;
	}while((nCountNumber /= 10) > 0);

	nCount-=1;

	if(nCount >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
		{
			(*it)->setPositionX( (*it)->getPositionX() + (((20*m_stSize.x) * (nCount))/2));
		}
	}
	SetAnchorPoint(m_stAnchorPoint);
}

void CNumber::EffectNumber(int nNumber)
{
	m_nTargetNumber = nNumber;
}
void CNumber::SetSize(CCPoint stSize)
{
	vector<CCSprite*>::iterator it;
	m_stSize = stSize;

	if(m_pNumberList.size() >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
		{
			(*it)->setScaleX(stSize.x);
			(*it)->setScaleY(stSize.y);
		}
	}
}
void CNumber::SetVisible(bool bVisible)
{
	vector<CCSprite*>::iterator it;
	m_bVisible = bVisible;
	if(m_pNumberList.size() >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
		{
			(*it)->setVisible(m_bVisible);
		}
	}
}