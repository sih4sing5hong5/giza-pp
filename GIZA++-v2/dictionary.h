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
  Noah A. Smith
  Dictionary object for dictionary filter in Model 1 training

  9 August 1999
*/

#ifndef GIZAPP_UTIL_DICTIONARY_H_
#define GIZAPP_UTIL_DICTIONARY_H_

#include "util/vector.h"

namespace util {

class Dictionary {
 public:
  explicit Dictionary(const char* filename);
  Dictionary();
  ~Dictionary();

  bool Open(const char* filename);
  bool indict(int, int);

  bool IsOK() const { return !is_dead_; }

 private:
  bool is_dead_;
  int cur_val_;
  int cur_index_min_;
  int cur_index_max_;
  Vector<int> pairs_[2];
};
} // namespace util

#endif  // GIZAPP_UTIL_DICTIONARY_H_
