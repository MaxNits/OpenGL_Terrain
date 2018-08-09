#include "RidgedDevice.h"
#include <math.h>

RidgedDevice::RidgedDevice()
{

}

float RidgedDevice::ridgeNoice(float x, float y, float height)
{
    return (2*(0.5 - fabs(0.5 - height)));
}

float RidgedDevice::generateRidged(float x, float y)
{

}
