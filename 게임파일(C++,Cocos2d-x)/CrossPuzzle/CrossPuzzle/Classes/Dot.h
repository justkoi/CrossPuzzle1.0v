#include "stdafx.h"

class CDot
{
private:
	

public:
	CCPoint m_stPos;
	CCSprite* m_pDot;
	bool	m_bItem; //!< ���������� �ƴ��� ǥ��
	CCLayer* m_pThisScene;
public:

	CDot(CCPoint stPos);
	CDot(CCPoint stPos, CCLayer* pThisScene);


};