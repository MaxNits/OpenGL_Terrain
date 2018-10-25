#ifndef NOISE_MODULE_CURVE_H
#define NOISE_MODULE_CURVE_H

#include "Module.h"

namespace noise
{
namespace module
{

struct ControlPoint
{
  double inputValue;
  double outputValue;
};

// Noise module that maps the output value from a source module onto an
// arbitrary function curve.
// Since this curve is a cubic spline, an application must add a minimum
// of four control points to the curve.  If this is not done, the
// GetValue() method fails.

class CurveMapper: public Module
{
public:
    CurveMapper ();

	~CurveMapper ();

	virtual int getSourceModuleCount() const override;

	virtual double getValue(double x, double y, double z) const override;
    
    void addControlPoint(double inputValue, double outputValue);

    void clearAllControlPoints();

    const ControlPoint* getControlPointArray() const;

	int getControlPointCount() const;

protected:
    int findInsertionPos(double inputValue);

    void insertAtPos(int insertionPos, double inputValue, double outputValue);

    ControlPoint* mControlPoints;
	int mControlPointCount;
};

} // namespace module
} // namespace noise

#endif
