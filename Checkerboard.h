#ifndef NOISE_MODULE_CHECKERBOARD_H
#define NOISE_MODULE_CHECKERBOARD_H

#include "Module.h"

namespace noise
{
namespace module
{

class Checkerboard: public Module
{

public:
    Checkerboard();

    virtual int GetSourceModuleCount () const override;

    virtual double GetValue (double x, double y, double z) const override;

	void setMinValue(unsigned value);

	void setMaxValue(unsigned value);

private:
	unsigned mMinValue;
	unsigned mMaxValue;
};

}
}

#endif
