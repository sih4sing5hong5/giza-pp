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

#ifndef GIZAPP_MODEL1_H_
#define GIZAPP_MODEL1_H_

#include "globals.h"
#include "util/util.h"
#include "util/vector.h"
#include "vocab.h"

class Perplexity;
class sentenceHandler;

namespace util {
class Dictionary;
} // namespace util

extern int NumberOfVALIalignments;

class ReportInfo {
 protected:
  Perplexity& perp;
  sentenceHandler& sHandler1;
  Perplexity* testPerp;
  sentenceHandler* testHandler;
  Perplexity& trainViterbiPerp;
  Perplexity* testViterbiPerp;

  ReportInfo(Perplexity& _perp,
             sentenceHandler& _sHandler1,
             Perplexity* _testPerp,
             sentenceHandler* _testHandler,
             Perplexity& _trainViterbiPerp,
             Perplexity* _testViterbiPerp)
    : perp(_perp),
      sHandler1(_sHandler1),
      testPerp(_testPerp),
      testHandler(_testHandler),
      trainViterbiPerp(_trainViterbiPerp),
      testViterbiPerp(_testViterbiPerp) { }

  virtual ~ReportInfo() { }
};

class Model1 : public ReportInfo {
 public:
  string efFilename;
  VocabList&  Elist ;
  VocabList&  Flist ;
  double eTotalWCount ; // size of source copus in number of words
  double fTotalWCount ; // size of target corpus in number of words
  int noEnglishWords;
  int noFrenchWords;
  tmodel<COUNT, PROB>&tTable;
  Vector<WordEntry>& evlist ;
  Vector<WordEntry>& fvlist ;
  int ALmissing,ALtoomuch,ALeventsMissing,ALeventsToomuch;
  int ALmissingVALI,ALtoomuchVALI,ALeventsMissingVALI,ALeventsToomuchVALI;
  int ALmissingTEST,ALtoomuchTEST,ALeventsMissingTEST,ALeventsToomuchTEST;

  Model1(const char* efname, VocabList& evcblist, VocabList& fvcblist,
         tmodel<COUNT, PROB>&_tTable,Perplexity& _perp,
         sentenceHandler& _sHandler1,
         Perplexity* _testPerp,
         sentenceHandler* _testHandler,
         Perplexity& _trainViterbiPerp,
         Perplexity* _testViterbiPerp);

  virtual ~Model1();

  void initialize_table_uniformly(sentenceHandler& sHandler1);
  int em_with_tricks(int noIterations,
                     bool seedModel1, util::Dictionary& dictionary, bool useDict);
  void load_table(const char* tname);
  void readVocabFile(const char* fname, Vector<WordEntry>& vlist, int& vsize,
                     int& total);
  Vector<WordEntry>& getEnglishVocabList(void) const { return Elist.getVocabList();};
  Vector<WordEntry>& getFrenchVocabList(void) const  { return Flist.getVocabList();};
  double getETotalWCount(void) const { return eTotalWCount;};
  double getFTotalWCount(void) const { return fTotalWCount;};
  int getNoEnglishWords(void) const  { return noEnglishWords;};
  int getNoFrenchWords(void)  const { return noFrenchWords;};
  tmodel<COUNT, PROB>& getTTable(void) { return tTable;};
  string& getEFFilename(void) { return efFilename;};

  void addAL(const Vector<WordIndex>& viterbi_alignment,int pair_no,int l) {
    if ( pair_no<=int(ReferenceAlignment.size()) ) {
	  //cerr << "AL: " << viterbi_alignment << " " << pair_no << endl;
      ErrorsInAlignment(ReferenceAlignment[pair_no-1],
                        viterbi_alignment,
                        l,
                        ALmissing,
                        ALtoomuch,
                        ALeventsMissing,
                        ALeventsToomuch,
                        pair_no);

      if (pair_no <= NumberOfVALIalignments) {
        ErrorsInAlignment(ReferenceAlignment[pair_no-1],
                          viterbi_alignment,
                          l,
                          ALmissingVALI,
                          ALtoomuchVALI,
                          ALeventsMissingVALI,
                          ALeventsToomuchVALI,
                          pair_no);
      }
      if (pair_no > NumberOfVALIalignments) {
        ErrorsInAlignment(ReferenceAlignment[pair_no-1],
                          viterbi_alignment,
                          l,
                          ALmissingTEST,
                          ALtoomuchTEST,
                          ALeventsMissingTEST,
                          ALeventsToomuchTEST,
                          pair_no);
      }
    }
  }

  // TODO: WTF! clean up.
  void initAL() {
    ALmissingVALI=ALtoomuchVALI=ALeventsMissingVALI=ALeventsToomuchVALI=ALmissingTEST=ALtoomuchTEST=ALeventsMissingTEST=ALeventsToomuchTEST=ALmissing=ALtoomuch=ALeventsMissing=ALeventsToomuch=0;
  }

  double errorsAL () const {
    if (ALeventsMissingVALI+ALeventsToomuchVALI)
      return (ALmissingVALI+ALtoomuchVALI)/double(ALeventsMissingVALI+ALeventsToomuchVALI);
    else
      return 0.0;
  }

  void errorReportAL(ostream& out, const string& m) const;

 private:
  void em_loop(int it, Perplexity& perp,
               sentenceHandler& sHandler1,
               bool seedModel1,
               bool , const char*,
               util::Dictionary& dictionary, bool useDict,
               Perplexity& viterbiperp, bool=false);

  friend class Model2;
  friend class HMM;
};

#endif  // GIZAPP_MODEL1_H_
