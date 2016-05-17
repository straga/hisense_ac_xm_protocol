#########################################################
# Author TaoHe																					#
# Created On: 29th Feb,2016															#
# Description : Sub Makefile.														#
# Not Support make here directly												#
#########################################################

#do not edit below if no necessary

include $(ROOT)/rules.mk


OBJS := $(patsubst %.$(CODEEXT),%.o,$(wildcard *.$(CODEEXT)))

ifeq ($(MAKELEVEL),0)
all : MSG
else
all : $(OBJS)
endif
.PHONY : all clean

$(OBJS):%o:%$(CODEEXT)
	$(AT)echo "[CC] $<"
	$(AT)$(CC) -c $< -o $(OBJDIR)/"$@" $(BUILDFLAG) $(LIBFLAG)

clean:
	$(AT)rm -rf $(OBJS)
MSG:
	@echo "You should execute "make" at the Project Top Dir" 