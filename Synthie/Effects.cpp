#include "pch.h"
#include "Effects.h"

void CEffects::Compression(double input[2], double output[2])
{
	if (input[0] > 32767)
	{
		output[0] = 32767 + 0.1 * input[0];
		output[1] = 32767 + input[1] * 0.1;
	}
	else
	{
		output[0] = input[0];
		output[1] = input[1];
	}
}

void CEffects::NoiseGate(double input[2], double output[2])
{
	if (input[0] < 32767)
	{
		output[0] = 0.1 * input[0];
		output[1] = 0.1 * input[1];
	}
	else
	{
		output[0] = input[0];
		output[1] = input[1];
	}
}

void CEffects::Chorus(double input[2], double output[2])
{
	output[0] = input[0] + (0.75 * (m_onepast + m_twopast));
	output[1] = output[0];

	m_twopast = m_onepast;
	m_onepast = output[0];
}

