#
# ----------------------------------------------------------------------
#     T-Kernel 2.0 Software Package
#
#     Copyright 2011 by Ken Sakamura.
#     This software is distributed under the latest version of T-License 2.x.
# ----------------------------------------------------------------------
#
#     Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
#     Modified by T-Engine Forum at 2012/11/07.
#     Modified by T-Engine Forum at 2013/03/01.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#

#
#	Makefile
#		for GNU make
#
#	device driver : console/serial (em1d)

MACHINE = em1d
TETYPE = tef

SRC_SYSDEP = ns16450.c

# ----------------------------------------------------------------------------

DEPS = Dependencies
DEPENDENCIES_OUTPUT := $(DEPS)
DEPS_SRC = Dependencies_src

include $(BD)/etc/makerules

HEADER = $(BD)/include

# ----------------------------------------------------------------------------

TARGET = console

S = ../src

SRC = main.c consmlock.c console_drv.c line_drv.c
SRC += $(SRC_SYSDEP)

OBJ = $(addsuffix .o, $(basename $(SRC)))

CFLAGS += $(CFLAGS_WARNING)

# ----------------------------------------------------------------------------

TARGET_SVC = libconsolesvc.a

I	= $(S)/svc
IFSRC	= $(S)/svc
OBJ_SVC = $(addsuffix .o, $(basename $(SRC_SVC)))

IFLIB = device/serialio.h

# ----------------------------------------------------------------------------

VPATH = $(S) $(IFSRC)
HEADER += $(S)

# ----------------------------------------------------------------------------

.PHONY: all clean install source clean_source clean_install

ALL = $(TARGET).o $(TARGET_SVC)

all: $(ALL)

# ----------------------------------------------------------------------------

# generate source code dependencies and define SRC_SVC
#    (included here because $(SRC_SVC) is referred from $(OBJ) as prerequisites)
$(DEPS_SRC): $(addprefix $(BD)/include/, $(IFLIB))
	$(RM) $@
	for iflib_src in $(IFLIB) ; do \
	  $(BD)/etc/mkdrvsvc -deps $(MACHINE) $(BD)/include/$$iflib_src >> $@ ; \
	done
-include $(DEPS_SRC)

# ----------------------------------------------------------------------------

$(TARGET).o: $(SRC_SVC) $(OBJ)
	$(LINK_R.o) $(OBJ) $(OUTPUT_OPTION)

$(TARGET_SVC): $(OBJ_SVC)
	$(AR) $(ARFLAGS) $@ $?
  ifdef RANLIB
	$(RANLIB) $@
  endif

clean:
	$(RM) $(OBJ) $(OBJ_SVC) $(ALL) $(DEPS) $(DEPS_SRC)

source: $(SRC_SVC)

$(SRC_SVC): $(addprefix $(BD)/include/, $(IFLIB))
	( cd $(IFSRC) ; \
	for iflib_src in $(IFLIB) ; do \
	  $(BD)/etc/mkdrvsvc $(MACHINE) $(BD)/include/$$iflib_src ; \
	done );

clean_source:
	( cd $(I) ; $(RM) *.h )
	( cd $(IFSRC) ; $(RM) *.S )

clean_install:
	$(RM) $(addprefix $(DRIVER_INSTALLDIR)/, $(TARGET).o)
	$(RM) $(addprefix $(LIB_INSTALLDIR)/, $(TARGET_SVC))

install: $(addprefix $(DRIVER_INSTALLDIR)/, $(TARGET).o) $(addprefix $(LIB_INSTALLDIR)/, $(TARGET_SVC))

# ----------------------------------------------------------------------------

ifdef DEPENDENCIES_OUTPUT
  $(DEPS): ; touch $(DEPS)
else
  $(DEPS): $(SRC) ; $(MAKEDEPS) $@ $?
endif
-include $(DEPS)
