#include "checkerboard.h"

using namespace noise::module;

Checkerboard::Checkerboard()
	: Module(GetSourceModuleCount())
	, mMinValue(-1.0)
	, mMaxValue(1.0)
	, mFrequency(10)
{
}

double Checkerboard::GetValue(double x, double y, double z) const
{
	/*int ix = (int)(floor(MakeInt32Range(x)));
	int iy = (int)(floor(MakeInt32Range(y)));
	int iz = (int)(floor(MakeInt32Range(z)));
	return (ix & mFrequency ^ iy & mFrequency ^ iz & mFrequency) ? mMinValue : mMaxValue;*/

	return GetValueCustom(x, y, z, mFrequency);
}

int Checkerboard::GetSourceModuleCount() const
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

double Checkerboard::GetValueCustom(double x, double y, double z, unsigned length) const
{
	int ix = (int)(floor(MakeInt32Range(x)));
	int iy = (int)(floor(MakeInt32Range(y)));
	int iz = (int)(floor(MakeInt32Range(z)));
	
	// if row/line is odd we return odd (int terms of "length") cells as 1
	// if it's even, we return even sells as 1

	unsigned rowFactor = (ix - (ix % length)) / length;
	bool isRowOdd = isOdd(rowFactor);

	unsigned lineFactor = (iy - (iy % length)) / length;
	bool isLineOdd = isOdd(lineFactor);

	if (isRowOdd)
	{
		return (isLineOdd) ? mMinValue : mMaxValue;
	}
	else
	{
		return (isLineOdd) ? mMaxValue : mMinValue;
	}
}

bool Checkerboard::isOdd(unsigned value) const
{
	return (value % 2) != 0;
}
