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
    
	/*noise::NoiseQuality GetNoiseQuality () const
    {
      return m_noiseQuality;
    }*/

    int GetOctaveCount() const
    {
		return m_octaveCount;
    }

    double GetPersistence() const
    {
		return m_persistence;
    }

    int GetSeed() const
    {
		return m_seed;
    }

    void SetFrequency(double frequency)
    {
		m_frequency = frequency;
    }

    void SetLacunarity(double lacunarity)
    {
		// For best results, set the lacunarity to a number between 1.5 and 3.5
		m_lacunarity = lacunarity;
    }
    
    /*void SetNoiseQuality (noise::NoiseQuality noiseQuality)
    {
		m_noiseQuality = noiseQuality;
    }*/

    void SetOctaveCount(int octaveCount)
    {
		if (octaveCount < 1 || octaveCount > BILLOW_MAX_OCTAVE) 
		{
			throw noise::ExceptionInvalidParam();
		}

		m_octaveCount = octaveCount;
    }

    void SetPersistence(double persistence)
    {
		// For best results, set the persistence value to a number between 0.0 and 1.0
		m_persistence = persistence;
    }

    void SetSeed(int seed)
    {
		m_seed = seed;
    }

protected:
    double m_frequency;
    double m_lacunarity;
    //noise::NoiseQuality m_noiseQuality;
    int m_octaveCount;
    double m_persistence;
    int m_seed;
};

} // namespace module
} // namespace noise

#endif
