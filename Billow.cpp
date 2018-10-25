#include "Billow.h"

using namespace noise;
using namespace noise::module;

Billow::Billow()
	: Module(getSourceModuleCount())
	, mFrequency    (DEFAULT_BILLOW_FREQUENCY   )
	, mLacunarity   (DEFAULT_BILLOW_LACUNARITY  )
	, mNoiseQuality (DEFAULT_BILLOW_QUALITY     )
	, mOctaveCount  (DEFAULT_BILLOW_OCTAVE_COUNT)
	, mPersistence  (DEFAULT_BILLOW_PERSISTENCE )
	, mSeed         (DEFAULT_BILLOW_SEED)
{}

int Billow::getSourceModuleCount() const { return 0; }

double Billow::getValue(double x, double y, double z) const
{
	double value = 0.0;
	double signal = 0.0;
	double curPersistence = 1.0;
	double nx, ny, nz;
	int seed;

	x *= mFrequency;
	y *= mFrequency;
	z *= mFrequency;

	for (int curOctave = 0; curOctave < mOctaveCount; curOctave++) 
	{
		// Make sure that these floating-point values have the same range as a 32-
		// bit integer so that we can pass them to the coherent-noise functions.
		nx = MakeInt32Range(x);
		ny = MakeInt32Range(y);
		nz = MakeInt32Range(z);

		// Get the coherent-noise value from the input value and add it to the
		// final result.
		seed = (mSeed + curOctave) & 0xffffffff;
		signal = GradientCoherentNoise3D(nx, ny, nz, seed, mNoiseQuality);
		signal = 2.0 * fabs (signal) - 1.0;
		value += signal * curPersistence;

		// Prepare the next octave.
		x *= mLacunarity;
		y *= mLacunarity;
		z *= mLacunarity;
		curPersistence *= mPersistence;
	}

	value += 0.5;

	return value;
}

double Billow::getFrequency() const
{
	return mFrequency;
}

double Billow::getLacunarity() const
{
	return mLacunarity;
}

NoiseQuality Billow::getNoiseQuality() const
{
	return mNoiseQuality;
}

int Billow::getOctaveCount() const
{
	return mOctaveCount;
}

double Billow::getPersistence() const
{
	return mPersistence;
}

int Billow::getSeed() const
{ 
	return mSeed;
}

void Billow::setFrequency(double frequency)
{
	mFrequency = frequency;
}

void Billow::setLacunarity(double lacunarity)
{
	// For best results, set the lacunarity to a number between 1.5 and 3.5
	mLacunarity = lacunarity;
}

void Billow::setNoiseQuality(NoiseQuality noiseQuality)
{
	mNoiseQuality = noiseQuality;
}

void Billow::setOctaveCount(int octaveCount)
{
	if (octaveCount < 1 || octaveCount > BILLOW_MAX_OCTAVE)
	{
	  throw noise::ExceptionInvalidParam();
	}

	mOctaveCount = octaveCount;
}

void Billow::setPersistence(double persistence)
{
	// For best results, set the persistence value to a number between 0.0 and 1.0
	mPersistence = persistence;
}

void Billow::setSeed(int seed)
{ 
	mSeed = seed;
}
