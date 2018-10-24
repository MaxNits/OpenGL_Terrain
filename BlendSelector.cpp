#include "BlendSelector.h"
#include "interp.h"

using namespace noise::module;

BlendSelector::BlendSelector()
	: Module(getSourceModuleCount())
{
}

double BlendSelector::getValue(double x, double y, double z) const
{
	assert (m_pSourceModule[0] != NULL);
	assert (m_pSourceModule[1] != NULL);
	assert (m_pSourceModule[2] != NULL);
	
	double v0 = mSourceModule[0]->getValue(x, y, z);
	double v1 = mSourceModule[1]->getValue(x, y, z);
	double alpha = (mSourceModule[2]->getValue(x, y, z) + 1.0) / 2.0;
	return LinearInterp(v0, v1, alpha);
}

const Module& noise::module::BlendSelector::GetControlModule() const
{
	if (mSourceModule == NULL || mSourceModule[2] == NULL)
	{
		throw noise::ExceptionNoModule();
	}

	return *(mSourceModule[2]);
}

int BlendSelector::getSourceModuleCount() const
{
	return 3;
}

void BlendSelector::setControlModule(const Module& controlModule)
{
	assert(mSourceModule != NULL);
	mSourceModule[2] = &controlModule;
}
