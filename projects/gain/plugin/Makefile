# Copyright (c) 2026 MOD Audio Limited
# SPDX-License-Identifier: MIT
#
# DPF wrapper Makefile for the gain plugin.
#
# DPF (the DISTRHO Plugin Framework) is expected to be reachable from
# this directory at ./dpf/. For builds via builder.mod.audio, the
# Buildroot recipe symlinks /root/dpf into ./dpf at configure time.
# For local development, clone DPF yourself and symlink/copy it here.

NAME = gain
FILES_DSP = Plugin.cpp

include dpf/Makefile.plugins.mk

TARGETS = lv2_dsp

all: $(TARGETS)
