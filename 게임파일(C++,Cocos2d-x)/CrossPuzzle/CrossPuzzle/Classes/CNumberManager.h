#pragma once


#include "stdafx.h" 

using namespace std;

USING_NS_CC;

typedef struct
{
	CNumber* m_Number;
	float m_fTimer;
	float m_fStartY;
}stNumberChunk;

class CNumberManager
{
public:
	CCLayer* m_pThisScene;			//!< 출력 대상 신
	
	vector<stNumberChunk*> m_pNumberList;	//!< 모든 출력중인 숫자 보관 STL LIST

public:
	
	//!< 숫자, 좌표, 크기
	void Insert(int nNumber, float fX, float fY, ccColor3B ccColor, float fSizeW = 0.6f, float fSizeH = 0.6f);



	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();
};