#include "Terrain.h"
#include "TerrainMesh.h"
#include "ImageLoader.h"
#include "PerlinGenerator.h"

#define HEIGHT_SHIFT 0.5f

Terrain::Terrain(float width, float height)
    : mWidth(width)
    , mHeight(height)
{
    mTerrainHandle = std::make_shared<TerrainHandle>(mWidth, mHeight);
}

std::shared_ptr<TerrainHandle> Terrain::loadTerrain(const char* filename, float height)
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

float Terrain::perlinLevel(std::shared_ptr<PerlinGenerator> generator, float heightScale, float xoff, float yoff,
                           float grid_scale, float octaves, float persistence)
{
    return (heightScale * generator->octavePerlin(xoff * grid_scale, yoff * grid_scale, 0, octaves, persistence) - HEIGHT_SHIFT);
}

std::shared_ptr<TerrainHandle> Terrain::generateTerrain()
{
    mTerrainHandle = std::make_shared<TerrainHandle>(mWidth, mHeight);

    std::shared_ptr<PerlinGenerator> mPerlinGenerator = std::make_shared<PerlinGenerator>(500);

    float frequency = 3; // hills frequency
    float offsetIncrement = 0.0001;
    float xoff = 0;
    float yoff = 0;

    for (float y = 0; y < mHeight; y++)
    {
        xoff = 0;

        for (float x = 0; x < mWidth; x++)
        {
            auto perlin = perlinLevel(mPerlinGenerator, 400, xoff, yoff, 1, 5, 2) +
                          perlinLevel(mPerlinGenerator, 30, xoff, yoff, 5, 5, 2) +
                          perlinLevel(mPerlinGenerator, 3, xoff, yoff, 30, 5, 2);

            mTerrainHandle->setHeight(x, y, perlin);
            xoff += offsetIncrement * frequency;
        }

        yoff += offsetIncrement * frequency;
    }


    mTerrainHandle->computeNormals();
    return mTerrainHandle;
}

const std::shared_ptr<TerrainHandle> Terrain::getHandle()
{
    return mTerrainHandle;
}
