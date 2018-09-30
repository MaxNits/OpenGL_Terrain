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

	virtual int GetSourceModuleCount() const override
	{ 
		return 0;
	}

    virtual double GetValue(double x, double y, double z) const override;

    double GetFrequency() const
    {
		return m_frequency;
    }

    double GetLacunarity() const
    {
		return m_lacunarity;
    }

    /*noise::NoiseQuality GetNoiseQuality() const
    {
		return m_noiseQuality;
    }*/

    int GetOctaveCount() const
    {
		return m_octaveCount;
    }

    int GetSeed () const
    {
		return m_seed;
    }

    void SetFrequency (double frequency)
    {
		m_frequency = frequency;
    }

    void SetLacunarity(double lacunarity) 
	{
		// For best results, set the lacunarity to a number between 1.5 and 3.5
		m_lacunarity = lacunarity; 
		
		CalcSpectralWeights();
    }

    /*void SetNoiseQuality (noise::NoiseQuality noiseQuality)
    {
		m_noiseQuality = noiseQuality;
    }*/

    void SetOctaveCount(int octaveCount)
    {
		if (octaveCount > RIDGED_MAX_OCTAVE) 
		{
			throw noise::ExceptionInvalidParam ();
		}

		m_octaveCount = octaveCount;
    }

    void SetSeed (int seed)
    {
		m_seed = seed;
    }

protected:
    void CalcSpectralWeights();

    double m_frequency;
    double m_lacunarity;
    //noise::NoiseQuality m_noiseQuality;
    int m_octaveCount;
    double m_pSpectralWeights[RIDGED_MAX_OCTAVE];
    int m_seed;
};

} // namespace noise
} // namespace module

#endif
