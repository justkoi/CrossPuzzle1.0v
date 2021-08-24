#pragma once

#include "stdafx.h"

using namespace std;
USING_NS_CC;

class CPopList
{
public:

	vector<CBlock*> m_BlockList; //!< ��Ʈ�� ��� ����
	CBlock* m_FocusBlock; //!< ��Ŀ�̵� ���

public:

	void Init(int nIndex);
	
	
	void SelectBlock(stVec2i stBlockIndex);
	void CheckAround(); //!< �����¿� ����� üũ�Ͽ� ���� //!< �̹� ���Ե� ����� ���Խ�Ű�� �ʴ´�

	CBlock* getNextFocusBlock(); //!< ���� ���� ��Ŀ�� �� ��� ��ȯ

};