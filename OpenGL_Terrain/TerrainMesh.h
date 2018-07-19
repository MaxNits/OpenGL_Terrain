#pragma once

#include "PerlinGenerator.h"

#include <vector>

class Vec3f;

class TerrainHandle
{
public:
    TerrainHandle(unsigned width, unsigned length);

    ~TerrainHandle();

    void setHeight(unsigned x, unsigned z, float y);

    float getHeight(unsigned x, unsigned z);

    unsigned getWidth();

    unsigned getLength();

    void computeNormals();

    Vec3f getNormal(unsigned x, unsigned z);

private:
    Vec3f** mNormals;
    unsigned mTerrainWidth;
    unsigned mTerrainLength;
    float** mHeights;
    bool mNormalsComputed;
};
