#include "TerrainMesh.h"
#include "Vec3f.h"

#include <iostream>
#include <chrono>

TerrainMesh::TerrainMesh(unsigned width, unsigned length)
    : mTerrainWidth(width)
    , mTerrainLength(length)
{
    mHeights = new float*[length];
    for (int i = 0; i < length; i++)
    {
        mHeights[i] = new float[width];
    }

    mNormals = new Vec3f*[length];
    for (int i = 0; i < length; i++)
    {
        mNormals[i] = new Vec3f[width];
    }

    mNormalsComputed = false;
}

TerrainMesh::~TerrainMesh()
{
    for (int i = 0; i < mTerrainLength; i++)
    {
        delete[] mHeights[i];
    }
    delete[] mHeights;

    for (int i = 0; i < mTerrainLength; i++)
    {
        delete[] mNormals[i];
    }
    delete[] mNormals;
}

void TerrainMesh::setHeight(unsigned x, unsigned z, float y)
{
    mHeights[x][z] = y;
    mNormalsComputed = false;
}

float TerrainMesh::getHeight(unsigned x, unsigned z)
{
    return mHeights[x][z];
}

unsigned TerrainMesh::getWidth()
{
    return mTerrainWidth;
}

unsigned TerrainMesh::getLength()
{
    return mTerrainLength;
}

void TerrainMesh::computeNormals()
{
    if (mNormalsComputed)
    {
        std::cout << "Normals are already computed." << std::endl;
        return;
    }

    // Compute the rough version of the normals
    Vec3f** normals_temp = new Vec3f*[mTerrainLength];
    for (int i = 0; i < mTerrainLength; i++)
    {
        normals_temp[i] = new Vec3f[mTerrainWidth];
    }

    for (int z = 0; z < mTerrainLength; z++)
    {
        for (int x = 0; x < mTerrainWidth; x++)
        {
            Vec3f sum(0.0f, 0.0f, 0.0f);

            Vec3f out;
            if (z > 0)
            {
                out = Vec3f(0.0f, mHeights[z - 1][x] - mHeights[z][x], -1.0f);
            }

            Vec3f in;
            if (z < mTerrainLength - 1)
            {
                in = Vec3f(0.0f, mHeights[z + 1][x] - mHeights[z][x], 1.0f);
            }

            Vec3f left;
            if (x > 0)
            {
                left = Vec3f(-1.0f, mHeights[z][x - 1] - mHeights[z][x], 0.0f);
            }

            Vec3f right;
            if (x < mTerrainWidth - 1)
            {
                right = Vec3f(1.0f, mHeights[z][x + 1] - mHeights[z][x], 0.0f);
            }

            if (x > 0 && z > 0)
            {
                sum += out.cross(left).normilize();
            }
            if (x > 0 && z < mTerrainLength - 1)
            {
                sum += left.cross(in).normilize();
            }
            if (x < mTerrainWidth - 1 && z < mTerrainLength - 1)
            {
                sum += in.cross(right).normilize();
            }
            if (x < mTerrainWidth - 1 && z > 0)
            {
                sum += right.cross(out).normilize();
            }

            normals_temp[z][x] = sum;
        }
    }

    // Smooth out the normals
    const float FALLOUT_RATIO = 0.5f;
    for (int z = 0; z < mTerrainLength; z++)
    {
        for (int x = 0; x < mTerrainWidth; x++)
        {
            Vec3f sum = normals_temp[z][x];

            if (x > 0)
            {
                sum += normals_temp[z][x - 1] * FALLOUT_RATIO;
            }
            if (x < mTerrainWidth - 1)
            {
                sum += normals_temp[z][x + 1] * FALLOUT_RATIO;
            }
            if (z > 0)
            {
                sum += normals_temp[z - 1][x] * FALLOUT_RATIO;
            }
            if (z < mTerrainLength - 1)
            {
                sum += normals_temp[z + 1][x] * FALLOUT_RATIO;
            }

            if (sum.magnitude() == 0)
            {
                sum = Vec3f(0.0f, 1.0f, 0.0f);
            }

            mNormals[z][x] = sum.normilize();
        }
    }

    for (int i = 0; i < mTerrainLength; i++) {
        delete[] normals_temp[i];
    }
    delete[] normals_temp;

    mNormalsComputed = true;
}

Vec3f TerrainMesh::getNormal(unsigned x, unsigned z)
{
    if (!mNormalsComputed)
    {
        computeNormals();
    }

    return mNormals[x][z];
}
