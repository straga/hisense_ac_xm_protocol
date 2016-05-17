#do not edit below if no necessary
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
	$(CC) $^ -o $@ $(SOFLAGS)   
else
	echo "Build static lib"
	$(AR) -cr $@ $^	
endif
	cp $@ $(ROOT)
clean:
	@-rm -f $(OBJS) *.so *.a
