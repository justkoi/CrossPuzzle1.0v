LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/TeamLogoScene.cpp \
                   ../../Classes/PopList.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/Map.cpp \
                   ../../Classes/LogoScene.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/CNumber.cpp \
                   ../../Classes/CEffectManager.cpp \
                   ../../Classes/Block.cpp \
                   ../../Classes/CNumberManager.cpp \
                   ../../Classes/CComboManager.cpp \
                   ../../Classes/LevelMenuScene.cpp \
                   ../../Classes/StageMenuScene.cpp \
                   ../../Classes/CPlaneManager.cpp \
                   ../../Classes/Dot.cpp \
                   ../../Classes/CreditScene.cpp\
                   ../../Classes/CreditBlock.cpp\
                   ../../Classes/CMStyleButton.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)

