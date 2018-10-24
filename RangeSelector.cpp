#include "interp.h"
#include "RangeSelector.h"

using namespace noise::module;

RangeSelector::RangeSelector()
	: Module(getSourceModuleCount())
	, mEdgeFalloff(DEFAULT_SELECT_EDGE_FALLOFF)
	, mLowerBound(DEFAULT_SELECT_LOWER_BOUND)
	, mUpperBound(DEFAULT_SELECT_UPPER_BOUND)
{
}

double RangeSelector::getValue(double x, double y, double z) const
{
	assert(mSourceModule[0] != NULL);
	assert(mSourceModule[1] != NULL);
	assert(mSourceModule[2] != NULL);

	double controlValue = mSourceModule[2]->GetValue(x, y, z);
	double alpha;

	if (mEdgeFalloff > 0.0)
	{
		if (controlValue < (mLowerBound - mEdgeFalloff))
		{
		    // The output value from the control module is below the selector
		    // threshold; return the output value from the first source module.
		    return mSourceModule[0]->GetValue(x, y, z);
		} 
		else if (controlValue < (mLowerBound + mEdgeFalloff))
		{
			// The output value from the control module is near the lower end of the
			// selector threshold and within the smooth curve. Interpolate between
			// the output values from the first and second source modules.
			double lowerCurve = (mLowerBound - mEdgeFalloff);
			double upperCurve = (mLowerBound + mEdgeFalloff);
			alpha = SCurve3((controlValue - lowerCurve) / (upperCurve - lowerCurve));
			return LinearInterp(mSourceModule[0]->GetValue(x, y, z), mSourceModule[1]->GetValue(x, y, z), alpha);
		}
		else if (controlValue < (mUpperBound - mEdgeFalloff))
		{
			// The output value from the control module is within the selector
			// threshold; return the output value from the second source module.
			return mSourceModule[1]->GetValue(x, y, z);
		}
		else if (controlValue < (mUpperBound + mEdgeFalloff))
		{
			// The output value from the control module is near the upper end of the
			// selector threshold and within the smooth curve. Interpolate between
			// the output values from the first and second source modules.
			double lowerCurve = (mUpperBound - mEdgeFalloff);
			double upperCurve = (mUpperBound + mEdgeFalloff);
			alpha = SCurve3((controlValue - lowerCurve) / (upperCurve - lowerCurve));
			return LinearInterp(mSourceModule[1]->GetValue(x, y, z), mSourceModule[0]->GetValue(x, y, z), alpha);
		}
		else
		{
			// Output value from the control module is above the selector threshold;
			// return the output value from the first source module.
			return mSourceModule[0]->GetValue(x, y, z);
		}
	}
	else
	{
		if (controlValue < mLowerBound || controlValue > mUpperBound)
		{
			return mSourceModule[0]->GetValue(x, y, z);
		}
		else
		{
			return mSourceModule[1]->GetValue(x, y, z);
		}
	}
}

void RangeSelector::getBounds(double lowerBound, double upperBound)
{
	assert (lowerBound < upperBound);

	mLowerBound = lowerBound;
	mUpperBound = upperBound;

	// Make sure that the edge falloff curves do not overlap.
	setEdgeFalloff(mEdgeFalloff);
}

void RangeSelector::setEdgeFalloff(double edgeFalloff)
{
	// Make sure that the edge falloff curves do not overlap.
	double boundSize = mUpperBound - mLowerBound;
	mEdgeFalloff = (edgeFalloff > boundSize / 2)? boundSize / 2: edgeFalloff;
}

const noise::module::Module& noise::module::RangeSelector::getControlModule() const
{
	if (mSourceModule == NULL || mSourceModule[2] == NULL) {
		throw noise::ExceptionNoModule();
	}

	return *(mSourceModule[2]);
}

double noise::module::RangeSelector::getEdgeFalloff() const
{
	return mEdgeFalloff;
}

double noise::module::RangeSelector::getLowerBound() const
{
	return mLowerBound;
}

int noise::module::RangeSelector::getSourceModuleCount() const
{
	return 3;
}

double noise::module::RangeSelector::getUpperBound() const
{
	return mUpperBound;
}

void noise::module::RangeSelector::setControlModule(const Module& controlModule)
{
	assert(mSourceModule != NULL);
	mSourceModule[2] = &controlModule;
}
