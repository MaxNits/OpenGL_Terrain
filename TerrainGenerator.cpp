#include "Billow.h"
#include "BlendSelector.h"
#include "CurveMapper.h"
#include "Checkerboard.h"
#include "ExponentMapper.h"
#include "ImageLoader.h"
#include "Invert.h"
#include "Perlin.h"
#include "RidgedMulti.h"
#include "Spheres.h"
#include "Terrace.h"
#include "TerrainGenerator.h"
#include "TerrainHandle.h"
#include "Voronoi.h"

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
	perlinModule->setFrequency(2.0);
    perlinModule->setLacunarity(3.0);
    perlinModule->setOctaveCount(7);
    perlinModule->setPersistence(0.3);
    //mModules.push_back(perlinModule);

	std::shared_ptr<RidgedMulti> ridgedModule = std::make_shared<RidgedMulti>();
    ridgedModule->setFrequency(2.0);
    ridgedModule->setLacunarity(3.0);
    ridgedModule->setOctaveCount(10);
    mModules.push_back(ridgedModule);

	std::shared_ptr<Billow> billowModule = std::make_shared<Billow>();
    billowModule->setFrequency(2.0);
    billowModule->setLacunarity(3.5);
    billowModule->setOctaveCount(10);
    billowModule->setPersistence(0.2);
	mModules.push_back(billowModule);

	std::shared_ptr<Voronoi> voronoiModule = std::make_shared<Voronoi>();
	voronoiModule->setDisplacement(0.0);
	voronoiModule->setFrequency(10.0);
	voronoiModule->setSeed(20);
	voronoiModule->enableDistance(true);
	//mModules.push_back(voronoiModule);
	
	std::shared_ptr<Checkerboard> checkerboardModule = std::make_shared<Checkerboard>();
	checkerboardModule->setMinValue(-1.0);
	checkerboardModule->setMaxValue(1.0);
	checkerboardModule->setFrequency(200);
	checkerboardModule->setCoordsFactor(mHeight);
	mModules.push_back(checkerboardModule);

	std::shared_ptr<BlendSelector> blendSelectorModule = std::make_shared<BlendSelector>();
	//blendSelectorModule->getSourceModule(0, *ridgedModule);
	//blendSelectorModule->getSourceModule(1, *billowModule);
	blendSelectorModule->setControlModule(*checkerboardModule);
	mModules.push_back(blendSelectorModule);

}

std::shared_ptr<TerrainHandle> TerrainGenerator::generateTerrain()
{
	float xFrequency = 1;
	float yFrequency = 1;
	float xOffsetIncrement = 1 / mHeight;
	float yOffsetIncrement = 1 / mWidth;
    float xoff = 0; // Perlin noise needs values between 0 and 1
    float yoff = 0; // That's why we feed it small incremental values for our [x,y] matrix

    for (float y = 0; y < mHeight; y++)
    {
        xoff = 0;

        for (float x = 0; x < mWidth; x++)
        {
			double output = 0.0;

			output = mModules[3]->getValue(xoff, yoff, 0);

			/*for (std::shared_ptr<Module> it : mModules)
			{
				output += (float)it->GetValue(xoff, yoff, 0);
			}*/

			mTerrainHandle->setHeight(x, y, 200.f * output);
            xoff += xOffsetIncrement * xFrequency;
        }

        yoff += yOffsetIncrement * yFrequency;
    }

    mTerrainHandle->computeNormals();
    return mTerrainHandle;
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

const std::shared_ptr<TerrainHandle> TerrainGenerator::getHandle()
{
    return mTerrainHandle;
}
