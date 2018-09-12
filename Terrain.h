#pragma once
#include <memory>
#include <vector>

class TerrainHandle;
class PerlinDevice;

class Terrain
{
public:
    Terrain(float width, float height);

    std::shared_ptr<TerrainHandle> loadTerrain(const char* filename, float height);

    float perlinLevel(std::shared_ptr<PerlinDevice> generator, float heightScale, float xoff, float yoff, float grid_scale, float octaves, float persistence);

    std::shared_ptr<TerrainHandle> generateTerrain();

    const std::shared_ptr<TerrainHandle> getHandle();

private:
    std::shared_ptr<TerrainHandle> mTerrainHandle;

    //std::vector<std::shared_ptr<Generator> > mGenerators;

    float mWidth;
    float mHeight;
};
