#ifndef NOISE_MODULE_PERLIN_H
#define NOISE_MODULE_PERLIN_H

#include "Module.h"

namespace noise
{
namespace module
{

constexpr NoiseQuality DEFAULT_PERLIN_QUALITY = QUALITY_STD;
constexpr double DEFAULT_PERLIN_FREQUENCY = 1.0;
constexpr double DEFAULT_PERLIN_LACUNARITY = 2.0;
constexpr double DEFAULT_PERLIN_PERSISTENCE = 0.5;
constexpr int DEFAULT_PERLIN_OCTAVE_COUNT = 6;
constexpr int DEFAULT_PERLIN_SEED = 0;
constexpr int PERLIN_MAX_OCTAVE = 30;

class Perlin: public Module
{
public:
    Perlin ();

	virtual int getSourceModuleCount() const override;

    virtual double getValue(double x, double y, double z) const override;

    double getFrequency() const;

	double getLacunarity() const;

    noise::NoiseQuality getNoiseQuality() const;

    int getOctaveCount() const;

    double getPersistence() const;

    int getSeed() const;

    void setFrequency(double frequency);

    void setLacunarity(double lacunarity);

    void setNoiseQuality(noise::NoiseQuality noiseQuality);

    void setOctaveCount(int octaveCount);

    void setPersistence(double persistence);

    void setSeed(int seed);

protected:
	NoiseQuality m_noiseQuality;
    double m_frequency;
    double m_lacunarity;
	double m_persistence;
	int m_octaveCount;
    int m_seed;
};

} // namespace module
} // namespace noise

#endif
