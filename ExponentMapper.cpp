#include "ExponentMapper.h"

using namespace noise::module;

ExponentMapper::ExponentMapper()
	: Module(GetSourceModuleCount())
	, m_exponent(DEFAULT_EXPONENT)
{
}

double ExponentMapper::GetValue (double x, double y, double z) const
{
	// Because most noise modules will output values that range from -1.0
	// to +1.0, ExponentMapper first normalizes this output value (the
	// range becomes 0.0 to 1.0), maps that value onto an exponential
	// curve, then rescales that value back to the original range.

	assert (m_pSourceModule[0] != NULL);
	
	double value = mSourceModule[0]->GetValue(x, y, z);
	return (pow(fabs((value + 1.0) / 2.0), m_exponent) * 2.0 - 1.0);
}

double ExponentMapper::GetExponent() const
{
	return m_exponent;
}

int ExponentMapper::GetSourceModuleCount() const
{
	return 1;
}

void ExponentMapper::SetExponent(double exponent)
{
	m_exponent = exponent;
}
