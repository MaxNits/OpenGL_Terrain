#ifndef NOISE_MODULE_EXPONENT_H
#define NOISE_MODULE_EXPONENT_H

#include "Module.h"

namespace noise
{
namespace module
{

constexpr double DEFAULT_EXPONENT = 1.0;

class ExponentMapper : public Module
{
public:
	ExponentMapper();

	virtual int getSourceModuleCount() const override;

	virtual double getValue(double x, double y, double z) const override;

    double getExponent() const;

    void setExponent(double exponent);

protected:
    double mExponent;
};

} // namespace module
} // namespace noise

#endif
