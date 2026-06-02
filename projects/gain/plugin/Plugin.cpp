// Copyright (c) 2026 MOD Audio Limited
// SPDX-License-Identifier: MIT
//
// Simple mono gain plugin. One audio in, one audio out, one parameter
// controlling output amplitude (0..4x).

#include "DistrhoPlugin.hpp"

START_NAMESPACE_DISTRHO

class GainPlugin : public Plugin
{
public:
    GainPlugin()
        : Plugin(kParameterCount, 0, 0),
          fGain(1.0f)
    {
    }

protected:
    const char* getLabel()       const override { return "Gain"; }
    const char* getDescription() const override { return "Simple mono gain plugin."; }
    const char* getMaker()       const override { return "MOD"; }
    const char* getHomePage()    const override { return "https://mod.audio"; }
    const char* getLicense()     const override { return "MIT"; }
    uint32_t    getVersion()     const override { return d_version(1, 0, 0); }
    int64_t     getUniqueId()    const override { return d_cconst('M', 'g', 'n', '1'); }

    void initParameter(uint32_t index, Parameter& parameter) override
    {
        if (index == kGain) {
            parameter.hints      = kParameterIsAutomatable;
            parameter.name       = "Gain";
            parameter.symbol     = "gain";
            parameter.unit       = "x";
            parameter.ranges.def = 1.0f;
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 4.0f;
        }
    }

    float getParameterValue(uint32_t index) const override
    {
        return (index == kGain) ? fGain : 0.0f;
    }

    void setParameterValue(uint32_t index, float value) override
    {
        if (index == kGain) fGain = value;
    }

    void run(const float** inputs, float** outputs, uint32_t frames) override
    {
        const float* in   = inputs[0];
        float*       out  = outputs[0];
        const float  gain = fGain;
        for (uint32_t i = 0; i < frames; ++i)
            out[i] = in[i] * gain;
    }

private:
    float fGain;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainPlugin)
};

Plugin* createPlugin() { return new GainPlugin(); }

END_NAMESPACE_DISTRHO
