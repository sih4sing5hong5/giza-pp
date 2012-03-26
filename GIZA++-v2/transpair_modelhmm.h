/*
  Copyright (C) 2000,2001  Franz Josef Och (RWTH Aachen - Lehrstuhl fuer Informatik VI)

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

#ifndef GIZAPP_TRANSPAIR_MODELHMM_H_
#define GIZAPP_TRANSPAIR_MODELHMM_H_

#include "defs.h"
#include "util/array2.h"
#include "util/vector.h"
#include "ntables.h"
#include "atables.h"
#include "ttables.h"
#include "alignment.h"
#include <cmath>
#include "transpair_model2.h"
#include "hmm.h"

class HMMNetwork;

class TransPairModelHMM : public transpair_model2
{
 private:
  HMMNetwork* network_;

 public:
  // TODO: make sure this.
  typedef TransPairModelHMM simpler_transpair_model;

  TransPairModelHMM(const Vector<WordIndex>& es,
                    const Vector<WordIndex>& fs,
                    const TModel<COUNT, PROB>& tTable,
                    const AModel<PROB>&aTable,
                    const AModel<PROB>&,const nmodel<PROB>&,
                    double, double, const HMM* h);
  ~TransPairModelHMM();

  const HMMNetwork* GetHMMNetwork() const { return network_; }
  HMMNetwork* mutable_HMMNetwork() { return network_; }

  int modelnr() const { return 6; }

  LogProb scoreOfMove(const alignment&a, WordIndex _new_i, WordIndex j,double f=-1.0) const;

  LogProb scoreOfAlignmentForChange(const alignment&) const { return -1.0; }

  LogProb scoreOfSwap(const alignment&a, WordIndex j1, WordIndex j2,double=-1.0) const {
    return _scoreOfSwap(a,j1,j2);
  }

  LogProb _scoreOfMove(const alignment&a, WordIndex new_i, WordIndex j,double f = -1.0) const {
    alignment b(a);
    b.set(j, new_i);
    const LogProb a_prob = prob_of_target_and_alignment_given_source(a);
    const LogProb b_prob = prob_of_target_and_alignment_given_source(b);
    if (a_prob) {
      return b_prob / a_prob;
    } else if (b_prob) {
      return 1e20;
    } else {
      return 1.0;
    }
  }

  LogProb _scoreOfSwap(const alignment&a, WordIndex j1, WordIndex j2, double f = -1.0) const {
    WordIndex aj1 = a(j1), aj2 = a(j2);
    if (aj1 == aj2) return 1.0;
    const LogProb a_prob = prob_of_target_and_alignment_given_source(a);

    const_cast<alignment&>(a).set(j1,aj2);
    const_cast<alignment&>(a).set(j2,aj1);
    const LogProb b_prob = prob_of_target_and_alignment_given_source(a);
    const_cast<alignment&>(a).set(j1,aj1);
    const_cast<alignment&>(a).set(j2,aj2);

    if (a_prob) {
      return b_prob / a_prob;
    } else if( b_prob ) {
      return 1e20;
    } else {
      return 1.0;
    }
  }

  LogProb prob_of_target_and_alignment_given_source(const alignment&al,
                                                    bool verbose = false) const;

  void computeScores(const alignment& al, vector<double>& d) const;

  bool isSubOptimal() const { return false; }

  friend inline ostream& operator<<(ostream& out, const TransPairModelHMM&) {
    return out << "NO-OUTPUT for TransPairModelHMM\n";
  }
};

#endif  // GIZAPP_TRANSPAIR_MODELHMM_H_
