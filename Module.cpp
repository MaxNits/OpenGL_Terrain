#include "Module.h"

using namespace noise::module;

Module::Module(int sourceModuleCount)
{
	mSourceModule = NULL;

	// Create an array of pointers to all source modules required by this
	// noise module. Set these pointers to NULL.
	if (sourceModuleCount > 0)
	{
		mSourceModule = new const Module*[sourceModuleCount];
		for (int i = 0; i < sourceModuleCount; i++)
		{
			mSourceModule[i] = NULL;
		}
	}
	else
	{
		mSourceModule = NULL;
	}
}

Module::~Module()
{
	delete[] mSourceModule;
}

const Module& Module::getSourceModule(int index) const
{
	assert(mSourceModule != NULL);

	if (index >= getSourceModuleCount() || index < 0 || mSourceModule[index] == NULL)
	{
		throw noise::ExceptionNoModule();
	}

	return *(mSourceModule[index]);
}

void Module::getSourceModule(int index, const Module& sourceModule)
{
	assert(mSourceModule != NULL);

	if (index >= getSourceModuleCount() || index < 0)
	{
		throw noise::ExceptionInvalidParam();
	}

	mSourceModule[index] = &sourceModule;
}