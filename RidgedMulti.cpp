#include "RidgedMulti.h"

using namespace noise;
using namespace noise::module;

RidgedMulti::RidgedMulti()
	: Module (getSourceModuleCount())
	, mFrequency    (DEFAULT_RIDGED_FREQUENCY   )
	, mLacunarity   (DEFAULT_RIDGED_LACUNARITY  )
	, mNoiseQuality (DEFAULT_RIDGED_QUALITY     )
	, mOctaveCount  (DEFAULT_RIDGED_OCTAVE_COUNT)
	, mSeed         (DEFAULT_RIDGED_SEED)
{
	calcSpectralWeights();
}

int RidgedMulti::getSourceModuleCount() const {
  return 0;
}

void RidgedMulti::calcSpectralWeights()
{
	double h = 1.0; // This exponent parameter should be user-defined
	double frequency = 1.0;

	for (int i = 0; i < RIDGED_MAX_OCTAVE; i++) 
	{
		// Compute weight for each frequency.
		mSpectralWeights[i] = pow(frequency, -h);
		frequency *= mLacunarity;
	}
}

double RidgedMulti::getValue(double x, double y, double z) const
{
	x *= mFrequency;
	y *= mFrequency;
	z *= mFrequency;
	
	double signal = 0.0;
	double value  = 0.0;
	double weight = 1.0;
	
	// These parameters should be user-defined
	double offset = 1.0;
	double gain = 2.0;
	
	for (int curOctave = 0; curOctave < mOctaveCount; curOctave++) 
	{
		// Make sure that these floating-point values have the same range as a 32-
		// bit integer so that we can pass them to the coherent-noise functions.
		double nx, ny, nz;
		nx = MakeInt32Range(x);
		ny = MakeInt32Range(y);
		nz = MakeInt32Range(z);
		
		// Get the coherent-noise value.
		int seed = (mSeed + curOctave) & 0x7fffffff;
		signal = GradientCoherentNoise3D (nx, ny, nz, seed, mNoiseQuality);
		
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
		value += (signal * mSpectralWeights[curOctave]);
		
		// Go to the next octave.
		x *= mLacunarity;
		y *= mLacunarity;
		z *= mLacunarity;
	}
	
	return (value * 1.25) - 1.0;
}

double RidgedMulti::getFrequency() const
{
	return mFrequency;
}

double RidgedMulti::getLacunarity() const
{
	return mLacunarity;
}

NoiseQuality RidgedMulti::getNoiseQuality() const
{
	return mNoiseQuality;
}

int RidgedMulti::getOctaveCount() const
{
	return mOctaveCount;
}

int RidgedMulti::getSeed() const
{ 
	return mSeed;
}

void RidgedMulti::setFrequency(double frequency)
{
	mFrequency = frequency;
}

void RidgedMulti::setLacunarity(double lacunarity)
{
	// For best results, set the lacunarity to a number between 1.5 and 3.5
	mLacunarity = lacunarity;

	calcSpectralWeights();
}

void
RidgedMulti::setNoiseQuality(NoiseQuality noiseQuality)
{
	mNoiseQuality = noiseQuality;
}

void RidgedMulti::setOctaveCount(int octaveCount)
{
	if (octaveCount > RIDGED_MAX_OCTAVE)
	{
	  throw noise::ExceptionInvalidParam();
	}

	mOctaveCount = octaveCount;
}

void RidgedMulti::setSeed(int seed)
{ 
	mSeed = seed;
}
