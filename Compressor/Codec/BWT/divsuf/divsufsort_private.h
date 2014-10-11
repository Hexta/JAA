/*
 * divsufsort_private.h for libdivsufsort
 * Copyright (c) 2003-2008 Yuta Mori All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef DIVSUFSORT_PRIVATE_H
#define DIVSUFSORT_PRIVATE_H

#include <vector>
#include <stack>
#include "divsufsort.h"

using std::stack;
using std::vector;

/*- Constants -*/
#if !defined(UINT8_MAX)
#define UINT8_MAX (255)
#endif /* UINT8_MAX */

#define ALPHABET_SIZE (UINT8_MAX + 1)

/* for divsufsort.c */
#define BUCKET_A_SIZE (ALPHABET_SIZE)
#define BUCKET_B_SIZE (ALPHABET_SIZE * ALPHABET_SIZE)
/* for sssort.c */

#define SS_INSERTIONSORT_THRESHOLD (8)
#define SS_BLOCKSIZE (1024)
#define SS_MISORT_STACKSIZE (16)
#define SS_SMERGE_STACKSIZE (32)

/* for trsort.c */

#define TR_INSERTIONSORT_THRESHOLD (80)
#define TR_STACKSIZE (64)

struct StackDataT {

  StackDataT(int32_t *a, int32_t *b, int32_t c, int32_t d) : a(a), b(b), c(c), d(d) { };

  int32_t *a, *b, c;
  int32_t d;
};

struct StackDataT2 {

  StackDataT2(int32_t *a, int32_t *b, int32_t* c, int32_t d) : a(a), b(b), c(c), d(d) { };

  int32_t *a, *b, *c;
  int32_t d;
};

struct StackDataT3 {

  StackDataT3() : a(0), b(0), c(0), d(0), e(0) { };

  StackDataT3(const int32_t *a, int32_t *b, int32_t *c, int32_t d, int32_t e) : a(a), b(b), c(c), d(d), e(e) { };

  const int32_t *a;
  int32_t *b, *c;
  int32_t d, e;
};

template < class T1, class T2, class T3, class T4 >
inline bool
stackPop(T1 *a, T1 *b, T2 *c, T3 *d, stack < T4 > *stack) {
  if (stack->empty())
    return -1;

  auto const& stackTop = stack->top();

  *a = stackTop.a;
  *b = stackTop.b;
  *c = stackTop.c;
  *d = stackTop.d;

  stack->pop();

  return 0;
}

inline bool
stackPop(int32_t const **a, int32_t **b, int32_t **c, int32_t *d, int32_t *e, vector < StackDataT3 > *stack) {
  if (stack->empty())
    return -1;

  auto const& stackTop = stack->back();

  *a = stackTop.a;
  *b = stackTop.b;
  *c = stackTop.c;
  *d = stackTop.d;
  *e = stackTop.e;

  stack->pop_back();

  return 0;
}

/* for divsufsort.c */
#define BUCKET_A(_c0) bucket_A[(_c0)]
#define BUCKET_B(_c0, _c1) (bucket_B[((_c1) << 8) | (_c0)])
#define BUCKET_BSTAR(_c0, _c1) (bucket_B[((_c0) << 8) | (_c1)])

void
sssort(const uint8_t *Td, const int32_t *PA,
    int32_t *first, int32_t *last,
    int32_t *buf, int32_t bufsize,
    int32_t depth, int32_t n, int32_t lastsuffix);

void
trsort(int32_t *ISA, int32_t *SA, int32_t n, int32_t depth);

#endif /* _DIVSUFSORT_PRIVATE_H */
