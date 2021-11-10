#pragma once
#include "AudioNode.h"
class CSineWavePlusHarmonics :
    public CAudioNode
{
public:
    CSineWavePlusHarmonics();

    //! Start audio generation
    virtual void Start();

    //! Generate one frame of audio
    virtual bool Generate();

    //! Set the sine wave frequency
    void SetFreq(double f) { m_freq = f; }

    //! Set the sine wave amplitude
    void SetAmplitude(double a) { m_amp = a; }

    // Set the sine wave harmonics

    void SetHarmonics(double h[8]);

private:
    double m_freq;
    double m_amp;
    double m_phase;

    double m_harmonics[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
};

