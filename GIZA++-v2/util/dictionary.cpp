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

  Dictionary file must be in order (sorted) by Foreign vocab id, but English
  vocab ids may be in any order.

  9 August 1999
*/

#include "util/dictionary.h"

#include <iostream>
#include <fstream>
#include <cstring>

namespace util {

Dictionary::Dictionary()
    : is_dead_(false), cur_val_(0), cur_index_min_(0), cur_index_max_(0) {}

Dictionary::Dictionary(const char *filename)
    : is_dead_(false), cur_val_(0), cur_index_min_(0), cur_index_max_(0) {
  if (!Open(filename)) {
    std::cerr << "Failed to open "  << filename << std::endl;
    std::exit(1);
  }
}

Dictionary::~Dictionary() {}

bool Dictionary::Open(const char* filename) {
  if (!std::strcmp(filename, "")) {
    is_dead_ = true;
    return false;
  }
  std::cout << "Reading dictionary from:  " << filename << '\n';
  std::ifstream ifs(filename);
  if (!ifs) {
    std::cerr << "ERROR: Can't open dictionary: " << filename << '\n';
    return false;
  }

  int p, q;
  while ((ifs >> p >> q)) {
    pairs_[0].push_back(p);
    pairs_[1].push_back(q);
  }
  std::cout << "Dictionary read; " << pairs_[0].size() << " pairs loaded." << '\n';
  ifs.close();
  return true;
}

bool Dictionary::indict(int p, int q) {
  if (is_dead_) return false;
  if (p == 0 && q == 0) return false;

  if (cur_val_ == p) {
    for (int i = cur_index_min_; i <= cur_index_max_; i++)
      if (pairs_[1][i] == q) return true;
    return false;
  } else{
    int begin = 0, end = pairs_[0].size() - 1, middle = 0;
    unsigned int t;
    bool ret = false;
    while (begin <= end) {
      middle = begin + ((end - begin) >> 1);
      if (p < pairs_[0][middle]) {
        end = middle - 1;
      } else if (p > pairs_[0][middle]) {
        begin = middle + 1;
      } else {
        break;
      }
    }
    t = middle;
    while (pairs_[0][t] == p) {
      if (pairs_[1][t--] == q) ret = true;
    }
    cur_index_min_ = t + 1;
    t = middle + 1;
    while (pairs_[0][t] == p && t < pairs_[0].size()) {
      if (pairs_[1][t++] == q) ret = true;
    }
    cur_index_max_ = t - 1;
    cur_val_ = p;
    return ret;
  }
}

} // namespace util
