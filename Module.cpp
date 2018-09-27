#include "Module.h"

using namespace noise::module;

Module::Module(int sourceModuleCount)
{
	mSourceModule = NULL;

	// Create an array of pointers to all source modules required by this
	// noise module.  Set these pointers to NULL.
	if (sourceModuleCount > 0) {
		mSourceModule = new const Module*[sourceModuleCount];
		for (int i = 0; i < sourceModuleCount; i++) {
			mSourceModule[i] = NULL;
		}
	}
	else {
		mSourceModule = NULL;
	}
}

Module::~Module()
{
	delete[] mSourceModule;
}

const Module& Module::GetSourceModule(int index) const
{
	assert(m_pSourceModule != NULL);

	if (index >= GetSourceModuleCount() || index < 0
		|| mSourceModule[index] == NULL) {
		throw noise::ExceptionNoModule();
	}

	return *(mSourceModule[index]);
}

void Module::SetSourceModule(int index, const Module& sourceModule)
{
	assert(m_pSourceModule != NULL);

	if (index >= GetSourceModuleCount() || index < 0) {
		throw noise::ExceptionInvalidParam();
	}

	mSourceModule[index] = &sourceModule;
}