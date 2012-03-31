/*
  Copyright (C) 1988,1999,2000,2001  Franz Josef Och (RWTH Aachen - Lehrstuhl fuer Informatik VI)

  This file is part of GIZA++ ( extension of GIZA).

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
  USA.
*/

#ifndef GIZAPP_UTIL_FLEXARRAY_H_
#define GIZAPP_UTIL_FLEXARRAY_H_

#include "util/array.h"
#include <ostream>

template <class T>
class FlexArray {
 private:
  Array<T> array_;
  int start_, end_;

 public:
  FlexArray(int start = 0, int end = -1)
      : array_(end - start + 1), start_(start), end_(end) {}
  FlexArray(int start, int end, const T& init)
      : array_(end - start + 1, init), start_(start), end_(end) {}
  ~FlexArray() {}

  T& operator[](int i) { return array_[i - start_]; }

  const T& operator[](int i) const { return array_[i - start_]; }

  int low() const { return start_; }
  int high() const { return end_; }

  T* begin() { return conv<double>(array_.begin()); }
  T* end() { return conv<double>(array_.end()); }
};

template <class T>
inline std::ostream& operator<<(std::ostream& out, const FlexArray<T>& x) {
  for (int i = x.low(); i <= x.high(); ++i) {
    out << i << ':' << x[i] << ';' << ' ';
  }
  return out;
}

#endif  // GIZAPP_UTIL_FLEXARRAY_H_
