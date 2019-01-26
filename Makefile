#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := memtest

ESP_IDF_VERSION := esp-idf

IDF_PATH := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))/$(ESP_IDF_VERSION)
include $(IDF_PATH)/make/project.mk
