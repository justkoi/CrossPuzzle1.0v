#include "stdafx.h"

class CDot
{
private:
	

public:
	CCPoint m_stPos;
	CCSprite* m_pDot;
	bool	m_bItem; //!< 아이템인지 아닌지 표시
	CCLayer* m_pThisScene;
public:

	CDot(CCPoint stPos);
	CDot(CCPoint stPos, CCLayer* pThisScene);


};