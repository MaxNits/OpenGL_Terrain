#include "Module.h"

using namespace noise::module;

Module::Module(int sourceModuleCount)
{
	m_pSourceModule = NULL;

	// Create an array of pointers to all source modules required by this
	// noise module.  Set these pointers to NULL.
	if (sourceModuleCount > 0) {
		m_pSourceModule = new const Module*[sourceModuleCount];
		for (int i = 0; i < sourceModuleCount; i++) {
			m_pSourceModule[i] = NULL;
		}
	}
	else {
		m_pSourceModule = NULL;
	}
}

Module::~Module()
{
	delete[] m_pSourceModule;
}

const Module& Module::GetSourceModule(int index) const
{
	assert(m_pSourceModule != NULL);

	if (index >= GetSourceModuleCount() || index < 0
		|| m_pSourceModule[index] == NULL) {
		throw noise::ExceptionNoModule();
	}

	return *(m_pSourceModule[index]);
}

void Module::SetSourceModule(int index, const Module& sourceModule)
{
	assert(m_pSourceModule != NULL);

	if (index >= GetSourceModuleCount() || index < 0) {
		throw noise::ExceptionInvalidParam();
	}

	m_pSourceModule[index] = &sourceModule;
}