#############################################################
# File:rules.mk
# This file defines the compile envirnment and it`s rules
# Author Kevin He
# Created on 17th May,2016
#############################################################

# Note: before include this file ,some variables shoud have be defined. 
# this variables are: CODEEXT,TARGET(the lib name),ROOT,SRC_ROOT,OBJDIR
#

export CODEEXT TARGET ROOT SRC_ROOT OBJDIR

#default use debug compile,user can change it`s value to 0
debug ?= 1

AR := ar
RM := rm
CP := cp
ECHO := echo

#for makefile debug
SILENT := -s
AT := @

export SILENT AT

ifeq ($(CODEEXT),cpp)
	CC := g++
else
	CC := gcc
endif
export CC

LIBFIX := lib
LIBEXT :=
ifeq ($(static),1)
	LIBEXT := a
else
	SOFLAGS += -shared
	LIBEXT := so
endif

export LIBNAME = $(LIBFIX)$(TARGET).$(LIBEXT)


OS := $(strip $(shell uname -s | tr '[:upper:]' '[:lower:]'))
CPU = $(shell uname -m | sed -e 's/i[345678]86/i386/')
PLATFORM = $(CPU)-$(OS)
export OS CPU PLATFORM

#define FLAGS below.
PICFLAGS = -fPIC
SOFLAGS += -Wl,-O1 
WFLAGS += -W -Wall -Wno-unused -Wno-parentheses -fno-omit-frame-pointer -fno-strict-aliasing 
LD_FLAG += -lm
IFLAGS +=  
DEBUG_FLAG += 

ifeq ($(debug),1)
DEBUG_FLAG += -DDEBUG
endif

ifeq ($(OS), linux)
  ifeq ($(JAVA_HOME),)
 $(error "Can not find env JAVA_HOME")
  else
	INC := $(JAVA_HOME)/include
	IFLAGS += -I$(INC) -I$(INC)/linux
  endif
endif

#so before include this file,user can change this variable for different use.
export COMPILE_FLAG = $(DEBUG_FLAG) $(PICFLAGS) $(SOFLAGS) $(WFLAGS) $(LD_FLAG) $(IFLAGS)

