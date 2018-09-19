#ifndef NOISE_EXCEPTION_H
#define NOISE_EXCEPTION_H

#include <iostream>

namespace noise
{

  /// @addtogroup libnoise
  /// @{

  /// Abstract base class for libnoise exceptions
  class Exception : public std::exception
  {
  public:
	  Exception() {}
	  virtual ~Exception() {}

	  virtual const char* what() const noexcept override { return ""; }
  };

  /// Invalid parameter exception
  ///
  /// An invalid parameter was passed to a libnoise function or method.
  class ExceptionInvalidParam: public Exception
  {
  public:
	  ExceptionInvalidParam() {
	      _msg = "An invalid parameter was passed to a libnoise function or method.\n";
	  }

	  virtual const char* what() const noexcept override
	  {
		  return _msg.c_str();
	  }
  private:
	  std::string _msg;
  };

  /// No module exception
  ///
  /// Could not retrieve a source module from a noise module.
  ///
  /// @note If one or more required source modules were not connected to a
  /// specific noise module, and its GetValue() method was called, that
  /// method will raise a debug assertion instead of this exception.  This
  /// is done for performance reasons.
  class ExceptionNoModule: public Exception
  {
  };

  /// Out of memory exception
  ///
  /// There was not enough memory to perform an action.
  class ExceptionOutOfMemory: public Exception
  {
  };

  /// Unknown exception
  ///
  /// libnoise raised an unknown exception.
  class ExceptionUnknown: public Exception
  {
  };

  /// @}

}

#endif
