#pragma once


#include "stdafx.h" 
#include <list>
using namespace std;

USING_NS_CC;

typedef struct
{
	CCAnimation* m_pBlockAni;
	CCSprite * m_pBlock;
	int m_nIndex;
	float m_fTimer;
}stAnimation;

class CEffectManager
{
public:
	CCLayer* m_pThisScene;			//!< 출력 대상 신
	
	list<stAnimation*> m_pEffectList;	//!< 모든 출력중인 이펙트 보관 STL LIST

public:
	
	void Insert(int nIndex, float fX, float fY, float fSizeW = 1.0f, float fSizeH = 1.0f, float fAngle = 0.0f);



	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();

	void Pause();
	void Resume();
};