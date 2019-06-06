#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := memtest

ESP_IDF_VERSION := esp-idf

CFLAGS+=-mfix-esp32-psram-cache-dupldst
CXXFLAGS+=-mfix-esp32-psram-cache-dupldst

include $(IDF_PATH)/make/project.mk
