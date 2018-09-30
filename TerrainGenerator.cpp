#include "Billow.h"
#include "ImageLoader.h"
#include "Perlin.h"
#include "RidgedMulti.h"
#include "TerrainGenerator.h"
#include "TerrainHandle.h"

#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

using namespace noise::module;

TerrainGenerator::TerrainGenerator(float width, float height)
    : mWidth(width)
    , mHeight(height)
{
    mTerrainHandle = std::make_shared<TerrainHandle>(mWidth, mHeight);

	std::shared_ptr<Perlin> perlinModule = std::make_shared<Perlin>();
	perlinModule->SetFrequency(1.0);
    perlinModule->SetLacunarity(5.0);
    perlinModule->SetOctaveCount(3);
    perlinModule->SetPersistence(0.3);

    mModules.push_back(perlinModule);

	std::shared_ptr<RidgedMulti> ridgedModule = std::make_shared<RidgedMulti>();
    ridgedModule->SetFrequency(2.0);
    ridgedModule->SetLacunarity(3.0);
    ridgedModule->SetOctaveCount(10);

    mModules.push_back(ridgedModule);

	std::shared_ptr<Billow> billowModule = std::make_shared<Billow>();
    billowModule->SetFrequency(2.0);
    billowModule->SetLacunarity(3.5);
    billowModule->SetOctaveCount(10);
    billowModule->SetPersistence(0.2);

    mModules.push_back(billowModule);
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
				output += it->GetValue(xoff, yoff, 0);
			}

			mTerrainHandle->setHeight(x, y, 200 * output);
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
