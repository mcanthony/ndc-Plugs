/*
 * DISTRHO CycleShifter, a DPF'ied CycleShifter.
 * Copyright (C) 2004 Niall Moody
 * Copyright (C) 2015 Filipe Coelho <falktx@falktx.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef DISTRHO_PLUGIN_CYCLE_SHIFTER_HPP_INCLUDED
#define DISTRHO_PLUGIN_CYCLE_SHIFTER_HPP_INCLUDED

#include "DistrhoPlugin.hpp"

#define BUFFER_SIZE 11025

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class DistrhoPluginCycleShifter : public Plugin
{
public:
    enum Parameters {
        kParameterNewCycleVolume,
        kParameterInputVolume,
        kParameterCount
    };

    DistrhoPluginCycleShifter();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* d_getLabel() const noexcept override
    {
        return "CycleShifter";
    }

    const char* d_getMaker() const noexcept override
    {
        return "ndc Plugs";
    }

    const char* d_getLicense() const noexcept override
    {
        return "MIT";
    }

    uint32_t d_getVersion() const noexcept override
    {
        return 0x1000;
    }

    int64_t d_getUniqueId() const noexcept override
    {
        return d_cconst('C', 'S', 'f', 't');
    }

    // -------------------------------------------------------------------
    // Init

    void d_initParameter(uint32_t index, Parameter& parameter) override;
    void d_initProgramName(uint32_t index, d_string& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float d_getParameterValue(uint32_t index) const override;
    void  d_setParameterValue(uint32_t index, float value) override;
    void  d_setProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Process

    void d_activate() override;
    void d_run(const float** inputs, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------

private:
    float fNewCycleVolume;
    float fInputVolume;

    float CycleBuffer[BUFFER_SIZE]; // buffer to store the cycle in
    int OutIndex;                   // index for playing the buffer
    int InCount;                    // counts how many samples we've recorded
    bool ReadWrite;                 // 0=read, 1=write
    float EnvOld;                   // last (input) sample - used to determine zero-crossings

    float DoProcess(float a);

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistrhoPluginCycleShifter)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // DISTRHO_PLUGIN_CYCLE_SHIFTER_HPP_INCLUDED