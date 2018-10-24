#include "ExponentMapper.h"

using namespace noise::module;

ExponentMapper::ExponentMapper()
	: Module(getSourceModuleCount())
	, mExponent(DEFAULT_EXPONENT)
{
}

double ExponentMapper::getValue(double x, double y, double z) const
{
	// Because most noise modules will output values that range from -1.0
	// to +1.0, ExponentMapper first normalizes this output value (the
	// range becomes 0.0 to 1.0), maps that value onto an exponential
	// curve, then rescales that value back to the original range.

	assert (mSourceModule[0] != NULL);
	
	double value = mSourceModule[0]->getValue(x, y, z);
	return (pow(fabs((value + 1.0) / 2.0), mExponent) * 2.0 - 1.0);
}

double ExponentMapper::GetExponent() const
{
	return mExponent;
}

int ExponentMapper::getSourceModuleCount() const
{
	return 1;
}

void ExponentMapper::SetExponent(double exponent)
{
	mExponent = exponent;
}
