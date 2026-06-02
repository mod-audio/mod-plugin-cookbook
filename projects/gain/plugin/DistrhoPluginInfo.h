// Copyright (c) 2026 MOD Audio Limited
// SPDX-License-Identifier: MIT

#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_BRAND       "MOD"
#define DISTRHO_PLUGIN_NAME        "Gain"
#define DISTRHO_PLUGIN_URI         "urn:mod-cookbook:gain-project"

#define DISTRHO_PLUGIN_HAS_UI       0
#define DISTRHO_PLUGIN_IS_RT_SAFE   1
#define DISTRHO_PLUGIN_NUM_INPUTS   1
#define DISTRHO_PLUGIN_NUM_OUTPUTS  1

enum Parameters {
    kGain = 0,
    kParameterCount
};

#endif
