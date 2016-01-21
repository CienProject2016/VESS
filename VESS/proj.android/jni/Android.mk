LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AnimationScene.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/BackgroundObject.cpp \
                   ../../../Classes/BackgroundSpawnScheduler.cpp \
                   ../../../Classes/BattleOperator.cpp \
                   ../../../Classes/DialogLayer.cpp \
                   ../../../Classes/EnterScene.cpp \
                   ../../../Classes/Event.cpp \
                   ../../../Classes/FightLayer.cpp \
                   ../../../Classes/GameData.cpp \
                   ../../../Classes/GameScene.cpp \
                   ../../../Classes/healthState.cpp \
                   ../../../Classes/Hero.cpp \
                   ../../../Classes/Ingredient.cpp \
                   ../../../Classes/Item.cpp \
		../../../Classes/monster.cpp \
                   ../../../Classes/MonsterSpawnScheduler.cpp \
		../../../Classes/Settings.cpp \
                   ../../../Classes/Stage.cpp \
    	         ../../../Classes/StageScene.cpp \
                   ../../../Classes/StartScene.cpp \
                   ../../../Classes/TestScene.cpp \
                   ../../../Classes/TextLayer.cpp \
                   ../../../Classes/Unit.cpp \
                   ../../../Classes/Upgradelayer.cpp 


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

