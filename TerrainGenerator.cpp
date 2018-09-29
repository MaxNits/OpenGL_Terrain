#include "TerrainGenerator.h"
#include "TerrainHandle.h"
#include "ImageLoader.h"
#include "PerlinDevice.h"
#include "RidgedDevice.h"
#include "Perlin.h"

#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

constexpr auto HEIGHT_SHIFT = 0.5f;

using namespace noise::module;

TerrainGenerator::TerrainGenerator(float width, float height)
    : mWidth(width)
    , mHeight(height)
{
    mTerrainHandle = std::make_shared<TerrainHandle>(mWidth, mHeight);

	std::shared_ptr<Perlin> perlinModule = std::make_shared<Perlin>();
	perlinModule->SetFrequency(2.0);
    perlinModule->SetLacunarity(3.0);
    perlinModule->SetOctaveCount(10);
    perlinModule->SetPersistence(0.3);

    mModules.push_back(perlinModule);
}

std::shared_ptr<TerrainHandle> TerrainGenerator::loadTerrain(const char* filename, float height)
{
    std::shared_ptr<Image> image = loadBMP(filename);
    mTerrainHandle = std::make_shared<TerrainHandle>(image->width, image->height);

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            unsigned char color = (unsigned char)image->pixels[3 * (y * image->width + x)];
            float h = height * ((color / 255.0f) - 0.5f);
            mTerrainHandle->setHeight(x, y, h);
        }
    }

    mTerrainHandle->computeNormals();
    return mTerrainHandle;
}

std::shared_ptr<TerrainHandle> TerrainGenerator::generateTerrain()
{
    float frequency = 3; // hills frequency
    float offsetIncrement = 0.0001;
    float xoff = 0; // Perlin noise needs values between 0 and 1
    float yoff = 0; // That's why we feed it small incremental values for our [x,y] matrix

    for (float y = 0; y < mHeight; y++)
    {
        xoff = 0;

        for (float x = 0; x < mWidth; x++)
        {
			float output = 0.f;
			
			for (std::shared_ptr<Module> it : mModules)
			{
				output = it->GetValue(xoff, yoff, 0);
			}

			mTerrainHandle->setHeight(x, y, 500 * output);
            xoff += offsetIncrement * frequency;
        }

        yoff += offsetIncrement * frequency;
    }

    mTerrainHandle->computeNormals();
    return mTerrainHandle;
}

const std::shared_ptr<TerrainHandle> TerrainGenerator::getHandle()
{
    return mTerrainHandle;
}
