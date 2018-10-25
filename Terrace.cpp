#include "interp.h"
#include "misc.h"
#include "Terrace.h"

using namespace noise::module;
using namespace noise;

Terrace::Terrace()
	:  Module (getSourceModuleCount())
	, mControlPointCount (0)
	, mInvertTerraces (false)
	, mControlPoints (NULL)
{
}

Terrace::~Terrace()
{
	delete[] mControlPoints;
}

void Terrace::addControlPoint(double value)
{
	// Find the insertion point for the new control point and insert the new
	// point at that position.  The control point array will remain sorted by
	// value.
	int insertionPos = findInsertionPos(value);
	insertAtPos(insertionPos, value);
}

void Terrace::clearAllControlPoints()
{
	delete[] mControlPoints;
	mControlPoints = NULL;
	mControlPointCount = 0;
}

int Terrace::findInsertionPos(double value)
{
	int insertionPos;
	for (insertionPos = 0; insertionPos < mControlPointCount; insertionPos++)
	{
		if (value < mControlPoints[insertionPos])
		{
			// We found the array index in which to insert the new control point.
			// Exit now.
			break;
		} 
		else if (value == mControlPoints[insertionPos])
		{
			// Each control point is required to contain a unique value, so throw
			// an exception.
			throw noise::ExceptionInvalidParam ();
		}
	}

	return insertionPos;
}

double Terrace::getValue(double x, double y, double z) const
{
	assert (m_pSourceModule[0] != NULL);
	assert (mControlPointCount >= 2);

	// Get the output value from the source module.
	double sourceModuleValue = mSourceModule[0]->getValue (x, y, z);

	// Find the first element in the control point array that has a value
	// larger than the output value from the source module.
	int indexPos;
	for (indexPos = 0; indexPos < mControlPointCount; indexPos++)
	{
		if (sourceModuleValue < mControlPoints[indexPos]) {
			break;
		}
	}

	// Find the two nearest control points so that we can map their values
	// onto a quadratic curve.
	int index0 = ClampValue (indexPos - 1, 0, mControlPointCount - 1);
	int index1 = ClampValue (indexPos    , 0, mControlPointCount - 1);

	// If some control points are missing (which occurs if the output value from
	// the source module is greater than the largest value or less than the
	// smallest value of the control point array), get the value of the nearest
	// control point and exit now.
	if (index0 == index1)
	{
		return mControlPoints[index1];
	}

	// Compute the alpha value used for linear interpolation.
	double value0 = mControlPoints[index0];
	double value1 = mControlPoints[index1];
	double alpha = (sourceModuleValue - value0) / (value1 - value0);
	if (mInvertTerraces)
	{
		alpha = 1.0 - alpha;
		SwapValues (value0, value1);
	}

	// Squaring the alpha produces the terrace effect.
	alpha *= alpha;

	// Now perform the linear interpolation given the alpha value.
	return LinearInterp (value0, value1, alpha);
}

void Terrace::insertAtPos(int insertionPos, double value)
{
	// Make room for the new control point at the specified position within
	// the control point array.  The position is determined by the value of
	// the control point; the control points must be sorted by value within
	// that array.
	double* newControlPoints = new double[mControlPointCount + 1];

	for (int i = 0; i < mControlPointCount; i++)
	{
		if (i < insertionPos)
		{
			newControlPoints[i] = mControlPoints[i];
		} 
		else
		{
			newControlPoints[i + 1] = mControlPoints[i];
		}
	}

	delete[] mControlPoints;
	mControlPoints = newControlPoints;
	++mControlPointCount;

	// Now that we've made room for the new control point within the array,
	// add the new control point.
	mControlPoints[insertionPos] = value;
}

void Terrace::makeControlPoints(int controlPointCount)
{
	if (controlPointCount < 2)
	{
		throw noise::ExceptionInvalidParam ();
	}

	clearAllControlPoints();

	double terraceStep = 2.0 / ((double)controlPointCount - 1.0);
	double curValue = -1.0;

	for (int i = 0; i < (int)controlPointCount; i++) 
	{
		addControlPoint (curValue);
		curValue += terraceStep;
	}
}

const double* Terrace::getControlPointArray() const
{
	return mControlPoints;
}

int Terrace::getControlPointCount() const
{
	return mControlPointCount;
}

int Terrace::getSourceModuleCount() const
{
	return 1;
}

void Terrace::invertTerraces(bool invert /*= true*/)
{
	mInvertTerraces = invert;
}

bool Terrace::isTerracesInverted() const
{
	return mInvertTerraces;
}
