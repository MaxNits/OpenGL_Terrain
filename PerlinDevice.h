#pragma once

class Vec3f;

class PerlinDevice
{
public:
    PerlinDevice(); // remove this

    PerlinDevice(unsigned repeatInterval);

    float perlin(float x, float y, float z);

    float octavePerlin(float x, float y, float z, int octaves, float persistence);

private:
    float fade(float t);

    int increment(int num); // increment with repeat

    float gradient(int hash, float x, float y, float z);

    float lerp(float a, float b, float x);

    int mPermutation[512];
    unsigned mRepeatInterval;
};
