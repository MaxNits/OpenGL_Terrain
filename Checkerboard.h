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

    virtual int GetSourceModuleCount() const override;

    virtual double GetValue(double x, double y, double z) const override;

	virtual double GetValueCustom(double x, double y, double z, unsigned length) const;

	void setMinValue(double value);

	void setMaxValue(double value);

	void setFrequency(unsigned value);

private:
	bool isOdd(unsigned value) const;

	double mMinValue;
	double mMaxValue;
	unsigned mFrequency;
};

}
}

#endif
