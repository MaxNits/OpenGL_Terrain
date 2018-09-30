#ifndef NOISE_MISC_H
#define NOISE_MISC_H

namespace noise
{

  /// Clamps a value onto a clamping range.
  ///
  /// @param value The value to clamp.
  /// @param lowerBound The lower bound of the clamping range.
  /// @param upperBound The upper bound of the clamping range.
  ///
  /// @returns
  /// - @a value if @a value lies between @a lowerBound and @a upperBound.
  /// - @a lowerBound if @a value is less than @a lowerBound.
  /// - @a upperBound if @a value is greater than @a upperBound.
  ///
  /// This function does not modify any parameters.
  inline int ClampValue (int value, int lowerBound, int upperBound)
  {
    if (value < lowerBound) {
      return lowerBound;
    } else if (value > upperBound) {
      return upperBound;
    } else {
      return value;
    }
  }

  /// @addtogroup libnoise
  /// @{

  /// Returns the maximum of two values.
  ///
  /// @param a The first value.
  /// @param b The second value.
  ///
  /// @returns The maximum of the two values.
  template <class T>
  T GetMax (const T& a, const T& b)
  {
    return (a > b? a: b);
  }

  /// Returns the minimum of two values.
  ///
  /// @param a The first value.
  /// @param b The second value.
  ///
  /// @returns The minimum of the two values.
  template <class T>
  T GetMin (const T& a, const T& b)
  {
    return (a < b? a: b);
  }

  /// Swaps two values.
  ///
  /// @param a A variable containing the first value.
  /// @param b A variable containing the second value.
  ///
  /// @post The values within the the two variables are swapped.
  template <class T>
  void SwapValues (T& a, T& b)
  {
    T c = a;
    a = b;
    b = c;
  }

  /// @}

}

#endif
