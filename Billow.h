#ifndef NOISE_MODULE_BILLOW_H
#define NOISE_MODULE_BILLOW_H

#include "Module.h"

namespace noise
{
namespace module
{

constexpr NoiseQuality DEFAULT_BILLOW_QUALITY = QUALITY_STD;
constexpr double DEFAULT_BILLOW_FREQUENCY = 1.0;
constexpr double DEFAULT_BILLOW_LACUNARITY = 2.0;
constexpr double DEFAULT_BILLOW_PERSISTENCE = 0.5;
constexpr int BILLOW_MAX_OCTAVE = 30;
constexpr int DEFAULT_BILLOW_OCTAVE_COUNT = 6;
constexpr int DEFAULT_BILLOW_SEED = 0;

class Billow: public Module
{
public:
    Billow();

	virtual int getSourceModuleCount() const override;

    virtual double getValue(double x, double y, double z) const override;

	double getFrequency() const;

    double getLacunarity() const;
    
	NoiseQuality getNoiseQuality() const;

    int getOctaveCount() const;

    double getPersistence() const;

    int getSeed() const;

    void setFrequency(double frequency);

    void setLacunarity(double lacunarity);
    
    void setNoiseQuality(NoiseQuality noiseQuality);

    void setOctaveCount(int octaveCount);

    void setPersistence(double persistence);

    void setSeed(int seed);

protected:
	NoiseQuality mNoiseQuality;

    double mFrequency;
    double mLacunarity;
	double mPersistence;
    int mOctaveCount;
    int mSeed;
};

} // namespace module
} // namespace noise

#endif
