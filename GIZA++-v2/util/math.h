/*
  Copyright 1998 (c) by RWTH Aachen - Lehrstuhl fuer Informatik VI
  Franz Josef Och
*/

#ifndef GIZAPP_UTIL_MATH_H_
#define GIZAPP_UTIL_MATH_H_

namespace util {
inline double mfabs(double x) { return (x < 0.0) ? (-x) :x; }
} // namespace util

#endif  // GIZAPP_UTIL_MATH_H_
