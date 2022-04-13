#
# ----------------------------------------------------------------------
#     T-Kernel 2.0 Software Package
#
#     Copyright 2011 by Ken Sakamura.
#     This software is distributed under the latest version of T-License 2.x.
# ----------------------------------------------------------------------
#
#     Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#

#
#	Makefile for gmake
#	make all drivers for tef_emid
#

DRV_TARGET = clk console kbpd lowkbpd screen sysdsk
DRV_SRC_TARGET = clk console

# ----------------------------------------------------------------------------
.PHONY: all clean source clean_source clean_all

all: $(DRV_TARGET)

$(DRV_TARGET):
	cd ../$@/build ; \
	$(MAKE) ; \
	$(MAKE) install

clean:
	@( cd ../ ; \
	for dir in $(DRV_TARGET); do \
		( cd $$dir/build ; $(MAKE) clean clean_install ) ; \
	done ) ;

source:
	@( cd ../ ; \
	for dir in $(DRV_SRC_TARGET); do \
		( cd $$dir/build ; $(MAKE) source ) ; \
	done ) ;

clean_source:
	@( cd ../ ; \
	for dir in $(DRV_SRC_TARGET); do \
		( cd $$dir/build ; $(MAKE) clean_source ) ; \
	done ) ;

clean_all: clean clean_source
