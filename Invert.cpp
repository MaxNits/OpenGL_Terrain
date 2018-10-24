#include "Invert.h"

using namespace noise::module;

Invert::Invert()
	: Module(getSourceModuleCount())
{
}

double Invert::getValue(double x, double y, double z) const
{
	assert (mSourceModule[0] != NULL);

	return -(mSourceModule[0]->getValue(x, y, z));
}

int Invert::getSourceModuleCount() const
{
	return 1;
}
