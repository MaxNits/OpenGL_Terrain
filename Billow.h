#ifndef NOISE_MODULE_BILLOW_H
#define NOISE_MODULE_BILLOW_H

#include "Module.h"

namespace noise
{
namespace module
{

const double DEFAULT_BILLOW_FREQUENCY = 1.0;
const double DEFAULT_BILLOW_LACUNARITY = 2.0;
const int DEFAULT_BILLOW_OCTAVE_COUNT = 6;
const double DEFAULT_BILLOW_PERSISTENCE = 0.5;
const noise::NoiseQuality DEFAULT_BILLOW_QUALITY = QUALITY_STD;
const int DEFAULT_BILLOW_SEED = 0;
const int BILLOW_MAX_OCTAVE = 30;

class Billow: public Module
{
public:
    Billow();

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
    noise::NoiseQuality m_noiseQuality;
    int m_octaveCount;
    double m_persistence;
    int m_seed;
};

} // namespace module
} // namespace noise

#endif
