#ifndef NOISE_MODULE_VORONOI_H
#define NOISE_MODULE_VORONOI_H

#include "Module.h"

namespace noise
{
namespace module
{

const double DEFAULT_VORONOI_DISPLACEMENT = 1.0; // Default displacement to apply to each cell
const double DEFAULT_VORONOI_FREQUENCY = 1.0;
const int DEFAULT_VORONOI_SEED = 0;

class Voronoi: public Module
{
public:
    Voronoi ();

	virtual int getSourceModuleCount() const override;

	virtual double getValue(double x, double y, double z) const override;
	
	void enableDistance(bool enable = true);

    double getDisplacement() const;
	
	double getFrequency() const;

    int getSeed() const;

    bool isDistanceEnabled() const;
    
    void setDisplacement(double displacement);

    void setFrequency(double frequency);

    void setSeed(int seed);

protected:
    double mDisplacement;
	double mFrequency;
    int mSeed;
	bool mEnableDistance;
};

} // namespace noise
} // namespace module

#endif
