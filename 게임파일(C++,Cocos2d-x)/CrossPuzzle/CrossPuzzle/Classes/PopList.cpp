#pragma once

#include "stdafx.h"
USING_NS_CC;

unsigned int g_nPopListNumber = 0;

void CPopList::Init(int nIndex)
{
	if(g_BlockList[nIndex].m_bLive == false)
	{
		// printf("없는블록최초포함 return\n");
		return;
	}

	m_FocusBlock = NULL;
	
	g_BlockList[nIndex].m_bChecked = true; //!< 체크하고
	m_BlockList.push_back(&g_BlockList[nIndex]); //!< 포커싱리스트에 집어넣음

	// printf("[%d]List / (%d, %d) 최초 포함됨",g_nPopListNumber,g_BlockList[nIndex].m_stIndex.m_nX,g_BlockList[nIndex].m_stIndex.m_nY);

	while(1) //!< 그 놈을 중심으로 모든 가닥을 연결
	{
		m_FocusBlock = getNextFocusBlock(); //!< 리스트의 앞에서부터 포커싱안된놈을 끄집어옴

		if(m_FocusBlock == NULL) //!< 더 이상 없다면 Break
			break;

		CheckAround(); //!< 상하좌우를 둘러보고 포함
	}


	//!< 종료
	g_nPopListNumber++;
}
void CPopList::CheckAround() //!< 포커싱 된 놈으로 부터 상하좌우 블록을 체크하여 포함 //!< 이미 포함된 블록은 포함시키지 않는다
	//!< 전부 확인했는데 없으면 다음 포커싱으로 넘어감 다음포커싱이 없다면 개수 확인후 종료
{
	stVec2i stBlockIndex;
	stBlockIndex = m_FocusBlock->m_stIndex;

	SelectBlock(stVec2i(stBlockIndex.m_nX -1, stBlockIndex.m_nY));
	SelectBlock(stVec2i(stBlockIndex.m_nX +1, stBlockIndex.m_nY));
	SelectBlock(stVec2i(stBlockIndex.m_nX, stBlockIndex.m_nY -1));
	SelectBlock(stVec2i(stBlockIndex.m_nX, stBlockIndex.m_nY +1));

}
CBlock* CPopList::getNextFocusBlock() //!< 가장 다음 포커싱 될 블록 반환
{
	for(int i=0; i<m_BlockList.size(); i++)
	{
		if( m_BlockList[i]->m_bFocused == false )
		{
			m_BlockList[i]->m_bFocused = true; //!< 포커싱체크
			return m_BlockList[i];
			break;
		}
	}
	return NULL;
}

void CPopList::SelectBlock(stVec2i stBlockIndex) //!< 해당 블록을 찾아서 포함
{
	//!< 맵 범위를 벗어나면 return

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
		//!< 지정된 위치와 모양이 같고
		if( g_BlockList[nBlock].m_stIndex == stBlockIndex && g_BlockList[nBlock].m_eBlockNumber == m_FocusBlock->m_eBlockNumber )
		{
			if( g_BlockList[nBlock].m_bChecked == true) //!< 이미 포함됬다면 탈락
				break;

			if( g_BlockList[nBlock].m_bLive == false) //!< 죽어있으면 탈락
				break;

			if( g_BlockList[nBlock].m_stIndex.m_nY < 2) //!< 맨 윗줄이면 탈락
				break;

			g_BlockList[nBlock].m_bChecked = true; //!< 포함됨 체크
			m_BlockList.push_back(&g_BlockList[nBlock]); //!< 포커싱리스트에 집어넣음
			// printf("[%d]List / (%d, %d) 포함됨",g_nPopListNumber,stBlockIndex.m_nX,stBlockIndex.m_nY);
			break;
		}
	}
}