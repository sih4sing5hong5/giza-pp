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

#include <climits>

typedef unsigned int WordIndex;
typedef unsigned int PositionIndex;
typedef float PROB;
typedef float COUNT;

const int TRANSFER_SIMPLE = 1;
const int TRANSFER = 0;
const unsigned int MAX_SENTENCE_LENGTH_ALLOWED = 101;
const int TRAIN_BUFFER_SIZE = 50000;
const int MAX_W = 457979;
const unsigned int MAX_VOCAB_SIZE = UINT_MAX;

const int PARLEV_ITER=1;
const int PARLEV_OPTHEUR=2;
const int PARLEV_OUTPUT=3;
const int PARLEV_SMOOTH=4;
const int PARLEV_EM=5;
const int PARLEV_MODELS=6;
const int PARLEV_SPECIAL=7;
const int PARLEV_INPUT=8;

extern WordIndex MAX_FERTILITY;
extern double LAMBDA; // Lambda that is used to scale cross_entropy factor

#endif  // GIZAPP_DEFS_H_
