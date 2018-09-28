#ifndef NOISE_MODULE_PERLIN_H
#define NOISE_MODULE_PERLIN_H

#include "Module.h"

namespace noise
{
namespace module
{

/// Default frequency for the noise::module::Perlin noise module.
const double DEFAULT_PERLIN_FREQUENCY = 1.0;

/// Default lacunarity for the noise::module::Perlin noise module.
const double DEFAULT_PERLIN_LACUNARITY = 2.0;

/// Default number of octaves for the noise::module::Perlin noise module.
const int DEFAULT_PERLIN_OCTAVE_COUNT = 6;

/// Default persistence value for the noise::module::Perlin noise module.
const double DEFAULT_PERLIN_PERSISTENCE = 0.5;

/// Default noise quality for the noise::module::Perlin noise module.
const noise::NoiseQuality DEFAULT_PERLIN_QUALITY = QUALITY_STD;

/// Default noise seed for the noise::module::Perlin noise module.
const int DEFAULT_PERLIN_SEED = 0;

/// Maximum number of octaves for the noise::module::Perlin noise module.
const int PERLIN_MAX_OCTAVE = 30;

class Perlin: public Module
{

public:
    Perlin ();

	virtual int GetSourceModuleCount() const override 
	{ 
		return 0; 
	}

    virtual double GetValue(double x, double y, double z) const override;

    // Returns the frequency of the first octave
    double GetFrequency () const
    {
		return m_frequency;
    }

    // The lacunarity is the frequency multiplier between successive octaves.
	double GetLacunarity() const
	{ 
		return m_lacunarity;
	}

    noise::NoiseQuality GetNoiseQuality () const
    {
		return m_noiseQuality;
    }

    int GetOctaveCount () const
    {
		return m_octaveCount;
    }

    double GetPersistence () const
    {
		return m_persistence;
    }

    int GetSeed () const
    {
		return m_seed;
    }

    // Sets the frequency of the first octave
    void SetFrequency (double frequency)
    {
		m_frequency = frequency;
    }

    void SetLacunarity (double lacunarity)
    {		
		// For best results, set the lacunarity to a number between 1.5 and 3.5	
		m_lacunarity = lacunarity;
    }

    void SetNoiseQuality (noise::NoiseQuality noiseQuality)
    {
		m_noiseQuality = noiseQuality;
    }

    void SetOctaveCount (int octaveCount)
    {
		if (octaveCount < 1 || octaveCount > PERLIN_MAX_OCTAVE)
		{
			throw noise::ExceptionInvalidParam();
		}

		m_octaveCount = octaveCount;
    }

    void SetPersistence (double persistence)
    {		
		// For best results, set the persistence to a number between 0.0 and 1.0.		
		m_persistence = persistence;
    }

    void SetSeed (int seed)
    {
		m_seed = seed;
    }

protected:
    double m_frequency; // Frequency of the first octave
    double m_lacunarity; // Frequency multiplier between successive octaves
    noise::NoiseQuality m_noiseQuality;	int m_octaveCount;
    double m_persistence;
    int m_seed;
};

}
}

#endif
