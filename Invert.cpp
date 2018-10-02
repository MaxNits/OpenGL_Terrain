#include "Invert.h"

using namespace noise::module;

Invert::Invert()
	: Module(GetSourceModuleCount())
{
}

double Invert::GetValue(double x, double y, double z) const
{
	assert (mSourceModule[0] != NULL);

	return -(mSourceModule[0]->GetValue(x, y, z));
}

int Invert::GetSourceModuleCount() const
{
	return 1;
}
