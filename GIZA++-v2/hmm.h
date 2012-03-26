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

#ifndef GIZAPP_HMM_H_
#define GIZAPP_HMM_H_

#include <iostream>
#include <string>
#include "util/vector.h"
#include "defs.h"
#include "model2.h"
#include "word_classes.h"
#include "hmm_tables.h"

class model3;
class HMMNetwork;
class Perplexity;
class sentenceHandler;

class HMM : public Model2 {
 private:
  WordClasses ewordclasses;
  WordClasses fwordclasses;
  HMMTables<int,WordClasses> counts, probs;

 public:
  HMM(Model2& m2);
  ~HMM();

  template<class Mapper>
  void makeWordClasses(const Mapper& m1, const Mapper& m2,
                       const std::string& efile, const std::string& ffile);

  void initialize_table_uniformly(sentenceHandler& handler);

  int em_with_tricks(int no_iterations);

  // WARNING: Do not call this function. Not implemented yet.
  void load_table(const char* filename);

  void em_loop(Perplexity& perp, sentenceHandler& sHandler1, bool dump_files,
               const char* alignfile, Perplexity&, bool test,bool doInit,int iter);

  HMMNetwork *makeHMMNetwork(const Vector<WordIndex>& es,
                             const Vector<WordIndex>&fs,
                             bool doInit) const;
  friend class model3;
};

template<class Mapper>
void HMM::makeWordClasses(const Mapper& m1, const Mapper& m2,
                          const std::string& efile, const std::string& ffile) {
  ifstream estrm(efile.c_str()), fstrm(ffile.c_str());
  if (!estrm) {
    cerr << "ERROR: can not read " << efile << endl;
  } else {
    ewordclasses.read(estrm,m1);
  }

  if (!fstrm) {
    cerr << "ERROR: can not read " << ffile << endl;
  } else {
    fwordclasses.read(fstrm,m2);
  }
}


#endif  // GIZAPP_HMM_H_
