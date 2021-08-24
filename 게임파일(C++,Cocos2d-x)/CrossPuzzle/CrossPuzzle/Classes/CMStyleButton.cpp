#include "stdafx.h"


void CMStyleButton::Init(CCLayer* pThisScene, int nLayer, const char * m_pButtonImage_wait, const char * m_pButtonImage_overing, CCPoint CPoint, float fScaleMax, float fScaleMin, float fDtValue)
{
	m_pThisScene = pThisScene;
	m_nLayer = nLayer;
	m_CPoint = CPoint;

	m_eState = E_BUTTON_WAIT;
	m_fScale = fScaleMax;
	m_fScaleMin = fScaleMin;
	m_fScaleMax = fScaleMax;
	m_fTargetScale = fScaleMin;
	m_fDtValue = fDtValue;
	m_bPauseUpdate = false;
	m_bVisible = true;

	m_pButtonImage[E_BUTTON_WAIT] = CCSprite::create(m_pButtonImage_wait);
	m_pButtonImage[E_BUTTON_WAIT]->setPosition( m_CPoint );
	m_pButtonImage[E_BUTTON_WAIT]->setScaleX(m_fScaleMax * D_SCALE_WIDTH);
	m_pButtonImage[E_BUTTON_WAIT]->setScaleY(m_fScaleMax * D_SCALE_HEIGHT);
    pThisScene->addChild(m_pButtonImage[E_BUTTON_WAIT], nLayer);
	m_CHitRect[E_BUTTON_WAIT].m_fWidth = m_pButtonImage[E_BUTTON_WAIT]->getTextureRect().CCRectGetMaxX(m_pButtonImage[E_BUTTON_WAIT]->getTextureRect());
	m_CHitRect[E_BUTTON_WAIT].m_fHeight = m_pButtonImage[E_BUTTON_WAIT]->getTextureRect().CCRectGetMaxY(m_pButtonImage[E_BUTTON_WAIT]->getTextureRect());
	
	m_pButtonImage[E_BUTTON_OVERING] = CCSprite::create(m_pButtonImage_overing);
	m_pButtonImage[E_BUTTON_OVERING]->setPosition( m_CPoint );
	m_pButtonImage[E_BUTTON_OVERING]->setScaleX(m_fScaleMax * D_SCALE_WIDTH);
	m_pButtonImage[E_BUTTON_OVERING]->setScaleY(m_fScaleMax * D_SCALE_HEIGHT);
    pThisScene->addChild(m_pButtonImage[E_BUTTON_OVERING], nLayer);
	m_CHitRect[E_BUTTON_OVERING].m_fWidth = m_pButtonImage[E_BUTTON_OVERING]->getTextureRect().CCRectGetMaxX(m_pButtonImage[E_BUTTON_OVERING]->getTextureRect());
	m_CHitRect[E_BUTTON_OVERING].m_fHeight = m_pButtonImage[E_BUTTON_OVERING]->getTextureRect().CCRectGetMaxY(m_pButtonImage[E_BUTTON_OVERING]->getTextureRect());
	
	//m_bTouched = false;
	m_bActioned = false;
	ChangeState(E_BUTTON_WAIT);
}

void CMStyleButton::setPositionY(float fPosY)
{
	m_CPoint.y = fPosY;
	for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
	{
		m_pButtonImage[i]->setPositionY(m_CPoint.y);
	}
}
void CMStyleButton::ChangeState(eButtonState eState)
{
	m_eState = eState;
	if(m_eState == E_BUTTON_WAIT)
	{
		m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
		m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
		m_fTargetScale = m_fScaleMax;
	}
	else if(m_eState == E_BUTTON_OVERING)
	{
		m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		m_fTargetScale = m_fScaleMin;
	}
}
void CMStyleButton::Update(float dt)
{
	if(m_bPauseUpdate == true)
		return;

	if(m_bActioned == false)
	{
		if(m_eState == E_BUTTON_WAIT)
		{
			if(m_fScale < m_fTargetScale)
			{
				//!< 눌렀다 떌대 효과
				//!< 요 밑부분을 주석걸면 효과 없음
				////////////////////////////
				m_fScale += dt * m_fDtValue;
				if(m_fScale >= m_fTargetScale)
				{
					m_fScale = m_fTargetScale;
				}
				//////////////////////////
			}
		}
		else if(m_eState == E_BUTTON_OVERING)
		{
			if(m_fScale > m_fTargetScale)
			{
				//!< 눌렀다 떌대 효과
				//!< 요 밑부분을 주석걸면 효과 없음
				////////////////////////////
				m_fScale -= dt * m_fDtValue;
				if(m_fScale <= m_fTargetScale)
				{
					m_fScale = m_fTargetScale;
				}
				//////////////////////////
			}
		}
	}
	for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
	{
		m_pButtonImage[i]->setScaleX(m_fScale * D_SCALE_WIDTH);
		m_pButtonImage[i]->setScaleY(m_fScale * D_SCALE_HEIGHT);
	}
}

void CMStyleButton::Exit()
{

}


void CMStyleButton::TouchBegan(CCPoint stPos)
{
	//!< 원형충돌
	float fLine = sqrt(((stPos.x - m_CPoint.x)*(stPos.x - m_CPoint.x)) + ((stPos.y- m_CPoint.y)*(stPos.y- m_CPoint.y)));

	if(m_bPauseUpdate == true)
		return;
	if(m_bVisible == false)
		return;
	//!< 주석부분은 사각형충돌
	/*if(stPos.x >= m_CPoint.x - (m_CHitRect[m_eState].m_fWidth/2) && stPos.x <= m_CPoint.x +  (m_CHitRect[m_eState].m_fWidth/2) &&
		stPos.y <= m_CPoint.y + (m_CHitRect[m_eState].m_fHeight/2) && stPos.y >= m_CPoint.y - (m_CHitRect[m_eState].m_fHeight/2)  )
	{*/
	if(fLine <= m_CHitRect[m_eState].m_fWidth/2)
	{
		ChangeState(E_BUTTON_OVERING);
		m_bTouched = true;
		/*for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
		{
			m_pButtonImage[i]->setOpacity(255 * 0.5f);
		}*/
	}
}
void CMStyleButton::TouchEnded(CCPoint stPos)
{
	//!< 원형충돌
	float fLine = sqrt(((stPos.x - m_CPoint.x)*(stPos.x - m_CPoint.x)) + ((stPos.y- m_CPoint.y)*(stPos.y- m_CPoint.y)));

	if(m_bPauseUpdate == true)
		return;
	if(m_bVisible == false)
		return;
	//!< 주석부분은 사각형충돌
	/*if(stPos.x >= m_CPoint.x - (m_CHitRect[m_eState].m_fWidth/2) && stPos.x <= m_CPoint.x +  (m_CHitRect[m_eState].m_fWidth/2) &&
		stPos.y <= m_CPoint.y + (m_CHitRect[m_eState].m_fHeight/2) && stPos.y >= m_CPoint.y - (m_CHitRect[m_eState].m_fHeight/2)  )
	{*/
	if(fLine <= m_CHitRect[m_eState].m_fWidth/2)
	{
		//ChangeState(E_BUTTON_OVERING);
		if(m_eState == E_BUTTON_OVERING)
			m_bActioned = true;
	}
	else
	{
		ChangeState(E_BUTTON_WAIT);
	}
}
void CMStyleButton::Reset()
{
	m_bActioned = false;
	ChangeState(E_BUTTON_WAIT);
}