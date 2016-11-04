LOCAL_PATH := $(call my-dir)

LAME_LIBMP3_DIR := libmp3lame

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
				   ../../Classes/NetworkManger.cpp \
				   ../../Classes/Tool.cpp \
				   ../../Classes/GameSocket.cpp \
				   ../../Classes/Global.cpp \
				   ../../Classes/NetworkPackage.cpp \
				   ../../Classes/TCPClient.cpp \
				   ../../Classes/TCPRequest.cpp \
				   ../../Classes/AudioManager.cpp \
				   ../../Classes/SiteManager.cpp \
				   ../../Classes/PorkerManager.cpp \
				   $(LAME_LIBMP3_DIR)/bitstream.c \
				   $(LAME_LIBMP3_DIR)/fft.c \
				   $(LAME_LIBMP3_DIR)/id3tag.c \
				   $(LAME_LIBMP3_DIR)/mpglib_interface.c \
				   $(LAME_LIBMP3_DIR)/presets.c \
				   $(LAME_LIBMP3_DIR)/quantize.c \
				   $(LAME_LIBMP3_DIR)/reservoir.c \
				   $(LAME_LIBMP3_DIR)/tables.c \
				   $(LAME_LIBMP3_DIR)/util.c \
				   $(LAME_LIBMP3_DIR)/VbrTag.c \
				   $(LAME_LIBMP3_DIR)/encoder.c \
				   $(LAME_LIBMP3_DIR)/gain_analysis.c \
				   $(LAME_LIBMP3_DIR)/lame.c \
				   $(LAME_LIBMP3_DIR)/newmdct.c \
				   $(LAME_LIBMP3_DIR)/psymodel.c \
				   $(LAME_LIBMP3_DIR)/quantize_pvt.c \
				   $(LAME_LIBMP3_DIR)/set_get.c \
				   $(LAME_LIBMP3_DIR)/takehiro.c \
				   $(LAME_LIBMP3_DIR)/vbrquantize.c \
				   $(LAME_LIBMP3_DIR)/version.c \
				   com_android_audio_SimpleLame.c

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
