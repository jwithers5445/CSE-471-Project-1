#include "pch.h"
#include "ADSR.h"

void CADSR::Start()
{
    m_time = 0;
}

bool CADSR::Generate()
{
	// Tell the component to generate an audio sample
	m_source->Generate();

	// Read the component's sample and make it our resulting frame.
	if (m_time < m_attack)
	{
		m_frame[0] = m_source->Frame(0) * m_time / m_attack;
		m_frame[1] = m_source->Frame(1) * m_time / m_attack;
	}
	else if (m_time >= m_attack && m_time < m_attack + m_decay)
	{
		m_frame[0] = m_source->Frame(0) * (1 - ((m_time - m_attack) * 100) / (4));
		m_frame[1] = m_source->Frame(1) * (1 - ((m_time - m_attack) * 100) / (4));
	}

	else if (m_time > m_duration - m_release)
	{
		m_frame[0] = m_source->Frame(0) * (m_duration - m_time) / m_release;
		m_frame[1] = m_source->Frame(1) * (m_duration - m_time) / m_release;
	}
	else
	{
		m_frame[0] = m_source->Frame(0) * 0.5;
		m_frame[1] = m_source->Frame(1) * 0.5;
	}
	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration;
}