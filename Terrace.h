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
	
	void AddControlPoint (double value);
	
	void ClearAllControlPoints();
	
	const double* GetControlPointArray() const;
	
	int GetControlPointCount() const;
	
	void InvertTerraces(bool invert = true);
	
	bool IsTerracesInverted() const;
   
    void MakeControlPoints(int controlPointCount);

protected:
	int FindInsertionPos(double value);
	void InsertAtPos(int insertionPos, double value);

	int m_controlPointCount;
	bool m_invertTerraces;
	double* m_pControlPoints;
};

} // namespace module
} // namespace noise

#endif
