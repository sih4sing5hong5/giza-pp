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

#ifndef GIZAPP_DEFS_H_
#define GIZAPP_DEFS_H_

typedef unsigned int WordIndex;
typedef unsigned int PositionIndex;
typedef float PROB;
typedef float COUNT;

const int kTransfer = 0;
const int kTransferSimple = 1;
const int kMaxWeight = 457979;
const int kTrainBufSize = 50000;
const unsigned int kMaxAllowedSentenceLength = 101;

// TODO: we might want to consider enum type.
const int kParLevIter    = 1;
const int kParLevOptheur = 2;
const int kParLevOutput  = 3;
const int kParLevSmooth  = 4;
const int kParLevEM      = 5;
const int kParLevModels  = 6;
const int kParLevSpecial = 7;
const int kParLevInput   = 8;

extern WordIndex g_max_fertility;

// Lambda that is used to scale cross_entropy factor
extern double g_lambda;

#endif  // GIZAPP_DEFS_H_
