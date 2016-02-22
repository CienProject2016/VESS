LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../../Classes/ActionFrameValue.cpp \
                   ../../../Classes/AnimationScene.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/BackgroundObject.cpp \
                   ../../../Classes/BackgroundSpawnScheduler.cpp \
                   ../../../Classes/BattleOperator.cpp \
				   ../../../Classes/Chest.cpp \
				   ../../../Classes/DefenseMovementState.cpp \
				   ../../../Classes/Dialog.cpp \
                   ../../../Classes/DialogScene.cpp \
				   ../../../Classes/DimensionGateController.cpp \
				   ../../../Classes/DurabilityController.cpp \
                   ../../../Classes/EnterScene.cpp \
                   ../../../Classes/FightLayer.cpp \
                   ../../../Classes/GameData.cpp \
				   ../../../Classes/GameoverPopupLayer.cpp \
                   ../../../Classes/GameScene.cpp \
				   ../../../Classes/GaugeLockChecker.cpp \
                   ../../../Classes/Hero.cpp \
				   ../../../Classes/HeroMovementState.cpp \
                   ../../../Classes/Item.cpp \
		../../../Classes/monster.cpp \
		../../../Classes/MiniPopupLayer.cpp \
		../../../Classes/MonsterAnimation.cpp \
					../../../Classes/MonsterAttackScheduler.cpp \
					../../../Classes/MonsterBehaviorPattern.cpp \
					../../../Classes/MonsterInfo.cpp \
                   ../../../Classes/MonsterSpawnScheduler.cpp \
				   ../../../Classes/ResourcePath.cpp \
				   ../../../Classes/SaveController.cpp \
				   ../../../Classes/Shield.cpp \
					../../../Classes/Settings.cpp \
                   ../../../Classes/Stage.cpp \
				   ../../../Classes/StageClearLayer.cpp \
				   ../../../Classes/StageLevelController.cpp \
				 ../../../Classes/StartScene.cpp \
				 ../../../Classes/Sword.cpp \
				   ../../../Classes/Tutorial.cpp \
				   ../../../Classes/TutorialController.cpp \
				   ../../../Classes/TutorialInfo.cpp \
				   ../../../Classes/TutorialLayer.cpp \
                   ../../../Classes/Unit.cpp \
				   ../../../Classes/UpgradeCompleteLayer.cpp \
				   ../../../Classes/UpgradeController.cpp \
				   ../../../Classes/UpgradeLayer.cpp 


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
