#ifndef NOISE_MODULE_SPHERES_H
#define NOISE_MODULE_SPHERES_H

#include "Module.h"

namespace noise
{
namespace module
{

struct SperesCenter
{
	SperesCenter(double _x, double _y, double _z)
		: x(_x)
		, y(_y)
		, z(_z)
	{
	}

	double x;
	double y;
	double z;
};

class Spheres: public Module
{
public:
	Spheres();

	virtual int getSourceModuleCount() const override;

	virtual double getValue(double x, double y, double z) const override;
	
	double getFrequency() const;

    void setFrequency(double frequency);

	void setSpheresCenter(double x, double y, double z);

protected:
    double mFrequency;
	SperesCenter mSpheresCenter;
};

} // namespace module
} // namespace noise

#endif
