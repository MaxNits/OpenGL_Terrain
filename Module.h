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

	virtual const Module& getSourceModule(unsigned index) const;

	// TODO: refactor this into vector to be able to insert and delete in the middle of the chain
	virtual void setSourceModule(unsigned index, const Module& sourceModule);

protected:
	// An array containing pointers to each source module required by this noise module.
	const Module** mSourceModule;

private:
	// This assignment operator does nothing and cannot be overridden. This restriction
	// is necessary because if this object was copied, all source modules assigned to
	// this noise module would need to be copied as well.
	const Module& operator=(const Module& module)
	{
		return *this;
	}
};

} // namespace module
} // namespace noise

#endif
