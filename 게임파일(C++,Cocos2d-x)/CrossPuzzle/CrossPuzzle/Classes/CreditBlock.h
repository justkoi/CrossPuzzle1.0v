#pragma once

#include "stdafx.h"


class CCreditBlock
{
	
public:
	CCSprite* m_pBlock;

	CCPoint m_stPos;
	float m_fGround;
	float m_fDelayTime;
	int m_nState;
	float m_fSpeed;
	float m_fJumpPower;
	bool m_bInit;
	int m_nIndex;
	float m_fResetTime;
	float m_fResetTimer;
public:
	CCreditBlock(CCLayer * pThisScene, CCPoint stPos, float fGround, float fDelayTime, string strFilePath);
	void Update(float dt, float fTimer);

	void Exit();
	void Reset(float fResetTime);
};