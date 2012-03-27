/*
  EGYPT Toolkit for Statistical Machine Translation

  Written by Yaser Al-Onaizan, Jan Curin, Michael Jahr, Kevin Knight, John Lafferty, Dan Melamed, David Purdy, Franz Och, Noah Smith, and David Yarowsky.

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

/*
  Alignment: 'checked' Alignment representation with automatic calculation
  of fertilities
  Franz Josef Och (30/07/99)
*/

#include "alignment.h"

Alignment::Alignment() {}
Alignment::Alignment(PositionIndex _l, PositionIndex _m)
    : a(_m+1, 0),
      positionSum(_l+1, 0), f(_l+1, 0),
      als_i(_l+1,0), als_j(_m+1), l(_l), m(_m) {
  Init();
}

Alignment::~Alignment() {}

void Alignment::Init() {
  f[0] = m;
  for (PositionIndex j = 1; j <= m; ++j) {
    if (j > 1) als_j[j].prev = j - 1;
    if (j < m) als_j[j].next = j + 1;
  }
  als_i[0] = 1;
}

std::ostream&operator<<(std::ostream& out, const Alignment& a) {
  const int m = a.a.size() - 1;
  const int l = a.f.size() - 1;

  out << "AL(l:" << l << ",m:" << m << ")(a: ";

  for (int j = 1; j <= m; j++) {
    out << a(j) << ' ';
  }
  out << ")(fert: ";
  for (int i = 0; i <= l; i++) {
    out << a.fert(i) << ' ';
  }
  return out << ")  c:" << "\n";
}
