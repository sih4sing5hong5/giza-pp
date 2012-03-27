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
  MoveSwapMatrix: Efficient representation for moving and swapping
  around in IBM3 training.
  Franz Josef Och (30/07/99)
*/

#ifndef GIZAPP_MOVE_SWAP_MATRIX_H_
#define GIZAPP_MOVE_SWAP_MATRIX_H_

#include "alignment.h"
#include "util/array2.h"

extern short DoViterbiTraining;

template<class TRANSPAIR>
class MoveSwapMatrix : public Alignment {
 private:
  const TRANSPAIR&ef;
  const WordIndex l, m;
  Array2<LogProb, Vector<LogProb> > _cmove, _cswap;
  Array2<char,Vector<char> > delmove,delswap;
  Vector<int> changed;
  int changedCounter;
  const int modelnr;
  bool lazyEvaluation;
  bool centerDeleted;

 public:
  MoveSwapMatrix(const TRANSPAIR&_ef, const Alignment&_a);
  ~MoveSwapMatrix();

  bool check() const { return 1; }

  const TRANSPAIR& get_ef() const { return ef; }

  bool isCenterDeleted() const { return centerDeleted; }
  bool isLazy()const { return lazyEvaluation; }

  void updateJ(WordIndex j, bool,double thisValue);
  void updateI(WordIndex i, double thisValue);
  void doMove(WordIndex _i, WordIndex _j);
  void doSwap(WordIndex _j1, WordIndex _j2);

  void delCenter() { centerDeleted = 1; }
  void delMove(WordIndex x, WordIndex y) { delmove(x,y) = 1; }
  void delSwap(WordIndex x, WordIndex y) {
    MASSERT(y>x);
    delswap(x,y)=1;
    delswap(y,x)=1;
  }

  bool isDelMove(WordIndex x, WordIndex y) const {
    return DoViterbiTraining||delmove(x,y);
  }

  bool isDelSwap(WordIndex x, WordIndex y) const {
    MASSERT(y>x);
    return DoViterbiTraining||delswap(x,y);
  }

  LogProb cmove(WordIndex x, WordIndex y) const {
    MASSERT( get_al(y)!=x );
    MASSERT( delmove(x,y)==0 );
    if (lazyEvaluation ) {
      return ef.scoreOfMove(*this,x,y);
    } else {
      return _cmove(x, y);
    }
  }

  LogProb cswap(WordIndex x, WordIndex y) const {
    MASSERT(x<y);
    MASSERT(delswap(x,y)==0);
    MASSERT(get_al(x)!=get_al(y));
    if (lazyEvaluation) {
      return ef.scoreOfSwap(*this,x,y);
    } else {
      MASSERT(y>x);
      return _cswap(x, y);
    }
  }

  void printWrongs() const;
  bool isRight() const;
  friend ostream&operator<<(ostream&out, const MoveSwapMatrix<TRANSPAIR>&m) {
    // TODO: fix C-style cast.
    return out << (Alignment)m << "\nEF:\n"<< m.ef << "\nCMOVE\n"
               <<m._cmove << "\nCSWAP\n" << m._cswap << endl;
  }
};

#endif  // GIZAPP_MOVE_SWAP_MATRIX_H_
