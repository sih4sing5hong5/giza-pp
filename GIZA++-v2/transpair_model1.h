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

#ifndef GIZAPP_TRANSPAIR_MODEL1_H_
#define GIZAPP_TRANSPAIR_MODEL1_H_

#include <cmath>
#include <algorithm>

#include "defs.h"
#include "util/array2.h"
#include "util/vector.h"
#include "ntables.h"
#include "atables.h"
#include "ttables.h"
#include "alignment.h"
#include "port/stl_helper.h"

class transpair_model1
{
 public:
  bool verboseTP;
  Array2<PROB, Vector<PROB> > t;
  WordIndex l, m;
  Vector<WordIndex> E,F;
  void setMode(bool)
  {}
  transpair_model1(const Vector<WordIndex>&es, const Vector<WordIndex>&fs, const TModel<COUNT, PROB>&tTable)
      : verboseTP(0),t(es.size(), fs.size()),l(es.size()-1), m(fs.size()-1),E(es),F(fs)
  {
    WordIndex l=es.size()-1,m=fs.size()-1;
    for(WordIndex i=0;i<=l;i++)
      for(WordIndex j=1;j<=m;j++)
      {
        t(i, j)=tTable.getProb(es[i], fs[j]);
        if( !(t(i,j)>=PROB_SMOOTH) )
          cerr << "ERROR IN PROBABILITY: " << t(i,j) << " " << PROB_SMOOTH << endl;
      }
  }
  /*  transpair_model1(const Vector<WordIndex>&es, const Vector<WordIndex>&fs)
      : verboseTP(0),t(es.size(), fs.size()),l(es.size()-1), m(fs.size()-1),E(es),F(fs)
      {
      WordIndex l=es.size()-1,m=fs.size()-1;
      for(WordIndex i=0;i<=l;i++)
      for(WordIndex j=1;j<=m;j++)
      {
      const string&estr=globeTrainVcbList->getVocabList()[es[i]].word;
      const string&fstr=globfTrainVcbList->getVocabList()[fs[j]].word;
      if( lev(estr,fstr)==0 )
      t(i,j)=1.0;
      else
      t(i,j)=1/100.0;
      MASSERT( t(i,j)>=PROB_SMOOTH );
      }
      }*/
  WordIndex get_l()const
  {return l;}
  WordIndex get_m()const
  {return m;}
  const PROB&get_t(WordIndex i, WordIndex j)const
  {MASSERT( t(i,j)>=PROB_SMOOTH);
    return t(i, j);}
  WordIndex get_es(int i)const {return E[i];}
  WordIndex get_fs(int j)const {return F[j];}
  bool greedyHillClimbing()const
  {return 0;}
  void computeScores(const Alignment&,vector<double>&)const
  {}
  LogProb scoreOfMove(const Alignment&a, WordIndex new_i, WordIndex j,double=-1.0)const
  {
    int old_i=a(j);
    return (t(new_i, j) /t(old_i, j));
  }
  LogProb scoreOfSwap(const Alignment&a, WordIndex j1, WordIndex j2,double=-1.0)const
  {
    WordIndex i1=a(j1), i2=a(j2);
    return (t(i2, j1)/t(i1, j1))*(t(i1, j2)/t(i2, j2));
  }
  LogProb prob_of_target_and_alignment_given_source(const Alignment&al)const
  {
    LogProb prob=1.0;
    int lp1=al.get_l()+1;
    for(unsigned int j=1;j<=al.get_m();++j)
      prob*=t(al(j),j)/lp1;
    return prob;
  }
};

#endif  // GIZAPP_TRANSPAIR_MODEL1_H_
