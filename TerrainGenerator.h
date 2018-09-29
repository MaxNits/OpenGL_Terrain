#pragma once

#include "Module.h"

#include <memory>
#include <vector>

class TerrainHandle;

class TerrainGenerator
{
public:
    TerrainGenerator(float width, float height);

    std::shared_ptr<TerrainHandle> loadTerrain(const char* filename, float height);

    std::shared_ptr<TerrainHandle> generateTerrain();

    const std::shared_ptr<TerrainHandle> getHandle();

private:
    std::shared_ptr<TerrainHandle> mTerrainHandle;

    std::vector<std::shared_ptr<noise::module::Module> > mModules;

    float mWidth;
    float mHeight;
};
