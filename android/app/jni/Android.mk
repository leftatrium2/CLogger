LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := app
LOCAL_SRC_FILES := \
	my_jni.c \
	my_jni_util.c

LOCAL_C_INCLUDES += \
	../../../lib/include/
	
LOCAL_CFLAGS += -std=c99
LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)