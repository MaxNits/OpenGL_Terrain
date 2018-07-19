#pragma once
#include <memory>

class TerrainHandle;
class PerlinGenerator;

class Terrain
{
public:
    Terrain(float width, float height);

    std::shared_ptr<TerrainHandle> loadTerrain(const char* filename, float height);

    float perlinLevel(std::shared_ptr<PerlinGenerator> generator, float heightScale, float xoff, float yoff, float grid_scale, float octaves, float persistence);

    std::shared_ptr<TerrainHandle> generateTerrain();

    const std::shared_ptr<TerrainHandle> getHandle();

private:
    std::shared_ptr<TerrainHandle> mTerrainHandle;

    float mWidth;
    float mHeight;
};
