#
# ----------------------------------------------------------------------
#     T-Kernel 2.0 Software Package
#
#     Copyright 2011 by Ken Sakamura.
#     This software is distributed under the latest version of T-License 2.x.
# ----------------------------------------------------------------------
#
#     Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
#     Modified by T-Engine Forum at 2011/09/08.
#     Modified by T-Engine Forum at 2012/11/07.
#     Modified by T-Engine Forum at 2013/03/01.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#

#	T-Monitor : tmmain (em1d)

MACHINE = em1d
TETYPE = tef

SRC_SYSDEP =

# ----------------------------------------------------------------------------

DEPS = Dependencies
DEPENDENCIES_OUTPUT := $(DEPS)

include $(BD)/etc/makerules

# install directory
TMONITOR_INSTALLDIR = $(BD)/monitor/bin/$(TETYPE)_$(MACHINE)

# h/w depend module path
HWDEPEND_PATH = $(BD)/monitor/hwdepend/$(TETYPE)_$(MACHINE)/build

# command/svc module path
CMDSVC_PATH = $(BD)/monitor/cmdsvc/build/$(TETYPE)_$(MACHINE)

# each driver module path
DRV_SIO_PATH = $(BD)/monitor/driver/sio/build/$(TETYPE)_$(MACHINE)
DRV_FLASH_PATH = $(BD)/monitor/driver/flash/build/$(TETYPE)_$(MACHINE)
DRV_MEMDISK_PATH = $(BD)/monitor/driver/memdisk/build/$(TETYPE)_$(MACHINE)

# header paths 
HEADER = $(BD)/include $(BD)/monitor/include

# ----------------------------------------------------------------------------

# version
VER := 2.01.00

# T-Monitor boot message
define VERSION
char const Version[] = "$(VER)";
char const * const Title[] = {
  "T-Monitor/$(TETYPE)_$(MACHINE) Version $(VER)",
  0,
  "@(#)$(shell LC_TIME=C date)"
};
endef

# ----------------------------------------------------------------------------

TARGET = tmonitor

S = ../../src

VPATH = $(S)
HEADER += $(S)

SRC = $(SRC_SYSDEP)

OBJ	= $(addsuffix .o, $(basename $(SRC)))

CFLAGS += $(CFLAGS_WARNING)

# ----------------------------------------------------------------------------

M_OBJ =	$(TMONITOR_INSTALLDIR)/hwdepend.o \
	$(TMONITOR_INSTALLDIR)/cmdsvc.o \
	$(TMONITOR_INSTALLDIR)/wrkbuf.o \
	$(TMONITOR_INSTALLDIR)/sio.o \
	$(TMONITOR_INSTALLDIR)/flash.o \
	$(TMONITOR_INSTALLDIR)/memdisk.o

LDLIBS = -lgcc

LDFLAGS += -static -nostdlib -T $(LINKSCRIPT)

ifneq ($(filter ram, $(options)), )
  # RAM version, for debug purpose
  LINKSCRIPT = monitor-ram.lnk
else
  LINKSCRIPT = monitor.lnk
endif

# ----------------------------------------------------------------------------

.PHONY: all clean install

ALL = $(TARGET).mot $(TARGET).map

all: hwdepend cmdsvc drivers $(ALL) install

$(TARGET).mot:	$(TARGET)
	$(OBJCOPY) -O srec --srec-forceS3 --srec-len 32 $< $@

$(TARGET): $(M_OBJ) $(OBJ) version.o
	$(CC) $(TARGET_ARCH) $(LDFLAGS) $^ $(LDLIBS) $(OUTPUT_OPTION)

version.c: Makefile $(OBJ) $(M_OBJ)
	echo "$$VERSION" > version.c

hwdepend:
	( cd $(HWDEPEND_PATH) ; $(MAKE) ; $(MAKE) install ; )

cmdsvc:
	( cd $(CMDSVC_PATH) ; $(MAKE) ; $(MAKE) install ; )

drivers:
	( cd $(DRV_SIO_PATH) ; $(MAKE) ; $(MAKE) install ; )
	( cd $(DRV_FLASH_PATH) ; $(MAKE) ; $(MAKE) install ; )
	( cd $(DRV_MEMDISK_PATH) ; $(MAKE) ; $(MAKE) install ; )

clean:
	( cd $(HWDEPEND_PATH) ; $(MAKE) clean )
	( cd $(CMDSVC_PATH) ; $(MAKE) clean )
	( cd $(DRV_SIO_PATH) ; $(MAKE) clean )
	( cd $(DRV_FLASH_PATH) ; $(MAKE) clean )
	( cd $(DRV_MEMDISK_PATH) ; $(MAKE) clean )
	$(RM) version.[co] $(OBJ) $(M_OBJ) $(TARGET) $(ALL) $(DEPS)

install: $(addprefix $(EXE_INSTALLDIR)/, $(ALL))

ifdef DEPENDENCIES_OUTPUT
  $(DEPS): ; touch $(DEPS)
else
  $(DEPS): $(SRC) ; $(MAKEDEPS) $@ $?
endif
-include $(DEPS)

$(SRC.C):
