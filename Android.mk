LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
 
LOCAL_SRC_FILES:=\
	hw_watchdog.c

LOCAL_SHARED_LIBRARIES := liblog
LOCAL_CFLAGS:=-O2 -g
#LOCAL_CFLAGS+=-DLINUX
 

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
 
LOCAL_MODULE:=hw_watchdog
 
# gold in binutils 2.22 will warn about the usage of mktemp
LOCAL_LDFLAGS += -Wl,--no-fatal-warnings
 
include $(BUILD_EXECUTABLE)
