#include "Billow.h"

using namespace noise::module;

Billow::Billow()
	: Module(getSourceModuleCount())
	, m_frequency    (DEFAULT_BILLOW_FREQUENCY   )
	, m_lacunarity   (DEFAULT_BILLOW_LACUNARITY  )
	, m_noiseQuality (DEFAULT_BILLOW_QUALITY     )
	, m_octaveCount  (DEFAULT_BILLOW_OCTAVE_COUNT)
	, m_persistence  (DEFAULT_BILLOW_PERSISTENCE )
	, m_seed         (DEFAULT_BILLOW_SEED)
{}

int Billow::getSourceModuleCount() const { return 0; }

double Billow::getValue(double x, double y, double z) const
{
	double value = 0.0;
	double signal = 0.0;
	double curPersistence = 1.0;
	double nx, ny, nz;
	int seed;

	x *= m_frequency;
	y *= m_frequency;
	z *= m_frequency;

	for (int curOctave = 0; curOctave < m_octaveCount; curOctave++) 
	{
		// Make sure that these floating-point values have the same range as a 32-
		// bit integer so that we can pass them to the coherent-noise functions.
		nx = MakeInt32Range(x);
		ny = MakeInt32Range(y);
		nz = MakeInt32Range(z);

		// Get the coherent-noise value from the input value and add it to the
		// final result.
		seed = (m_seed + curOctave) & 0xffffffff;
		signal = GradientCoherentNoise3D(nx, ny, nz, seed, m_noiseQuality);
		signal = 2.0 * fabs (signal) - 1.0;
		value += signal * curPersistence;

		// Prepare the next octave.
		x *= m_lacunarity;
		y *= m_lacunarity;
		z *= m_lacunarity;
		curPersistence *= m_persistence;
	}

	value += 0.5;

	return value;
}

double Billow::getFrequency() const
{
	return m_frequency;
}

double Billow::getLacunarity() const
{
	return m_lacunarity;
}

noise::NoiseQuality Billow::getNoiseQuality() const
{
	return m_noiseQuality;
}

int Billow::getOctaveCount() const
{
	return m_octaveCount;
}

double Billow::getPersistence() const
{
	return m_persistence;
}

int Billow::getSeed() const
{ 
	return m_seed;
}

void Billow::setFrequency(double frequency)
{
	m_frequency = frequency;
}

void Billow::setLacunarity(double lacunarity)
{
	// For best results, set the lacunarity to a number between 1.5 and 3.5
	m_lacunarity = lacunarity;
}

void Billow::setNoiseQuality(noise::NoiseQuality noiseQuality)
{
	m_noiseQuality = noiseQuality;
}

void Billow::setOctaveCount(int octaveCount)
{
	if (octaveCount < 1 || octaveCount > BILLOW_MAX_OCTAVE)
	{
	  throw noise::ExceptionInvalidParam();
	}

	m_octaveCount = octaveCount;
}

void Billow::setPersistence(double persistence)
{
	// For best results, set the persistence value to a number between 0.0 and 1.0
	m_persistence = persistence;
}

void Billow::setSeed(int seed)
{ 
	m_seed = seed;
}
