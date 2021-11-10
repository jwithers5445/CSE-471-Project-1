#include "pch.h"
#include "Additive.h"
#include <string>
#include "Notes.h"

using namespace std;

CAdditive::CAdditive()
{
    m_duration = 0.1;
}

void CAdditive::Start()
{
    m_sinewave.SetSampleRate(GetSampleRate());
    m_sinewave.SetHarmonics(m_harmonics);
    m_sinewave.Start();

    m_adsr.SetSource(&m_sinewave);
    m_adsr.SetSampleRate(GetSampleRate());
    m_adsr.Start();
    m_time = 0;
}

bool CAdditive::Generate()
{
    // Tell the component to generate an audio sample
    m_sinewave.Generate();

    bool valid = m_adsr.Generate();

    // Read the component's sample and make it our resulting frame.
    m_frame[0] = m_adsr.Frame(0);
    m_frame[1] = m_adsr.Frame(1);

    // Update time
    m_time += GetSamplePeriod();

    m_adsr.SetTime(m_time);

    // We return true until the time reaches the duration.
    return valid;
}

void CAdditive::SetNote(CNote* note)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for (int i = 0; i < len; i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal * (1 / (GetBPM() / 60)));

            m_adsr.SetDuration(value.dblVal * (1 / (GetBPM() / 60)));
        }

        else if (name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }
        else if (name == "harmonics1")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 0);
        }
        else if (name == "harmonics2")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 1);
        }
        else if (name == "harmonics3")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 2);
        }
        else if (name == "harmonics4")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 3);
        }
        else if (name == "harmonics5")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 4);
        }
        else if (name == "harmonics6")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 5);
        }
        else if (name == "harmonics7")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 6);
        }
        else if (name == "harmonics8")
        {
            value.ChangeType(VT_R8);
            SetHarmonics(value.dblVal, 7);
        }
    }

}

void CAdditive::SetHarmonics(double harm, int harm_value)
{
    m_harmonics[harm_value] = harm;
}
