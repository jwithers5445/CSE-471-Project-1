#include "pch.h"
#include "SineWavePlusHarmonics.h"

CSineWavePlusHarmonics::CSineWavePlusHarmonics()
{
	m_phase = 0;
	m_freq = 440;
}

void CSineWavePlusHarmonics::Start()
{
	m_phase = 0;
}

bool CSineWavePlusHarmonics::Generate()
{
	int num_harmonics = GetSampleRate() / (2 * m_freq);

	m_frame[0] = m_harmonics[0] * sin(m_phase * 2 * PI);

	for (int i = 1; i < num_harmonics; i++)
	{
		int s = i + 1;
		m_frame[0] += (m_harmonics[i] / s) * (sin(s*m_phase * 2 * PI));
	}
	m_frame[1] = m_frame[0];

	m_phase += m_freq * GetSamplePeriod();

	return true;
}

void CSineWavePlusHarmonics::SetHarmonics(double h[8])
{
	for (int i = 0; i < 8; i++)
	{
		m_harmonics[i] = h[i];
	}
}
