#include "misc.h"
#include "Spheres.h"

using namespace noise::module;

const double DEFAULT_SPHERES_FREQUENCY = 1.0;

Spheres::Spheres()
	: Module (GetSourceModuleCount())
	, mFrequency(DEFAULT_SPHERES_FREQUENCY)
{
}

double Spheres::GetValue(double x, double y, double z) const
{
	x *= mFrequency;
	y *= mFrequency;
	z *= mFrequency;
	
	double distFromCenter = sqrt(x * x + y * y + z * z);
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
