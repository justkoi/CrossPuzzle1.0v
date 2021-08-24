#include "stdafx.h" 


void CComboManager::Init(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;

	m_nCombo = 0;
	m_nTargetCombo = 0;

	m_stCombo.m_pCombo = CCSprite::create("Combo.png");
	m_stCombo.m_pCombo->setPosition( ccp( 190 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(100)  * D_SCALE_HEIGHT) );
	m_stCombo.m_pCombo->setScaleX(1.0f * D_SCALE_WIDTH);
	m_stCombo.m_pCombo->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pThisScene->addChild(m_stCombo.m_pCombo, 35);

	m_stCombo.m_pNumber = new CNumber();
	m_stCombo.m_pNumber->Init(m_pThisScene,ccp(1.0f,1.0f),g_nCombo,ccp(260 * D_SCALE_WIDTH, D_PHOTOSHOP_Y(100)  * D_SCALE_HEIGHT),33,2);
	
	m_stCombo.m_pCombo->setVisible(false);
	m_stCombo.m_pNumber->SetVisible(false);

	m_stCombo.m_fTimer = 2.0f;
	m_bPlayEffect = false;
}
void CComboManager::Update(float dt, int nCombo) //!< 콤보수치 2일때 1부터 시작 됨
{
	m_stCombo.m_fTimer += dt;
	m_stCombo.m_pNumber->Update(dt);
	//m_stCombo.m_pNumber->SetColor(ccc3(255 * 0.3,255 *1.0,255 * 0.3f));
	m_nTargetCombo = nCombo - 1;
	if(m_nTargetCombo <= 0)
		m_nTargetCombo = 0;

	if( m_stCombo.m_fTimer >= 0.2f )
	{
		if(m_nCombo < m_nTargetCombo)
		{
			m_nCombo++;

			if(g_bFever == false)
			{
				if(g_nStage == 12) //!<DevOption
					g_fFevergauge += 30.0f + (float)m_nCombo;
				else
					g_fFevergauge += 10.0f + (float)m_nCombo;
			}
			m_bPlayEffect = true;
			m_stCombo.m_pNumber->SetNumber(m_nCombo);
			m_stCombo.m_fTimer = 0.0f;

			m_stCombo.m_pCombo->setVisible(true);
			m_stCombo.m_pNumber->SetVisible(true);
			m_stCombo.m_pCombo->setOpacity(255 * 0.0f);
			m_stCombo.m_pNumber->SetOpacity(0.0f);
		}
	}

	if( m_stCombo.m_fTimer <= 0.8f)
	{
		m_stCombo.m_pCombo->setOpacity(255 * (m_stCombo.m_fTimer + 0.2f));
		m_stCombo.m_pNumber->SetOpacity(m_stCombo.m_fTimer);
	}
	else if( m_stCombo.m_fTimer > 1.2f && m_stCombo.m_fTimer <= 1.5f )
	{
		m_stCombo.m_pCombo->setScale(1.0f);
		m_stCombo.m_pNumber->SetSize(ccp(1.0f,1.0f));

		m_stCombo.m_pCombo->setOpacity(255 * (1.0f - (((m_stCombo.m_fTimer-0.5f) - 0.5f) * 2.0f)));
		m_stCombo.m_pNumber->SetOpacity( (1.0f - (((m_stCombo.m_fTimer-0.5f) - 0.5f) * 2.0f)));
	}
	else if(m_stCombo.m_fTimer > 1.5f )
	{
		m_stCombo.m_pCombo->setVisible(false);
		m_stCombo.m_pNumber->SetVisible(false);
	}
	
}
void CComboManager::Exit()
{
	m_stCombo.m_pNumber->Exit();
	delete m_stCombo.m_pNumber;
	m_pThisScene->removeChild(m_stCombo.m_pCombo, true);
}

void CComboManager::SetCombo(int nTargetCombo)
{
	m_nTargetCombo = nTargetCombo;
}