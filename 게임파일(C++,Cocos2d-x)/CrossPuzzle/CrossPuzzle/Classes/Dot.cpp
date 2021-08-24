#include "stdafx.h"

CDot::CDot(CCPoint stPos)
{
	m_stPos = stPos;
	m_bItem = false;
}
CDot::CDot(CCPoint stPos, CCLayer* pThisScene)
{
	m_stPos = stPos;
	m_pThisScene = pThisScene;
	m_bItem = true;

	m_pDot = CCSprite::create("Circle_1.png");
	m_pDot->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pDot->setScaleX(1.30f * D_SCALE_WIDTH);
	m_pDot->setScaleY(1.30f * D_SCALE_HEIGHT);
	m_pDot->setVisible(true);
	m_pDot->setAnchorPoint(ccp(0.5f,0.5f));
	m_pDot->setColor(ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f));
	m_pThisScene->addChild(m_pDot, 24);
}