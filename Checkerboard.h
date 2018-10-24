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

    virtual int getSourceModuleCount() const override;

    virtual double getValue(double x, double y, double z) const override;

	virtual double GetValueCustom(double x, double y, double z, unsigned frequency, unsigned length) const;

	void setMinValue(double value);

	void setMaxValue(double value);

	void setFrequency(unsigned value);

	void setCoordsFactor(unsigned value);

private:
	bool isOdd(unsigned value) const;

	double mMinValue;
	double mMaxValue;
	unsigned mFrequency;
	unsigned mCoordsFactor;
};

}
}

#endif
