#include "checkerboard.h"

using namespace noise::module;

constexpr double OUTPUT_FACTOR = 0.5;

Checkerboard::Checkerboard()
	: Module(getSourceModuleCount())
	, mMinValue(-1.0)
	, mMaxValue(1.0)
	, mFrequency(10)
	, mCoordsFactor(1000)
{
}

double Checkerboard::getValue(double x, double y, double z) const
{
	/*int ix = (int)(floor(MakeInt32Range(x)));
	int iy = (int)(floor(MakeInt32Range(y)));
	int iz = (int)(floor(MakeInt32Range(z)));
	return (ix & mFrequency ^ iy & mFrequency ^ iz & mFrequency) ? mMinValue : mMaxValue;*/

	return GetValueCustom(x, y, z, mCoordsFactor, mFrequency);
}

int Checkerboard::getSourceModuleCount() const
{
	return 0;
}

void Checkerboard::setMinValue(double value)
{
	mMinValue = value;
}

void Checkerboard::setMaxValue(double value)
{
	mMaxValue = value;
}

void Checkerboard::setFrequency(unsigned value)
{
	mFrequency = value;
}

double Checkerboard::GetValueCustom(double x, double y, double z, unsigned coordsFactor, unsigned frequency) const
{
	int ix = x * coordsFactor;
	int iy = y * coordsFactor;
	int iz = z * coordsFactor;
	
	// if row/line is odd we return odd (int terms of "length") cells as 1
	// if it's even, we return even sells as 1

	unsigned rowFactor = (ix - (ix % frequency)) / frequency;
	bool isRowOdd = isOdd(rowFactor);

	unsigned lineFactor = (iy - (iy % frequency)) / frequency;
	bool isLineOdd = isOdd(lineFactor);

	if (isRowOdd)
	{
		return ((isLineOdd) ? mMinValue : mMaxValue) * OUTPUT_FACTOR;
	}
	else
	{
		return ((isLineOdd) ? mMaxValue : mMinValue) * OUTPUT_FACTOR;
	}
}

bool Checkerboard::isOdd(unsigned value) const
{
	return (value % 2) != 0;
}

void noise::module::Checkerboard::setCoordsFactor(unsigned value)
{
	mCoordsFactor = value;
}
