#include "checkerboard.h"

using namespace noise::module;

Checkerboard::Checkerboard()
	: Module(GetSourceModuleCount())
	, mMinValue(-1)
	, mMaxValue(1)
{
}

double Checkerboard::GetValue(double x, double y, double z) const
{
	int ix = (int)(floor(MakeInt32Range(x)));
	int iy = (int)(floor(MakeInt32Range(y)));
	int iz = (int)(floor(MakeInt32Range(z)));
	return (ix & 1 ^ iy & 1 ^ iz & 1) ? mMinValue : mMaxValue;
}

int Checkerboard::GetSourceModuleCount() const
{
	return 0;
}

void Checkerboard::setMinValue(unsigned value)
{
	mMinValue = value;
}

void Checkerboard::setMaxValue(unsigned value)
{
	mMaxValue = value;
}
