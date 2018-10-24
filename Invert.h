#ifndef NOISE_MODULE_INVERT_H
#define NOISE_MODULE_INVERT_H

#include "Module.h"

namespace noise
{
namespace module
{

class Invert: public Module
{
public:
    Invert();

    virtual int getSourceModuleCount() const override;

    virtual double getValue(double x, double y, double z) const override;
};

} // namespace module
} // namespace noise

#endif
