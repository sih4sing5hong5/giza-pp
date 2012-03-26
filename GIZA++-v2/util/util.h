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

#ifndef GIZAPP_UTIL_UTIL_H_
#define GIZAPP_UTIL_UTIL_H_

#include <ostream>
#include <map>

#include "defs.h"
#include "util/vector.h"

class Perplexity;
class SentenceHandler;
class VocabList;
class WordEntry;

template <class COUNT, class PROB>
class TModel;

extern void parseConfigFile (char * fname );
extern void parseArguments(int argc, char *argv[]);

extern void generatePerplexityReport(const Perplexity& trainperp,
                                     const Perplexity& testperp,
                                     const Perplexity& trainVperp,
                                     const Perplexity& testVperp,
                                     std::ostream& of, int trainsize,
                                     int testsize, unsigned int last, bool flag);

extern void  printSentencePair(Vector<WordIndex>& es, Vector<WordIndex>& fs, ostream& of);

extern void printOverlapReport(const TModel<COUNT, PROB>& tTable,
                               SentenceHandler& testHandler, VocabList& trainEList,
                               VocabList& trainFList, VocabList& testEList, VocabList& testFList);

extern void printAlignToFile(const Vector<WordIndex>& es,  const Vector<WordIndex>& fs,
                             const Vector<WordEntry>& evlist, const Vector<WordEntry>& fvlist,
                             std::ostream& of2, const Vector<WordIndex>& viterbi_alignment, int pair_no,
                             double viterbi_score);

extern double ErrorsInAlignment(const std::map<std::pair<int,int>,char>& reference,
                                const Vector<WordIndex>& test,
                                int l,
                                int& missing,
                                int& toomuch,
                                int& eventsMissing,
                                int& eventsToomuch,
                                int pair_no);

extern double factorial(int);

#endif  // GIZAPP_UTIL_UTIL_H_
