#include "interp.h"
#include "misc.h"
#include "CurveMapper.h"

using namespace noise::module;

CurveMapper::CurveMapper()
	: Module(getSourceModuleCount ())
	, mControlPoints(NULL)
{
	mControlPointCount = 0;
}

CurveMapper::~CurveMapper()
{
	delete[] mControlPoints;
}

void CurveMapper::addControlPoint(double inputValue, double outputValue)
{
	// Find the insertion point for the new control point and insert the new
	// point at that position. The control point array will remain sorted by
	// input value. It does not matter which order these points are added.
	int insertionPos = findInsertionPos(inputValue);
	insertAtPos(insertionPos, inputValue, outputValue);
}

void CurveMapper::clearAllControlPoints()
{
	delete[] mControlPoints;
	mControlPoints = NULL;
	mControlPointCount = 0;
}

int CurveMapper::findInsertionPos(double inputValue)
{
	int insertionPos = 0;

	for (insertionPos = 0; insertionPos < mControlPointCount; insertionPos++)
	{
		if (inputValue < mControlPoints[insertionPos].inputValue)
		{
			// We found the array index in which to insert the new control point.
			// Exit now.
			break;
		} 
		else if (inputValue == mControlPoints[insertionPos].inputValue)
		{
			// Each control point is required to contain a unique input value, so
			// throw an exception.
			throw noise::ExceptionInvalidParam ();
		}
	}

	return insertionPos;
}

double CurveMapper::getValue(double x, double y, double z) const
{
	assert(mSourceModule[0] != NULL);
	assert(mControlPointCount >= 4);

	// Get the output value from the source module.
	double sourceModuleValue = mSourceModule[0]->getValue(x, y, z);

	// Find the first element in the control point array that has an input value
	// larger than the output value from the source module.
	int indexPos = 0;

	for (indexPos = 0; indexPos < mControlPointCount; indexPos++)
	{
		if (sourceModuleValue < mControlPoints[indexPos].inputValue)
		{
			break;
		}
	}

	// Find the four nearest control points so that we can perform cubic
	// interpolation.
	int index0 = ClampValue(indexPos - 2, 0, mControlPointCount - 1);
	int index1 = ClampValue(indexPos - 1, 0, mControlPointCount - 1);
	int index2 = ClampValue(indexPos    , 0, mControlPointCount - 1);
	int index3 = ClampValue(indexPos + 1, 0, mControlPointCount - 1);

	// If some control points are missing (which occurs if the value from the
	// source module is greater than the largest input value or less than the
	// smallest input value of the control point array), get the corresponding
	// output value of the nearest control point and exit now.
	if (index1 == index2)
	{
		return mControlPoints[index1].outputValue;
	}
	
	// Compute the alpha value used for cubic interpolation.
	double input0 = mControlPoints[index1].inputValue;
	double input1 = mControlPoints[index2].inputValue;
	double alpha = (sourceModuleValue - input0) / (input1 - input0);

	// Now perform the cubic interpolation given the alpha value.
	return CubicInterp( mControlPoints[index0].outputValue,
						mControlPoints[index1].outputValue,
						mControlPoints[index2].outputValue,
						mControlPoints[index3].outputValue,
						alpha);
}

void CurveMapper::insertAtPos(int insertionPos, double inputValue, double outputValue)
{
	// Make room for the new control point at the specified position within the
	// control point array.  The position is determined by the input value of
	// the control point; the control points must be sorted by input value
	// within that array.
	ControlPoint* newControlPoints = new ControlPoint[mControlPointCount + 1];

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
	
	// Now that we've made room for the new control point within the array, add
	// the new control point.
	mControlPoints[insertionPos].inputValue  = inputValue;
	mControlPoints[insertionPos].outputValue = outputValue;
}

const ControlPoint* CurveMapper::getControlPointArray() const
{
	return mControlPoints;
}

int CurveMapper::getControlPointCount() const
{
	return mControlPointCount;
}

int CurveMapper::getSourceModuleCount() const
{
	return 1;
}
