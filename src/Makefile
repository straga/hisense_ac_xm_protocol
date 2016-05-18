#
#
#

# before export ,add include path 
IFLAGS += -I include -I devices/include

include $(ROOT)/rules.mk

SUBDIRS := devices protocol
#SUBDIRS += 
OBJS := $(patsubst %.$(CODEEXT),%.o,$(wildcard *.$(CODEEXT)))

ifeq ($(MAKELEVEL),0)
all : MSG
else
all : $(OBJS) SUBDIRS
endif
.PHONY : all clean SUBDIRS

#$(warning dir(src) CC is $(CC),COMPILE_FLAG is $(COMPILE_FLAG))
$(OBJS):%o:%$(CODEEXT)
	$(AT)echo "[CC] $<"
	$(AT)$(CC) -c $< -o $(OBJDIR)/$@ $(COMPILE_FLAG)
	
SUBDIRS:
	$(AT)for n in $(SUBDIRS); do $(MAKE) $(SILENT) -C $$n || exit $$?;	done 

clean:
	$(AT)rm -f $(OBJS)
MSG:
	$(AT)echo "You should execute "make" at the Project Top Dir" l