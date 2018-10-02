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

	virtual int GetSourceModuleCount() const override;

	virtual double GetValue(double x, double y, double z) const override;
	
	void EnableDistance(bool enable = true);

    double GetDisplacement() const;
	
	double GetFrequency() const;

    int GetSeed() const;

    bool IsDistanceEnabled() const;
    
    void SetDisplacement(double displacement);

    void SetFrequency(double frequency);

    void SetSeed(int seed);

protected:
    double m_displacement;
    bool m_enableDistance;
    double m_frequency;
    int m_seed;
};

} // namespace noise
} // namespace module

#endif
