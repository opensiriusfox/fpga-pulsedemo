############################################################
# Use sane defaults
# "Your Makefiles are wrong" by Jacob Davis Hansonn
# https://tech.davis-hansson.com/p/make/
############################################################
SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
#MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >
############################################################

TARGET=pulsedemo
.PHONY: $(TARGET)
RTLSRC=../rtl
all: $(TARGET)

CFLAGS=-g -O2
CXXFLAGS=$(CFLAGS)

$(TARGET):
> verilator -Wno-fatal -I$(RTLSRC) --cc $(@)_top.v --trace --exe ../$(@).cpp \
>	-Mdir $(@) -CFLAGS "$(CFLAGS)"
> make -C $(@) -f V$(@)_top.mk

.PHONY: view run
run::
> $(TARGET)/V$(TARGET)_top
view::
> gtkwave gtkWave.sav &>/dev/null &

clean::
> rm -r *.o $(TARGET)
distclean:: clean
> rm -r *~