#include "stdafx.h"
int g_nIndex = 0;

CCreditBlock::CCreditBlock(CCLayer * pThisScene, CCPoint stPos, float fGround, float fDelayTime, string strFilePath)
{
	m_pBlock = CCSprite::create(strFilePath.c_str());
	m_pBlock->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBlock->setScaleY(1.00f * D_SCALE_HEIGHT);
	pThisScene->addChild(m_pBlock, 1);

	m_stPos = stPos;
	m_fGround = fGround;
	m_fDelayTime = fDelayTime;
	m_nState = 0;
	m_fSpeed = D_BLOCK_SPEED;
	m_fJumpPower = 140.0f;
	m_bInit = false;
	m_nIndex = g_nIndex;
	g_nIndex++;
	m_fResetTime = 0.0f;
	m_fResetTimer = 0.0f;
}



void CCreditBlock::Update(float dt, float fTimer)
{
	if(m_fResetTime > 0.0f)
	{
		m_fResetTimer += dt;
		if(m_fResetTimer >= m_fResetTime)
		{
			m_fResetTime = 0.0f;
			m_fResetTimer = 0.0f;

			m_nState = 2;
			m_fSpeed = m_fJumpPower;
			m_stPos.y = m_fGround + 3.0f;
		}
	}
	if (fTimer >= m_fDelayTime && m_bInit == false) {
		m_nState = 1;
		m_bInit = true;
	}
	if (m_nState == 1) {
		m_stPos.y -= m_fSpeed * dt;
		m_fSpeed += D_BLOCK_SPEED * dt * 0.5f;
		if(m_stPos.y <= m_fGround)
		{
			m_nState = 2;
			m_fSpeed = m_fJumpPower;
			m_stPos.y = m_fGround + 3.0f;
		}
	}
	else if (m_nState == 2)
	{
		m_stPos.y += m_fSpeed * dt;
		m_fSpeed -= 400 * dt;
		if(m_stPos.y <= m_fGround)
		{
			m_stPos.y = m_fGround;
			m_nState = 3;
		}
	}
	m_pBlock->setPositionX(m_stPos.x * D_SCALE_WIDTH);
	m_pBlock->setPositionY(m_stPos.y * D_SCALE_HEIGHT);

	
}

void CCreditBlock::Exit()
{
	m_pBlock->removeFromParentAndCleanup(true);
}

void CCreditBlock::Reset(float fResetTime)
{
	m_fResetTime = fResetTime;
}