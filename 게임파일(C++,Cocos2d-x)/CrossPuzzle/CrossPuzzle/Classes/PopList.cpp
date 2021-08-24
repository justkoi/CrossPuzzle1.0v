#pragma once

#include "stdafx.h"
USING_NS_CC;

unsigned int g_nPopListNumber = 0;

void CPopList::Init(int nIndex)
{
	if(g_BlockList[nIndex].m_bLive == false)
	{
		// printf("���º���������� return\n");
		return;
	}

	m_FocusBlock = NULL;
	
	g_BlockList[nIndex].m_bChecked = true; //!< üũ�ϰ�
	m_BlockList.push_back(&g_BlockList[nIndex]); //!< ��Ŀ�̸���Ʈ�� �������

	// printf("[%d]List / (%d, %d) ���� ���Ե�",g_nPopListNumber,g_BlockList[nIndex].m_stIndex.m_nX,g_BlockList[nIndex].m_stIndex.m_nY);

	while(1) //!< �� ���� �߽����� ��� ������ ����
	{
		m_FocusBlock = getNextFocusBlock(); //!< ����Ʈ�� �տ������� ��Ŀ�̾ȵȳ��� �������

		if(m_FocusBlock == NULL) //!< �� �̻� ���ٸ� Break
			break;

		CheckAround(); //!< �����¿츦 �ѷ����� ����
	}


	//!< ����
	g_nPopListNumber++;
}
void CPopList::CheckAround() //!< ��Ŀ�� �� ������ ���� �����¿� ����� üũ�Ͽ� ���� //!< �̹� ���Ե� ����� ���Խ�Ű�� �ʴ´�
	//!< ���� Ȯ���ߴµ� ������ ���� ��Ŀ������ �Ѿ ������Ŀ���� ���ٸ� ���� Ȯ���� ����
{
	stVec2i stBlockIndex;
	stBlockIndex = m_FocusBlock->m_stIndex;

	SelectBlock(stVec2i(stBlockIndex.m_nX -1, stBlockIndex.m_nY));
	SelectBlock(stVec2i(stBlockIndex.m_nX +1, stBlockIndex.m_nY));
	SelectBlock(stVec2i(stBlockIndex.m_nX, stBlockIndex.m_nY -1));
	SelectBlock(stVec2i(stBlockIndex.m_nX, stBlockIndex.m_nY +1));

}
CBlock* CPopList::getNextFocusBlock() //!< ���� ���� ��Ŀ�� �� ��� ��ȯ
{
	for(int i=0; i<m_BlockList.size(); i++)
	{
		if( m_BlockList[i]->m_bFocused == false )
		{
			m_BlockList[i]->m_bFocused = true; //!< ��Ŀ��üũ
			return m_BlockList[i];
			break;
		}
	}
	return NULL;
}

void CPopList::SelectBlock(stVec2i stBlockIndex) //!< �ش� ����� ã�Ƽ� ����
{
	//!< �� ������ ����� return

	if(stBlockIndex.m_nX < 0) 
		return;
	if(stBlockIndex.m_nX >= D_BLOCKMAP_WIDTH)
		return;
	if(stBlockIndex.m_nY < 2)
		return;
	if(stBlockIndex.m_nY >= D_BLOCKMAP_HEIGHT)
		return;

	for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		//!< ������ ��ġ�� ����� ����
		if( g_BlockList[nBlock].m_stIndex == stBlockIndex && g_BlockList[nBlock].m_eBlockNumber == m_FocusBlock->m_eBlockNumber )
		{
			if( g_BlockList[nBlock].m_bChecked == true) //!< �̹� ���ԉ�ٸ� Ż��
				break;

			if( g_BlockList[nBlock].m_bLive == false) //!< �׾������� Ż��
				break;

			if( g_BlockList[nBlock].m_stIndex.m_nY < 2) //!< �� �����̸� Ż��
				break;

			g_BlockList[nBlock].m_bChecked = true; //!< ���Ե� üũ
			m_BlockList.push_back(&g_BlockList[nBlock]); //!< ��Ŀ�̸���Ʈ�� �������
			// printf("[%d]List / (%d, %d) ���Ե�",g_nPopListNumber,stBlockIndex.m_nX,stBlockIndex.m_nY);
			break;
		}
	}
}