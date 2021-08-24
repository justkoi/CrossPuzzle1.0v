#pragma once


#include "stdafx.h" 
#include <vector>
using namespace std;

USING_NS_CC;

typedef struct
{
	CCSprite * m_pCombo;
	CNumber * m_pNumber;
	float m_fTimer;
}stCombo;

class CComboManager
{
private:
	CCLayer* m_pThisScene;			//!< 출력 대상 신

	stCombo m_stCombo;
	int m_nTargetCombo;
	
public:
	int m_nCombo;
	bool m_bPlayEffect;
	void SetCombo(int nTargetCombo);
public:
	void Init(CCLayer* pThisScene);
	void Update(float dt, int nCombo);
	void Exit();

};