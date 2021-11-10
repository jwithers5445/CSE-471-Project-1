#pragma once


// Class used for effects does effects in place so no return is needed.
class CEffects
{
public:
	void Compression(double input[2], double output[2]);

	void NoiseGate(double input[2], double output[2]);

	void Chorus(double input[2], double output[2]);

private:
	double m_onepast = 0;
	double m_twopast = 0;
};

