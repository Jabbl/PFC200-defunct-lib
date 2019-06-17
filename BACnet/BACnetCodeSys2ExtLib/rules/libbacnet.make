# -*-makefile-*-
#
# Copyright (C) 2013 by <cm>
#
# See CREDITS for details about who has contributed to this project.
#
# For further information about the PTXdist project and license conditions
# see the README file.
#

#
# We provide this package
#
PACKAGES-$(PTXCONF_LIBBACNET) += libbacnet

#
# Paths and names
#
LIBBACNET_VERSION	:= 0.9
LIBBACNET		:= libbacnet
#LIBBACNET_URL		:= file://src/$(LIBBACNET)
LIBBACNET_URL		:= file://src/BACnet/BACnetCodeSys2ExtLib/bin
LIBBACNET_DIR		:= $(BUILDDIR)/$(LIBBACNET)
LIBBACNET_WWW_DIR	:= src/BACnet/BACnetWBM/www
LIBBACNET_WWW_SD20_DIR := src/BACnet/SD20
LIBBACNET_SCRIPTS	:= src/BACnet/BACnetCodeSys2ExtLib/scripts
LIBBACNET_TARGETIPK := platform-wago-pfcXXX/packages/libbacnet_0.9_armhf.ipk
LIBBACNET_COPY_TO_DIR := src/BACnet/BACnetCodeSys2ExtLib/bin/BACnet-dev-newest.ipk
LIBBACNET_LICENSE	:= unknown

# ----------------------------------------------------------------------------
# Extract
# ----------------------------------------------------------------------------

#$(STATEDIR)/libbacnet.extract:
#	@$(call targetinfo)
#	@$(call clean, $(LIBBACNET_DIR))
#	@$(call extract, LIBBACNET)
#	@$(call patchin, LIBBACNET)
#	@$(call touch)

# ----------------------------------------------------------------------------
# Prepare
# ----------------------------------------------------------------------------

#LIBBACNET_PATH	:= PATH=$(CROSS_PATH)
LIBBACNET_CONF_TOOL	:= NO
LIBBACNET_MAKE_ENV	:= $(CROSS_ENV)

#$(STATEDIR)/libbacnet.prepare:
#	@$(call targetinfo)
#	@$(call world/prepare, LIBBACNET)
#	@$(call touch)

# ----------------------------------------------------------------------------
# Compile
# ----------------------------------------------------------------------------

#$(STATEDIR)/libbacnet.compile:
#	@$(call targetinfo)
#	@$(call world/compile, LIBBACNET)
#	@$(call touch)

# ----------------------------------------------------------------------------
# Install
# ----------------------------------------------------------------------------

#$(STATEDIR)/libbacnet.install:
#	@$(call targetinfo)
#	@$(call world/install, LIBBACNET)
#	@$(call touch)

# ----------------------------------------------------------------------------
# Target-Install
# ----------------------------------------------------------------------------

$(STATEDIR)/libbacnet.targetinstall:
	@$(call targetinfo)

	@$(call install_init, libbacnet)
	@$(call install_fixup, libbacnet,PRIORITY,optional)
	@$(call install_fixup, libbacnet,SECTION,base)
	@$(call install_fixup, libbacnet,AUTHOR,"<cm>")
	@$(call install_fixup, libbacnet,DESCRIPTION,missing)

#
# Note: Add everything *BEFORE* call to macro install_finish
#
	# The library itself
	@$(call install_copy, libbacnet, 0, 0, 0755, $(LIBBACNET_DIR)/libbacnet.so, /usr/lib/wide/libbacnet.so)

	@$(call install_finish, libbacnet)

	# Copy .ipk file to output path on Windows
	cp $(LIBBACNET_TARGETIPK) $(LIBBACNET_COPY_TO_DIR)

	@$(call touch)

# ----------------------------------------------------------------------------
# Clean
# ----------------------------------------------------------------------------

$(STATEDIR)/libbacnet.clean:
	@$(call targetinfo)
	@-cd $(LIBBACNET_DIR) && \
		$(LIBBACNET_ENV) $(LIBBACNET_PATH) $(MAKE) clean
	@$(call clean_pkg, LIBBACNET)
	rm -f $(LIBBACNET_COPY_TO_DIR)

# vim: syntax=make
