#pragma once

class Vec3f;

class PerlinGenerator
{
public:
    PerlinGenerator(); // remove this

    PerlinGenerator(unsigned repeatInterval);

    float fade(float t);

    int increment(int num);

    float gradient(int hash, float x, float y, float z);

    float lerp(float a, float b, float x);

    float perlin(float x, float y, float z);

    float octavePerlin(float x, float y, float z, int octaves, float persistence);

private:
    int mPermutation[512];

    unsigned mRepeatInterval;
};
