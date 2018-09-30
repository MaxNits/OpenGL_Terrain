#include "Billow.h"

using namespace noise::module;

Billow::Billow()
	: Module(GetSourceModuleCount())
	, m_frequency    (DEFAULT_BILLOW_FREQUENCY   )
	, m_lacunarity   (DEFAULT_BILLOW_LACUNARITY  )
	//, m_noiseQuality (DEFAULT_BILLOW_QUALITY     )
	, m_octaveCount  (DEFAULT_BILLOW_OCTAVE_COUNT)
	, m_persistence  (DEFAULT_BILLOW_PERSISTENCE )
	, m_seed         (DEFAULT_BILLOW_SEED)
{
}

double Billow::GetValue(double x, double y, double z) const
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
		signal = GradientCoherentNoise3D (nx, ny, nz, seed, DEFAULT_BILLOW_QUALITY);
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
