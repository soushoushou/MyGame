LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/LoginScene.cpp \
				   ../../Classes/MainScene.cpp \
				   ../../Classes/PopupLayer.cpp \
				   ../../Classes/ShadeLayer.cpp \
				   ../../Classes/toolFunctions.cpp \
				   ../../Classes/UserProfileUI.cpp \
				   ../../Classes/DebugSimpleServer.cpp \
				   ../../Classes/GamePlayScene.cpp \
				   ../../Classes/NiuPlayer.cpp \
				   ../../Classes/NiuPoker.cpp \
				   ../../Classes/TimeLayer.cpp \
				   ../../Classes/ChatLayer.cpp \
				   ../../Classes/Help.cpp \
				   ../../Classes/PopupScene.cpp \
				   ../../Classes/SettingMenuInPlaying.cpp \
				   ../../Classes/ShopLayer.cpp \
				   ../../Classes/Tool.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
