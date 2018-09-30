#ifndef NOISE_MODULE_PERLIN_H
#define NOISE_MODULE_PERLIN_H

#include "Module.h"

namespace noise
{
namespace module
{

const double DEFAULT_PERLIN_FREQUENCY = 1.0;
const double DEFAULT_PERLIN_LACUNARITY = 2.0;
const int DEFAULT_PERLIN_OCTAVE_COUNT = 6;
const double DEFAULT_PERLIN_PERSISTENCE = 0.5;
const noise::NoiseQuality DEFAULT_PERLIN_QUALITY = QUALITY_STD;
const int DEFAULT_PERLIN_SEED = 0;
const int PERLIN_MAX_OCTAVE = 30;

class Perlin: public Module
{
public:
    Perlin ();

	virtual int GetSourceModuleCount() const override;

    virtual double GetValue(double x, double y, double z) const override;

    double GetFrequency() const;

	double GetLacunarity() const;

    noise::NoiseQuality GetNoiseQuality() const;

    int GetOctaveCount() const;

    double GetPersistence() const;

    int GetSeed() const;

    void SetFrequency(double frequency);

    void SetLacunarity(double lacunarity);

    void SetNoiseQuality(noise::NoiseQuality noiseQuality);

    void SetOctaveCount(int octaveCount);

    void SetPersistence(double persistence);

    void SetSeed(int seed);

protected:
    double m_frequency;
    double m_lacunarity;
    noise::NoiseQuality m_noiseQuality;	int m_octaveCount;
    double m_persistence;
    int m_seed;
};

} // namespace module
} // namespace noise

#endif
