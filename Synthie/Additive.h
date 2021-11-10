#pragma once
#include "Instrument.h"

#include "ADSR.h"
#include "SineWavePlusHarmonics.h"

class CAdditive :
    public CInstrument
{
public:
    CAdditive();

    virtual ~CAdditive() {}

    virtual void Start();
    virtual bool Generate();

    void SetNote(CNote* note);

    void SetHarmonics(double harm, int harm_value);

    void SetDuration(double d) { m_duration = d; }


    void SetFreq(double f) { m_sinewave.SetFreq(f); }
    void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
private:
    double m_duration;
    double m_time;

    double m_harmonics[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    CSineWavePlusHarmonics m_sinewave;

    CADSR m_adsr;

};

