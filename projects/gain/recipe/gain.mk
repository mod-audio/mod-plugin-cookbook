# Copyright (c) 2026 MOD Audio Limited
# SPDX-License-Identifier: MIT
#
# Buildroot recipe for the project-mode gain example.
#
# This recipe points at the cookbook repository itself as its source —
# the gain project lives at projects/gain/ inside the cookbook. When
# uploaded to builder.mod.audio/buildroot, the builder clones the
# cookbook, builds the plugin against DPF, and assembles the .lv2
# bundle using the hand-written .ttl files from projects/gain/lv2/.
#
# For your own plugin, change GAIN_SITE to point at your repository
# (any reachable git URL — github.com, gitlab.com, codeberg.org, your
# own server). For reproducibility, pin GAIN_VERSION to a specific
# commit SHA rather than a branch name; the example uses `main` so
# the demo always tracks the latest cookbook.

GAIN_VERSION = main
GAIN_SITE = https://github.com/mod-audio/mod-plugin-cookbook.git
GAIN_SITE_METHOD = git
GAIN_BUNDLES = gain.lv2

define GAIN_CONFIGURE_CMDS
	# DPF is pre-cloned at /root/dpf inside the builder image; symlink
	# it where the plugin Makefile expects to find it.
	ln -s /root/dpf $(@D)/projects/gain/plugin/dpf
endef

define GAIN_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(TARGET_CONFIGURE_OPTS) $(MAKE) NOOPT=true -C $(@D)/projects/gain/plugin lv2_dsp
endef

define GAIN_INSTALL_TARGET_CMDS
	mkdir -p $($(PKG)_PKGDIR)/gain.lv2
	cp $(@D)/projects/gain/plugin/bin/gain.lv2/gain_dsp.so $($(PKG)_PKGDIR)/gain.lv2/
	cp $(@D)/projects/gain/lv2/manifest.ttl                $($(PKG)_PKGDIR)/gain.lv2/
	cp $(@D)/projects/gain/lv2/plugin.ttl                  $($(PKG)_PKGDIR)/gain.lv2/gain.ttl
endef

$(eval $(generic-package))
