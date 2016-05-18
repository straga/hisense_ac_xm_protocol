#do not edit below if no necessary
MAPFILE := ../proj.map
MAP_OPT := -Wl,-Map=$(MAPFILE)
include $(ROOT)/rules.mk
#LIBNAME = $(LIBFIX)$(TARGET).$(LIBEXT)
ifeq ($(OS), darwin)
  CC = libtool
endif
OBJS :=$(wildcard *.o)

$(LIBNAME): $(OBJS)
#ifeq ($(words $(findstring -fPIC, $(PICFLAGS))), 1)

ifneq ($(static),1)
	echo "Build shared lib"
	$(CC) $^ -o $@ $(SOFLAGS) $(MAP_OPT)   
else
	echo "Build static lib"
	$(AR) -cr $@ $^	
endif
	cp $@ $(ROOT)
clean:
	@-rm -f $(OBJS) *.so *.a ../*.so ../*.a $(MAPFILE)
