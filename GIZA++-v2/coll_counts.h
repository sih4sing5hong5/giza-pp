/*
  Copyright (C) 1999,2000,2001  Franz Josef Och (RWTH Aachen - Lehrstuhl fuer Informatik VI)

  This file is part of GIZA++ ( extension of GIZA ).

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

#ifndef GIZAPP_COLL_COUNTS_H_
#define GIZAPP_COLL_COUNTS_H_

#include <set>
#include <ostream>
#include <utility>

#include "defs.h"
#include "util/vector.h"
// #include "transpair_model3.h"
// #include "transpair_model4.h"

class alignment;
class LogProb;

template <class T> class MoveSwapMatrix;
template <class T> class AModel;
template <class T> class nmodel;
template <class COUNT, class PROB> class tmodel;

class OneMoveSwap {
 public:
  short type;
  short a, b;

  OneMoveSwap(short _type,short _a,short _b)
    : type(_type), a(_a), b(_b) {}

  // TODO: how about initialization a and b?
  OneMoveSwap() : type(0) {}
  ~OneMoveSwap() {}
};

inline bool operator<(const OneMoveSwap& a, const OneMoveSwap& b) {
  if (a.type < b.type) return 1;
  else if (b.type<a.type) return 0;
  else if (a.a<b.a) return 1;
  else if (b.a<a.a) return 0;
  else return a.b < b.b;
}

inline bool operator==(const OneMoveSwap& a, const OneMoveSwap& b) {
  return a.type == b.type && a.a == b.a &&a .b ==b .b;
}

inline std::ostream& operator<<(std::ostream& out, const OneMoveSwap&o) {
  return out << '(' << o.type << "," << o.a << "," << o.b << ")";
}

inline std::ostream& operator<<(std::ostream& out, const std::set<OneMoveSwap>& s) {
  for(std::set<OneMoveSwap>::const_iterator it = s.begin();
      it != s.end(); ++it)
    cout << *it << ' ';
  return out;
}

bool makeOneMoveSwap(const alignment& a,
                     const alignment& b,
                     std::set<OneMoveSwap>& oms);

// TODO: Need refactoring. this function requires too arguments.
template<class TRANSPAIR,class MODEL>
int collectCountsOverNeighborhood(const Vector<std::pair<MoveSwapMatrix<TRANSPAIR>*,LogProb> >&smsc,
                                  Vector<WordIndex>&es,
                                  Vector<WordIndex>&fs,
                                  tmodel<COUNT,PROB>& tTable,
                                  AModel<COUNT>& aCountTable, AModel<COUNT>& dCountTable,
                                  nmodel<COUNT>& nCountTable, double& p1count,
                                  double& p0count,
                                  LogProb& _total,
                                  float count,
                                  bool addCounts, MODEL* d4Table = 0);

#endif  // GIZAPP_COLL_COUNTS_H_
