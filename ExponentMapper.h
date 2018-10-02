#ifndef NOISE_MODULE_EXPONENT_H
#define NOISE_MODULE_EXPONENT_H

#include "Module.h"

namespace noise
{
namespace module
{

const double DEFAULT_EXPONENT = 1.0;

class ExponentMapper : public Module
{
public:
	ExponentMapper();

	virtual int GetSourceModuleCount() const override;

	virtual double GetValue(double x, double y, double z) const override;

    double GetExponent() const;

    void SetExponent(double exponent);

protected:
    double mExponent;
};

} // namespace module
} // namespace noise

#endif
