#ifndef NOISE_MODULEBASE_H
#define NOISE_MODULEBASE_H

#include <stdlib.h>
#include <assert.h>
#include <math.h>
//#include "../basictypes.h"
#include "exception.h"
#include "NoiseGenerator.h"

namespace noise
{
namespace module
{

class Module
{

public:
	Module(int sourceModuleCount);

	virtual ~Module();

	virtual double getValue(double x, double y, double z) const = 0;

	virtual int getSourceModuleCount() const = 0;

	virtual const Module& getSourceModule(int index) const;

	virtual void getSourceModule(int index, const Module& sourceModule);

protected:
	// An array containing the pointers to each source module required by this noise module.
	const Module** mSourceModule;

private:
	// This assignment operator does nothing and cannot be overridden. This restriction
	// is necessary because if this object was copied, all source modules assigned to 
	// this noise module would need to be copied as well.
	const Module& operator= (const Module& module)
	{
		return *this;
	}
};

} // namespace module
} // namespace noise

#endif
