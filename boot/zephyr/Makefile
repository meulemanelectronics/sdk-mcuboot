# Makefile
# -------------------------------
# Copyright 2022, (C) Sensorfy BV
#
SUBDIRS=

#
# The following Makefile variables can be set:
#
# BUILD_DIR		build directory
# BOARD			build for board definition
# BUILD_FLAG	Extra build flags
# SIGNING_KEY	The key used to sign 
#
BUILD_DIR?=build
BOARD?=nrf52840dk_nrf52840
BUILD_FLAG=-GNinja

# ----------------------------------------------------------------------------
# Makefile rules
#
all: bootloader

init-bootloader:
	cmake $(BUILD_FLAG) -B $(BUILD_DIR) -DBOARD=$(BOARD)

bootloader: init-bootloader
	ninja -C $(BUILD_DIR)

distclean: clean
	rm -fr $(BUILD_DIR)

clean:
	ninja -C $(BUILD_DIR) clean

.PHONY: $(SUBDIRS) init-bootloader bootloader clean distclean
