#include "stdafx.h" 

void CNumberManager::Init(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;
}
void CNumberManager::Update(float dt)
{
	if(m_pNumberList.size() >= 1)
	{
		vector<stNumberChunk*>::iterator it;
		for(it = m_pNumberList.begin(); it != m_pNumberList.end();)
		{
			(*it)->m_fTimer += dt;
			if((*it)->m_fTimer >= 1.0f)
			{
				(*it)->m_Number->Exit();
				delete (*it)->m_Number;
				delete (*it);
				it = m_pNumberList.erase(it);
			}
			else
			{
				 (*it)->m_Number->Update(dt);
				 (*it)->m_Number->SetPositionY(((*it)->m_fStartY + ((*it)->m_fTimer * 50.0f)) * D_SCALE_HEIGHT);
				 (*it)->m_Number->SetOpacity( (1.0f - (*it)->m_fTimer) );
				it++;
			}
		}
	}
}
void CNumberManager::Insert(int nNumber, float fX, float fY, ccColor3B ccColor, float fSizeW , float fSizeH)
{
	stNumberChunk* m_pNumberChunk = new stNumberChunk();
	m_pNumberChunk->m_Number = new CNumber();
	m_pNumberChunk->m_Number->Init(m_pThisScene,ccp(fSizeW * D_SCALE_WIDTH,fSizeH * D_SCALE_HEIGHT),nNumber,ccp(fX * D_SCALE_WIDTH,fY * D_SCALE_HEIGHT),26);
	m_pNumberChunk->m_Number->SetColor(ccColor);
	m_pNumberChunk->m_fTimer = 0.0f;
	m_pNumberChunk->m_fStartY = fY;
	m_pNumberList.push_back(m_pNumberChunk);
}

void CNumberManager::Exit()
{
	if(m_pNumberList.size() >= 1)
	{
		vector<stNumberChunk*>::iterator it;
		for(it = m_pNumberList.begin(); it != m_pNumberList.end();)
		{
			(*it)->m_Number->Exit();
			delete (*it)->m_Number;
			delete (*it);
			it = m_pNumberList.erase(it);
		}
	}
}