#pragma once

#include "stdafx.h"

using namespace std;
USING_NS_CC;

class CPopList
{
public:

	vector<CBlock*> m_BlockList; //!< 터트릴 블록 보관
	CBlock* m_FocusBlock; //!< 포커싱된 블록

public:

	void Init(int nIndex);
	
	
	void SelectBlock(stVec2i stBlockIndex);
	void CheckAround(); //!< 상하좌우 블록을 체크하여 포함 //!< 이미 포함된 블록은 포함시키지 않는다

	CBlock* getNextFocusBlock(); //!< 가장 다음 포커싱 될 블록 반환

};