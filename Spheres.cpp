#include "misc.h"
#include "Spheres.h"
#include <math.h>

using namespace noise::module;

const double DEFAULT_SPHERES_FREQUENCY = 1.0;

Spheres::Spheres()
	: Module(GetSourceModuleCount())
	, mFrequency(DEFAULT_SPHERES_FREQUENCY)
	, mSpheresCenter(0.0, 0.0, 0.0)
{
}

double Spheres::GetValue(double x, double y, double z) const
{
	x *= mFrequency;
	y *= mFrequency;
	z *= mFrequency;
	
	double distFromCenter = sqrt((double)pow((x - mSpheresCenter.x), 2) +
								 (double)pow((y - mSpheresCenter.y), 2) +
								 (double)pow((z - mSpheresCenter.z), 2));
	double distFromSmallerSphere = distFromCenter - floor(distFromCenter);
	double distFromLargerSphere = 1.0 - distFromSmallerSphere;
	double nearestDist = GetMin(distFromSmallerSphere, distFromLargerSphere);
	return 1.0 - (nearestDist * 4.0); // Puts it in the -1.0 to +1.0 range.
}

double Spheres::GetFrequency() const
{
	return mFrequency;
}

int Spheres::GetSourceModuleCount() const
{
	return 0;
}

void Spheres::SetFrequency(double frequency)
{
	mFrequency = frequency;
}

void Spheres::SetSpheresCenter(double x, double y, double z)
{
	mSpheresCenter.x = x;
	mSpheresCenter.y = y;
	mSpheresCenter.z = z;
}
