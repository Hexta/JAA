/******************************************************************************
 * Copyright (c) 2011-2013 Artur Molchanov <artur.molchanov@gmail.com>        *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 ******************************************************************************/

#pragma once

#include "Compressor/Codec/codecAbstract.h"

class DataBlock;

class Codec_MTF : public virtual Codec_abstract {
public:
  Codec_MTF();
  virtual ~Codec_MTF();

  void decode_MTF(DataBlock* inData);
  void encode_MTF(DataBlock* inData);

private:
  int mtf(int c);
  int get_mtf_c(int i);

  typedef struct mtf_list {
    int c;
    struct mtf_list *prev;
    struct mtf_list *next;
  } mtf_list_t;

  std::vector <mtf_list_t> table;
  mtf_list_t *p, *head, *tail;

  void init_mtf(int tsize);
};

inline int
Codec_MTF::mtf(int c) {
  int i = 0;

  /* find c. */
  p = head;
  while (p->c != c) {
    ++i;
    p = p->next;
  }
  /* move-to-front. */
  if (p->prev) {
    if (p->next) {
      p->prev->next = p->next;
      p->next->prev = p->prev;
    } else {
      p->prev->next = NULL;
      tail = p->prev;
    }
    p->prev = NULL;
    p->next = head;
    head->prev = p;
    head = p;
  } /* front, don't MTF! */

  return i;
}

inline int
Codec_MTF::get_mtf_c(int i) {
  /* find c. */
  p = head;
  while (i--) {
    p = p->next;
  }
  /* move-to-front. */
  if (p->prev) {
    if (p->next) {
      p->prev->next = p->next;
      p->next->prev = p->prev;
    } else {
      p->prev->next = NULL;
      tail = p->prev;
    }
    p->prev = NULL;
    p->next = head;
    head->prev = p;
    head = p;
  }
  return p->c;
}
