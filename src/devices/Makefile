#########################################################
# Author TaoHe																					#
# Created On: 29th Feb,2016															#
# Description : Sub Makefile.														#
# Not Support make here directly												#
#########################################################

#do not edit below if no necessary

include $(ROOT)/rules.mk

SUBDIRS := $(shell ls -l | grep ^d | awk '{if($$9 != "obj") print $$9}')
# except include directory
SUBDIRS := $(subst include,,$(SUBDIRS))
#ifneq ($(OS), linux)
SUBDIRS := $(subst javaInterface,,$(SUBDIRS))
#endif

#$(warning SUBDIRS is $(SUBDIRS) OS is $(OS))
export OBJDIR
ifeq ($(MAKELEVEL),0)
all : MSG
else
all : TODO
endif
.PHONY : all clean

TODO:
	@for n in $(SUBDIRS); do $(MAKE) $(SILENT) -C $$n || exit $$?;	done 
clean:
	@for n in $(SUBDIRS); do $(MAKE)  $(SILENT) -C $$n clean; done
MSG:
	@echo "You should execute "make" at the Project Top Dir" 