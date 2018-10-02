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

	virtual int GetSourceModuleCount() const override;

	virtual double GetValue(double x, double y, double z) const override;
    
    void AddControlPoint(double inputValue, double outputValue);

    void ClearAllControlPoints();

    const ControlPoint* GetControlPointArray() const;

	int GetControlPointCount() const;

protected:
    int FindInsertionPos(double inputValue);

    void InsertAtPos(int insertionPos, double inputValue, double outputValue);

    int mControlPointCount;
    ControlPoint* mControlPoints;
};

} // namespace module
} // namespace noise

#endif
