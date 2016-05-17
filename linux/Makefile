# Author: Kevin He
# Time:		16th May,2015	
# The Top make file to build
# 

CODEEXT := cpp
TARGET ?= device
ROOT := $(shell pwd)
SRC_ROOT := $(ROOT)/../src
OBJDIR := $(ROOT)/obj

include $(ROOT)/rules.mk
# rules 

BINNAME = main
MAIN_OBJS = main.o
MAIN_SRC = $(MAIN_OBJS:%.o=%.c)

SUBDIRS =$(shell ls -l $(SRC_ROOT) | grep ^d | awk '{if($$9 != "obj") print $$9}')
SUBDIRS := $(addprefix $(SRC_ROOT)/,$(SUBDIRS))
# $(warning "SUBDIRS is $(SUBDIRS)")
MAINLDFLAGS = -L$(OBJDIR) -l$(TARGET)

all : SUBOBJ $(BINNAME) 
.PHONY : all clean $(BINNAME)

SUBOBJ :
	$(AT)echo ""
	$(AT)echo "OS is $(OS) , CPU is $(CPU),MODEL is $(MODEL)"
	$(AT)echo "LIBNAME is $(LIBNAME)"
	$(AT)echo "CC is $(CC)"
	$(AT)$(MAKE) $(SILENT) -C $(OBJDIR) clean 
	$(AT)$(MAKE) $(SILENT) -C $(SRC_ROOT) 
	$(AT)$(MAKE) $(SILENT) -C $(OBJDIR) 

$(BINNAME) :
ifeq ($(MAIN_SRC),$(wildcard $(MAIN_SRC)))	
	$(AT)echo "[cc] $(MAIN_SRC)"	
	$(AT)$(CCACHE) $(CC)  $(MAIN_SRC) -o $@ $(MAINLDFLAGS) $(CFLAGS) $(LDFLAGS)	
endif
	$(AT)echo "Build SUCCESS" 
	
# the shell variable 'n' should use $$ to quote and do not add () 
clean:
#	$(AT)for n in $(SUBDIRS); do $(MAKE)  $(SILENT) -C $$n clean; done
	$(AT)$(MAKE) $(SILENT) -C $(OBJDIR) clean	
#	@-rm -rf $(BINNAME) *.so *.a ../obj ../libs log	
