#pragma once
//extern int g_nScore;
//extern int g_nSelectStage;
//extern stStageInfo g_StageInfo[D_STAGE_MAX];
//extern bool	g_bStageLock[D_STAGE_MAX];
//extern int g_nScoreLevel[D_STAGE_MAX];//�������� 0, 1, 2, 3 Save
//extern int g_nJudgment[D_STAGE_MAX][3];//������ ������ ReadOnly
//
extern bool g_bBGM_Sound;
extern bool g_bEFFECT_Sound;
//
extern bool g_bPause;
extern CCSize g_PhoneSize;

extern CMap	g_Map; //!< �� 0�� 1�� üũ �����Ҵ�
extern CBlock g_BlockList[D_BLOCKMAP_MAX];
extern int g_nBlockMax;//
extern int g_nScore;
extern int g_nCombo;
extern int g_nStage;
extern int g_nLevel;
extern CEffectManager g_EffectManager;
extern CEffectManager g_LineManager;
extern CPlaneManager g_PlaneManager;
extern CNumberManager g_NumberManager;
extern CComboManager g_ComboManager;
extern stStageInfo g_StageInfo[3][D_STAGE_MAX];
extern bool g_bStageLock[D_STAGE_MAX];
extern float g_fFevergauge; //!< �ǹ������� 100�� �ִ� �޺����� 10�� ������ �켱
extern bool	g_bFever; //!< �ǹ� ��� true false
extern unsigned int g_unMenu_BGM;
extern bool g_bFirstPlayed;

extern float g_fBGM_Volume;
extern float g_fEFFECT_Volume;

extern int g_nIndex;