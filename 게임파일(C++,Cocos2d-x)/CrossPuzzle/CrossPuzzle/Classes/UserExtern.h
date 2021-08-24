#pragma once
//extern int g_nScore;
//extern int g_nSelectStage;
//extern stStageInfo g_StageInfo[D_STAGE_MAX];
//extern bool	g_bStageLock[D_STAGE_MAX];
//extern int g_nScoreLevel[D_STAGE_MAX];//판정레벨 0, 1, 2, 3 Save
//extern int g_nJudgment[D_STAGE_MAX][3];//각각의 판정점 ReadOnly
//
extern bool g_bBGM_Sound;
extern bool g_bEFFECT_Sound;
//
extern bool g_bPause;
extern CCSize g_PhoneSize;

extern CMap	g_Map; //!< 맵 0과 1로 체크 동적할당
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
extern float g_fFevergauge; //!< 피버게이지 100이 최대 콤보마다 10씩 차오름 우선
extern bool	g_bFever; //!< 피버 모드 true false
extern unsigned int g_unMenu_BGM;
extern bool g_bFirstPlayed;

extern float g_fBGM_Volume;
extern float g_fEFFECT_Volume;

extern int g_nIndex;