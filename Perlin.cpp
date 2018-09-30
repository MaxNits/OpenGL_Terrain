#include "Perlin.h"

using namespace noise::module;

Perlin::Perlin()
	: Module(GetSourceModuleCount())
	, m_frequency    (DEFAULT_PERLIN_FREQUENCY   )
	, m_lacunarity   (DEFAULT_PERLIN_LACUNARITY  )
	, m_noiseQuality (DEFAULT_PERLIN_QUALITY     )
	, m_octaveCount  (DEFAULT_PERLIN_OCTAVE_COUNT)
	, m_persistence  (DEFAULT_PERLIN_PERSISTENCE )
	, m_seed         (DEFAULT_PERLIN_SEED)
{
}

int Perlin::GetSourceModuleCount() const { return 0; }

double Perlin::GetValue(double x, double y, double z) const
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
		nx = MakeInt32Range (x);
		ny = MakeInt32Range (y);
		nz = MakeInt32Range (z);
		
		// Get the coherent-noise value from the input value and add it to the
		// final result.
		seed = (m_seed + curOctave) & 0xffffffff;
		signal = GradientCoherentNoise3D (nx, ny, nz, seed, m_noiseQuality);
		value += signal * curPersistence;
		
		// Prepare the next octave.
		x *= m_lacunarity;
		y *= m_lacunarity;
		z *= m_lacunarity;
		curPersistence *= m_persistence;
	}	
	
	return value;
}

double Perlin::GetFrequency() const
{
	return m_frequency;
}

double Perlin::GetLacunarity() const
{
	return m_lacunarity;
}

noise::NoiseQuality Perlin::GetNoiseQuality() const
{
	return m_noiseQuality;
}

int Perlin::GetOctaveCount() const
{
	return m_octaveCount;
}

double Perlin::GetPersistence() const
{
	return m_persistence;
}

int Perlin::GetSeed() const
{ 
	return m_seed; 
}

void Perlin::SetFrequency(double frequency)
{
	m_frequency = frequency;
}

void Perlin::SetLacunarity(double lacunarity)
{
	// For best results, set the lacunarity to a number between 1.5 and 3.5
	m_lacunarity = lacunarity;
}

void Perlin::SetNoiseQuality(noise::NoiseQuality noiseQuality)
{
	m_noiseQuality = noiseQuality;
}

void Perlin::SetOctaveCount(int octaveCount)
{
	if (octaveCount < 1 || octaveCount > PERLIN_MAX_OCTAVE)
	{
	  throw noise::ExceptionInvalidParam();
	}

	m_octaveCount = octaveCount;
}

void Perlin::SetPersistence(double persistence)
{
	// For best results, set the persistence to a number between 0.0 and 1.0.
	m_persistence = persistence;
}

void Perlin::SetSeed(int seed)
{
	m_seed = seed;
}
