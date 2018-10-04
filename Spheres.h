#ifndef NOISE_MODULE_SPHERES_H
#define NOISE_MODULE_SPHERES_H

#include "Module.h"

namespace noise
{
namespace module
{

class Spheres: public Module
{
public:
    Spheres();

	virtual int GetSourceModuleCount() const override;

	virtual double GetValue(double x, double y, double z) const override;
	
	double GetFrequency() const;

    void SetFrequency(double frequency);

protected:
    double mFrequency;
};

} // namespace module
} // namespace noise

#endif
