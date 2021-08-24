#include "stdafx.h"

USING_NS_CC;

class CMap
{
private:


public:
	int			m_nBlockMap[D_BLOCKMAP_HEIGHT][D_BLOCKMAP_WIDTH];


	void Init();
	void Update();
	void Exit();


};