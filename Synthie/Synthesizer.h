#include "msxml2.h"
#pragma once
#include <list>
#include "Instrument.h"
#include "ToneInstrument.h"
#include "Additive.h"
#include "xmlhelp.h"
#include <vector>
#include "Note.h"
#include "Effects.h"

#include <string>

class CSynthesizer
{
public:
    //! Number of audio channels
    int GetNumChannels() { return m_channels; }

    //! Sample rate in samples per second
    double GetSampleRate() { return m_sampleRate; }

    //! Sample period in seconds (1/samplerate)
    double GetSamplePeriod() { return m_samplePeriod; }

    //! Set the number of channels
    void SetNumChannels(int n) { m_channels = n; }

    //! Set the sample rate
    void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

    CSynthesizer();

    //! Start the synthesizer
    void Start(void);

    //! Generate one audio frame
    bool Generate(double* frame);

    //! Get the time since we started generating audio
    double GetTime() { return m_time; }

    void Clear() { m_instruments.clear(); m_notes.clear(); }

    void OpenScore(CString& filename);

    double GetBPM() { return m_bpm; }

private:
    int		m_channels;
    double	m_sampleRate;
    double	m_samplePeriod;

    double m_time;

    std::list<CInstrument*> m_instruments;

    void XmlLoadScore(IXMLDOMNode* xml);

    void XmlLoadInstrument(IXMLDOMNode* xml);

    void XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument);

    double  m_bpm;                  //!< Beats per minute
    int     m_beatspermeasure;  //!< Beats per measure
    double  m_secperbeat;        //!< Seconds per beat

    std::vector<CNote> m_notes;

    int m_currentNote;          //!< The current note we are playing
    int m_measure;              //!< The current measure
    double m_beat;              //!< The current beat within the measure


    CEffects m_effects;


    BOOL m_chorus = false;     // The chorus being used or not
    BOOL m_compression = false;     // The compression being used or not
    BOOL m_noisegate = false;       // The noise gate being used or not
};


#pragma comment(lib, "msxml2.lib")