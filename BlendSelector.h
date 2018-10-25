#ifndef NOISE_MODULE_BLEND_H
#define NOISE_MODULE_BLEND_H

#include "Module.h"

namespace noise
{
namespace module
{

class BlendSelector: public Module
{
public:
    BlendSelector();

	virtual int getSourceModuleCount() const override;

	virtual double getValue(double x, double y, double z) const override;

	const Module& getControlModule() const;

    void setControlModule(const Module& controlModule);
};

} // namespace module
} // namespace noise

#endif
