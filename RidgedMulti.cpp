#include "RidgedMulti.h"

using namespace noise::module;

RidgedMulti::RidgedMulti()
	: Module (GetSourceModuleCount())
	, m_frequency    (DEFAULT_RIDGED_FREQUENCY   )
	, m_lacunarity   (DEFAULT_RIDGED_LACUNARITY  )
	, m_noiseQuality (DEFAULT_RIDGED_QUALITY     )
	, m_octaveCount  (DEFAULT_RIDGED_OCTAVE_COUNT)
	, m_seed         (DEFAULT_RIDGED_SEED)
{
	CalcSpectralWeights();
}

int RidgedMulti::GetSourceModuleCount() const {
  return 0;
}

void RidgedMulti::CalcSpectralWeights()
{
	double h = 1.0; // This exponent parameter should be user-defined
	double frequency = 1.0;

	for (int i = 0; i < RIDGED_MAX_OCTAVE; i++) 
	{
		// Compute weight for each frequency.
		m_pSpectralWeights[i] = pow(frequency, -h);
		frequency *= m_lacunarity;
	}
}

double RidgedMulti::GetValue(double x, double y, double z) const
{
	x *= m_frequency;
	y *= m_frequency;
	z *= m_frequency;
	
	double signal = 0.0;
	double value  = 0.0;
	double weight = 1.0;
	
	// These parameters should be user-defined
	double offset = 1.0;
	double gain = 2.0;
	
	for (int curOctave = 0; curOctave < m_octaveCount; curOctave++) 
	{
		// Make sure that these floating-point values have the same range as a 32-
		// bit integer so that we can pass them to the coherent-noise functions.
		double nx, ny, nz;
		nx = MakeInt32Range(x);
		ny = MakeInt32Range(y);
		nz = MakeInt32Range(z);
		
		// Get the coherent-noise value.
		int seed = (m_seed + curOctave) & 0x7fffffff;
		signal = GradientCoherentNoise3D (nx, ny, nz, seed, m_noiseQuality);
		
		// Make the ridges.
		signal = fabs(signal);
		signal = offset - signal;
		
		// Square the signal to increase the sharpness of the ridges.
		signal *= signal;
		
		// The weighting from the previous octave is applied to the signal.
		// Larger values have higher weights, producing sharp points along the
		// ridges.
		signal *= weight;
		
		// Weight successive contributions by the previous signal.
		weight = signal * gain;
		if (weight > 1.0) {
		  weight = 1.0;
		}
		if (weight < 0.0) {
		  weight = 0.0;
		}
		
		// Add the signal to the output value.
		value += (signal * m_pSpectralWeights[curOctave]);
		
		// Go to the next octave.
		x *= m_lacunarity;
		y *= m_lacunarity;
		z *= m_lacunarity;
	}
	
	return (value * 1.25) - 1.0;
}

double RidgedMulti::GetFrequency() const
{
	return m_frequency;
}

double RidgedMulti::GetLacunarity() const
{
	return m_lacunarity;
}

noise::NoiseQuality RidgedMulti::GetNoiseQuality() const
{
	return m_noiseQuality;
}

int RidgedMulti::GetOctaveCount() const
{
	return m_octaveCount;
}

int RidgedMulti::GetSeed() const
{ 
	return m_seed;
}

void RidgedMulti::SetFrequency(double frequency)
{
	m_frequency = frequency;
}

void RidgedMulti::SetLacunarity(double lacunarity)
{
	// For best results, set the lacunarity to a number between 1.5 and 3.5
	m_lacunarity = lacunarity;

	CalcSpectralWeights();
}

void
RidgedMulti::SetNoiseQuality(noise::NoiseQuality noiseQuality)
{
	m_noiseQuality = noiseQuality;
}

void RidgedMulti::SetOctaveCount(int octaveCount)
{
	if (octaveCount > RIDGED_MAX_OCTAVE)
	{
	  throw noise::ExceptionInvalidParam();
	}

	m_octaveCount = octaveCount;
}

void RidgedMulti::SetSeed(int seed)
{ 
	m_seed = seed;
}
