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

#ifndef GIZAPP_GLOBALS_H_
#define GIZAPP_GLOBALS_H_

#include <string>
#include <fstream>
#include <map>
#include "defs.h"
#include "util/vector.h"

// TODO: Use only POD data. Replace string objects with const char[]
// if it possible.

extern float g_smooth_prob;
extern bool Verbose, Log, Peg, Transfer, Transfer2to3, useDict ;
extern string Prefix, LogFilename, OPath,
  SourceVocabFilename, TargetVocabFilename, CorpusFilename, TestCorpusFilename,
  t_Filename, a_Filename, p0_Filename, d_Filename, n_Filename, dictionary_Filename;
extern ofstream logmsg ;
extern double M5P0,P0 ;
extern bool NODUMPS, FEWDUMPS  ;
extern string Usage ;
extern unsigned int MAX_SENTENCE_LENGTH ;
extern int PegUntil;

extern short DeficientDistortionForEmptyWord;

extern int M4_Dependencies;
extern int M5_Dependencies;

extern short OutputInAachenFormat;

#define DEP_MODEL_l 1
#define DEP_MODEL_m 2
#define DEP_MODEL_F 4
#define DEP_MODEL_E 8

#define DEP_MODELb_l 16
#define DEP_MODELb_m 32
#define DEP_MODELb_F 64
#define DEP_MODELb_E 128

#define DEP_SUM 256

class VocabList;

extern VocabList *globeTrainVcbList, *globfTrainVcbList;

extern short g_prediction_in_alignments;
extern short SmoothHMM;
#define VERB Verbose

extern Vector<map< pair<int,int>,char > > ReferenceAlignment;

#endif  // GIZAPP_GLOBALS_H_
