#
# Author Kevin He
#
#

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := devices

SRC_ROOT := $(LOCAL_PATH)/../src

ifeq ($(debug),1)
LOCAL_CFLAGS += -DDEBUG
endif

LOCAL_CFLAGS := -O3 -DANDROID -DPLAT_LINUX -fexceptions

LOCAL_C_INCLUDES := $(SRC_ROOT)/include $(SRC_ROOT)/devices/include
LOCAL_LDLIBS := -llog -pthread
#LOCAL_SHARED_LIBRARIES := liblog

#1 定义查找所有cpp文件的宏
define all-cpp-files-under
$(patsubst ./%,%, $(shell find $(SRC_ROOT) -name "*.cpp" -and -not -name ".*" -and -not -name "com_*"))
endef

define all-subdir-cpp-files
$(call all-cpp-files-under,.)
endef


#2 定义查找所有c文件的宏
define all-c-files-under
$(patsubst ./%,%, $(shell find $(SRC_ROOT) -name "*.c" -and -not -name ".*" -and -not -name "com_*"))
endef

define all-subdir-c-files
$(call all-c-files-under,.)
endef


ALL_SRC_FILES := $(call all-subdir-cpp-files)
LOCAL_SRC_FILES := $(patsubst %main.cpp,,$(ALL_SRC_FILES))

LOCAL_SRC_FILES += $(call all-subdir-c-files)

#$(warning LOCAL_SRC_FILES is $(LOCAL_SRC_FILES))

LOCAL_SDK_VERSION := 9

include $(BUILD_SHARED_LIBRARY)
