#ifndef NOISE_MODULE_RIDGEDMULTI_H
#define NOISE_MODULE_RIDGEDMULTI_H

#include "Module.h"

namespace noise
{
namespace module
{

const double DEFAULT_RIDGED_FREQUENCY = 1.0;
const double DEFAULT_RIDGED_LACUNARITY = 2.0;
const int DEFAULT_RIDGED_OCTAVE_COUNT = 6;
const noise::NoiseQuality DEFAULT_RIDGED_QUALITY = QUALITY_STD;
const int DEFAULT_RIDGED_SEED = 0;
const int RIDGED_MAX_OCTAVE = 30;

class RidgedMulti: public Module
{
public:
    RidgedMulti();

	virtual int GetSourceModuleCount() const override;

    virtual double GetValue(double x, double y, double z) const override;

    double GetFrequency() const;

    double GetLacunarity() const;

    noise::NoiseQuality GetNoiseQuality() const;

    int GetOctaveCount() const;

    int GetSeed() const;

    void SetFrequency(double frequency);

    void SetLacunarity(double lacunarity);

    void SetNoiseQuality(noise::NoiseQuality noiseQuality);

    void SetOctaveCount(int octaveCount);

    void SetSeed(int seed);

protected:
    void CalcSpectralWeights();

    double m_frequency;
    double m_lacunarity;
    noise::NoiseQuality m_noiseQuality;
    int m_octaveCount;
    double m_pSpectralWeights[RIDGED_MAX_OCTAVE];
    int m_seed;
};

} // namespace noise
} // namespace module

#endif
