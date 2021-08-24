#pragma once

#define RadToDeg(x) (57.29577951f * x)
#define DegToRad(x) (0.017453293f * x)

#define D_SOUND_MAX 4

#define D_PHONE_WIDTH 480
#define D_PHONE_HEIGHT 800

#define D_SCREEN_SCALE_WIDTH(s) (D_PHONE_WIDTH/100) * s
#define D_SCREEN_SCALE_HEIGHT(s) (D_PHONE_HEIGHT/100) * s

#define D_MENU_TITLE_X 240
#define D_MENU_TITLE_Y 700

#define D_BLOCK_WIDTH 64.0f
#define D_BLOCK_HEIGHT 64.0f

#define D_BLOCK_MAX (D_BLOCKMAP_WIDTH * (D_BLOCKMAP_HEIGHT - 1))
#define D_BLOCKMAP_MAX (D_BLOCKMAP_WIDTH * (D_BLOCKMAP_HEIGHT))

#define D_BLOCK_SPEED 650.0f
#define D_BLOCK_PLUSSPEED 120.0f

#define	D_LINE_START_X 48.0f
#define	D_LINE_START_Y 760.0f
//!< DevOption 696.0f 734.0f
#define D_BLOCK_BOUNCE_FOWER 90.0f
#define D_BLOCK_BOUNCE_FOWER_LOW 35.5f
#define D_BLOCK_BOUNCE_HURISTIC 1.4f

#define D_POP_LOOP 0

#define D_BLOCKMAP_WIDTH 7
#define D_BLOCKMAP_HEIGHT 12

#define D_SOUNDMNG CocosDenshion::SimpleAudioEngine::sharedEngine()
//#define	D_LINE_START_X -192.0f
//#define	D_LINE_START_Y 340.0f

#define D_SCORE_POP 10
#define D_SCORE_POP_PLUS 10 //!< 5이상 터트리면 + 100 * 갯수
#define D_SCORE_POP_COMBO 0.2f //!< 콤보 추가 기본 배수
#define D_SCORE_POP_LIGHTNING 10 //!< 아이템 전기로 터트린 점수
#define D_SCORE_POP_BOMB 10 //!< 아이템 폭탄으로 터트린 점수
#define D_SCORE_LINE 40

#define D_CAM_Z_FIXED 695.0f

#define D_PHOTOSHOP_Y(value) (D_PHONE_HEIGHT - value)


//#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);

//#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);

//#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);

//#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);

//m_pLoading->setVisible(true); \
	


#define D_SCENE_CHANGE_EFFECT_UP(scene) CCScene *pScene = CCTransitionFadeUp::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);

#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionFadeDown::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);

#define D_SCENE_CHANGE_EFFECT_FADE(scene) CCScene *pScene = CCTransitionFade::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);



#define D_BASIC_PHONE_WIDTH 480
#define D_BASIC_PHONE_HEIGHT 800

#define D_SCALE_WIDTH (g_PhoneSize.width/D_BASIC_PHONE_WIDTH)
#define D_SCALE_HEIGHT (g_PhoneSize.height/D_BASIC_PHONE_HEIGHT)

#define D_POPTIME_MAX 1.0f


#define D_STAGEMENU_START_X - 150.0f
#define D_STAGEMENU_START_Y   300.0f

#define D_STAGEMENU_DISTANCE 150.0f
#define D_STAGEMENU_WIDTH_NUMBER 3

#define D_STAGEMENU_WIDTH 140
#define D_STAGEMENU_HEGIHT 140

#define D_STAGE_MAX 33

#define D_BUTTON_SOUND "StageStart.mp3"