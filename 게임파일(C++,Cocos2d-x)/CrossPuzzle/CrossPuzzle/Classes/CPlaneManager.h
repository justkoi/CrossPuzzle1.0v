#pragma once


#include "stdafx.h" 

using namespace std;

USING_NS_CC;

typedef struct
{
	int m_nIndex;
	CCSprite* m_pPlane;
	float m_fTimer;
	float m_fStartY;
}stPlaneChunk;

class CPlaneManager
{
public:
	CCLayer* m_pThisScene;			//!< 출력 대상 신
	
	vector<stPlaneChunk*> m_pPlaneList;	//!< 모든 출력중인 숫자 보관 STL LIST

public:
	
	//!< 숫자, 좌표, 크기
	void Insert(int nIndex, float fX, float fY, float fSizeW = 1.0f, float fSizeH = 1.0f);



	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();
};