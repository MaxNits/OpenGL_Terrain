#ifndef NOISE_MODULE_SELECT_H
#define NOISE_MODULE_SELECT_H

#include "Module.h"

namespace noise
{
namespace module
{

const double DEFAULT_SELECT_EDGE_FALLOFF = 0.0;
const double DEFAULT_SELECT_LOWER_BOUND = -1.0;
const double DEFAULT_SELECT_UPPER_BOUND = 1.0;

class RangeSelector: public Module
{
public:
	RangeSelector();

	virtual int getSourceModuleCount() const override;

	virtual double getValue(double x, double y, double z) const override;

	const Module& getControlModule() const;

    double getEdgeFalloff() const;

    double getLowerBound() const;

    double getUpperBound() const;

    void getBounds(double lowerBound, double upperBound);

    void setControlModule(const Module& controlModule);

    void setEdgeFalloff(double edgeFalloff);

protected:
    double mEdgeFalloff;
    double mLowerBound;
    double mUpperBound;
};

} // namespace module
} // namespace noise

#endif
