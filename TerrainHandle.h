#pragma once

#include "PerlinDevice.h"

#include <vector>

class Vec3f;

class TerrainHandle
{
public:
    TerrainHandle(unsigned width, unsigned length);

    ~TerrainHandle();

    void setHeight(unsigned x, unsigned z, float y);

	void resizeTerrain(unsigned width, unsigned length);

    float getHeight(unsigned x, unsigned z);

    unsigned getWidth();

    unsigned getLength();

    void computeNormals();

    Vec3f getNormal(unsigned x, unsigned z);

private:
	Vec3f** mNormals;
	float** mHeights;

    unsigned mTerrainWidth;
    unsigned mTerrainLength;
    bool mNormalsComputed;
};
