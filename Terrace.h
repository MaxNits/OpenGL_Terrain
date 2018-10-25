#ifndef NOISE_MODULE_TERRACE_H
#define NOISE_MODULE_TERRACE_H

#include "Module.h"

namespace noise
{
namespace module
{

class Terrace: public Module
{
public:
	Terrace();

	~Terrace();

	virtual int getSourceModuleCount() const override;

	virtual double getValue(double x, double y, double z) const override;
	
	void addControlPoint(double value);
	
	void clearAllControlPoints();
	
	const double* getControlPointArray() const;
	
	int getControlPointCount() const;
	
	void invertTerraces(bool invert = true);
	
	bool isTerracesInverted() const;
   
    void makeControlPoints(int controlPointCount);

protected:
	int findInsertionPos(double value);

	void insertAtPos(int insertionPos, double value);

	int mControlPointCount;
	bool mInvertTerraces;
	double* mControlPoints;
};

} // namespace module
} // namespace noise

#endif
