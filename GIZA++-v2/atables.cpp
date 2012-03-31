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

#include "atables.h"
#include "globals.h"
#include "util/assert.h"
#include "parameter.h"

GLOBAL_PARAMETER(bool, CompactADTable, "compactadtable", "1: only 3-dimensional alignment table for IBM-2 and IBM-3", kParLevModels, 1);
GLOBAL_PARAMETER(float, amodel_smooth_factor, "model23SmoothFactor", "smoothing parameter for IBM-2/3 (interpolation with constant)", kParLevSmooth, 0.0);

template <class VALTYPE>
void AModel<VALTYPE>::printTable(const char *filename) const {
  if (is_distortion)
    cout << "Dumping distortion table (d) to file:" << filename <<'\n';
  else
    cout << "Dumping alignment table (a) to file:" << filename <<'\n';

  ofstream of(filename);
  double ssum = 0.0;
  for (WordIndex l = 0; l < MaxSentLength; l++) {
    for (WordIndex m = 0; m < MaxSentLength; m++) {
      if (CompactADTable && l != m)
        continue;
      unsigned int L = ((CompactADTable&&is_distortion)?MaxSentLength:(l+1))-1;
      unsigned int M = ((CompactADTable&&!is_distortion)?MaxSentLength:(m+1))-1;
      if(is_distortion == 0) {
        for (WordIndex j = 1;j <= M; j++) {
          double sum=0.0;
          for (WordIndex i = 0; i <= L; i++) {
            VALTYPE x=getValue(i, j, L, M);
            if (x > g_smooth_prob) {
              of << i << ' ' << j << ' ' << L << ' ' << M << ' ' << x << '\n';
              sum+=x;
            }
          }
          ssum+=sum;
        }
      } else {
        for (WordIndex i = 0; i <= L; i++) {
          double sum = 0.0;
          for (WordIndex j = 1; j <= M; j++) {
            VALTYPE x=getValue(j, i, L, M);
            if (x > g_smooth_prob) {
              of << j << ' ' << i << ' ' << L << ' ' << M << ' ' << x << '\n';
              sum+=x;
            }
          }
          ssum+=sum;
        }
      }
    }
  }
}

template <class VALTYPE>
void AModel<VALTYPE>::readTable(const char *filename) {
  ifstream inf(filename);
  cout << "Reading a/d table from " << filename << "\n";
  if(!inf){
    cerr << "\nERROR: Cannot open " << filename<<"\n";
    return;
  }
  WordIndex w, x, l, m;
  VALTYPE prob;
  while(inf >> w >> x >> l >> m >> prob ) {
    // the NULL word is added to the length
    // of the sentence in the tables, but discount it when you write the tables.
    setValue(w, x, l, m, prob);
  }
}

template class AModel<COUNT>;
