#pragma once

#include <math.h>
//#include "basictypes.h"

namespace noise
{

enum NoiseQuality
{
	QUALITY_FAST = 0, // Generates coherent noise quickly.
	QUALITY_STD = 1, // Generates standard-quality coherent noise.
	QUALITY_BEST = 2 // Generates the best-quality coherent noise.
};

double GradientCoherentNoise3D(double x, double y, double z, int seed = 0, NoiseQuality noiseQuality = QUALITY_STD);

double GradientNoise3D(double fx, double fy, double fz, int ix, int iy, int iz, int seed = 0);

int IntValueNoise3D(int x, int y, int z, int seed = 0);

inline double MakeInt32Range(double n)
{
	if (n >= 1073741824.0)
	{
		return (2.0 * fmod(n, 1073741824.0)) - 1073741824.0;
	}
	else if (n <= -1073741824.0)
	{
		return (2.0 * fmod(n, 1073741824.0)) + 1073741824.0;
	}
	else
	{
		return n;
	}
}

double ValueCoherentNoise3D(double x, double y, double z, int seed = 0, NoiseQuality noiseQuality = QUALITY_STD);

double ValueNoise3D(int x, int y, int z, int seed = 0);
}
