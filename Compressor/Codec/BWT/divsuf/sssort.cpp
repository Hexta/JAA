/*
 * sssort.c for libdivsufsort
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

#include "divsufsort_private.h"

#include <algorithm>
#include <stack>
#include <vector>

using std::min;
using std::swap;

/*- Private Functions -*/

const int32_t lg_table[256] = {
  -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

static inline
int32_t
ss_ilg(int32_t n) {
  return (n & 0xff00) ?
      8 + lg_table[(n >> 8) & 0xff] :
      0 + lg_table[(n >> 0) & 0xff];
}

const int32_t sqq_table[256] = {
  0, 16, 22, 27, 32, 35, 39, 42, 45, 48, 50, 53, 55, 57, 59, 61,
  64, 65, 67, 69, 71, 73, 75, 76, 78, 80, 81, 83, 84, 86, 87, 89,
  90, 91, 93, 94, 96, 97, 98, 99, 101, 102, 103, 104, 106, 107, 108, 109,
  110, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,
  128, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
  143, 144, 144, 145, 146, 147, 148, 149, 150, 150, 151, 152, 153, 154, 155, 155,
  156, 157, 158, 159, 160, 160, 161, 162, 163, 163, 164, 165, 166, 167, 167, 168,
  169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178, 178, 179, 180,
  181, 181, 182, 183, 183, 184, 185, 185, 186, 187, 187, 188, 189, 189, 190, 191,
  192, 192, 193, 193, 194, 195, 195, 196, 197, 197, 198, 199, 199, 200, 201, 201,
  202, 203, 203, 204, 204, 205, 206, 206, 207, 208, 208, 209, 209, 210, 211, 211,
  212, 212, 213, 214, 214, 215, 215, 216, 217, 217, 218, 218, 219, 219, 220, 221,
  221, 222, 222, 223, 224, 224, 225, 225, 226, 226, 227, 227, 228, 229, 229, 230,
  230, 231, 231, 232, 232, 233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238,
  239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246, 247,
  247, 248, 248, 249, 249, 250, 250, 251, 251, 252, 252, 253, 253, 254, 254, 255
};

static inline
int32_t
ss_isqrt(int32_t x) {
  int32_t y, e;

  if (x >= (SS_BLOCKSIZE * SS_BLOCKSIZE))
    return SS_BLOCKSIZE;

  e = (x & 0xffff0000) ?
      ((x & 0xff000000) ?
       24 + lg_table[(x >> 24) & 0xff] :
       16 + lg_table[(x >> 16) & 0xff]) :
      ((x & 0x0000ff00) ?
       8 + lg_table[(x >> 8) & 0xff] :
       0 + lg_table[(x >> 0) & 0xff]);

  if (e >= 16) {
    y = sqq_table[x >> ((e - 6) - (e & 1))] << ((e >> 1) - 7);
    if (e >= 24) {
      y = (y + 1 + x / y) >> 1;
    }
    y = (y + 1 + x / y) >> 1;
  } else if (e >= 8) {
    y = (sqq_table[x >> ((e - 6) - (e & 1))] >> (7 - (e >> 1))) + 1;
  } else {
    return sqq_table[x] >> 4;
  }

  return (x < (y * y)) ? y - 1 : y;
}


/*---------------------------------------------------------------------------*/

/* Compares two suffixes. */
static inline
int32_t
ss_compare(const uint8_t *T,
    const int32_t *p1, const int32_t *p2,
    int32_t depth) {
  const uint8_t *U1, *U2, *U1n, *U2n;

  for (U1 = T + depth + *p1,
       U2 = T + depth + *p2,
       U1n = T + *(p1 + 1) + 2,
       U2n = T + *(p2 + 1) + 2;
       (U1 < U1n) && (U2 < U2n) && (*U1 == *U2);
       ++U1, ++U2) {
  }

  return U1 < U1n ?
      (U2 < U2n ? *U1 - *U2 : 1) :
      (U2 < U2n ? -1 : 0);
}


/*---------------------------------------------------------------------------*/

/* Insertionsort for small size groups */
static inline
void
ss_insertionsort(const uint8_t *T, const int32_t *PA,
    int32_t *first, int32_t *last, int32_t depth) {
  int32_t *i, *j;
  int32_t t;
  int32_t r;

  for (i = last - 2; first <= i; --i) {
    for (t = *i, j = i + 1; 0 < (r = ss_compare(T, PA + t, PA + *j, depth));) {
      do {
        *(j - 1) = *j;
      } while ((++j < last) && (*j < 0));
      if (last <= j)
        break;
    }
    if (r == 0)
      *j = ~*j;
    *(j - 1) = t;
  }
}

/*---------------------------------------------------------------------------*/

static inline
void
ss_fixdown(const uint8_t *Td, const int32_t *PA,
    int32_t *SA, int32_t i, int32_t size) {
  int32_t j, k;
  int32_t v;
  int32_t c, d, e;

  for (v = SA[i], c = Td[PA[v]]; (j = 2 * i + 1) < size; SA[i] = SA[k], i = k) {
    d = Td[PA[SA[k = j++]]];
    if (d < (e = Td[PA[SA[j]]])) {
      k = j;
      d = e;
    }
    if (d <= c) {
      break;
    }
  }
  SA[i] = v;
}

/* Simple top-down heapsort. */
void
ss_heapsort(const uint8_t *Td, const int32_t *PA, int32_t *SA, int32_t size) {
  int32_t i, m;
  int32_t t;

  m = size;
  if ((size % 2) == 0) {
    --m;
    if (Td[PA[SA[m / 2]]] < Td[PA[SA[m]]]) {
      swap(SA[m], SA[m / 2]);
    }
  }

  for (i = m / 2 - 1; 0 <= i; --i) {
    ss_fixdown(Td, PA, SA, i, m);
  }
  if ((size % 2) == 0) {
    swap(SA[0], SA[m]);
    ss_fixdown(Td, PA, SA, 0, m);
  }
  for (i = m - 1; 0 < i; --i) {
    t = SA[0], SA[0] = SA[i];
    ss_fixdown(Td, PA, SA, 0, i);
    SA[i] = t;
  }
}


/*---------------------------------------------------------------------------*/

/* Returns the median of three elements. */
static inline
int32_t *
ss_median3(const uint8_t *Td, const int32_t *PA,
    int32_t *v1, int32_t *v2, int32_t *v3) {
  if (Td[PA[*v1]] > Td[PA[*v2]])
    swap(v1, v2);

  if (Td[PA[*v2]] > Td[PA[*v3]]) {
    if (Td[PA[*v1]] > Td[PA[*v3]])
      return v1;
    else
      return v3;
  }
  return v2;
}

/* Returns the median of five elements. */
static inline
int32_t *
ss_median5(const uint8_t *Td, const int32_t *PA,
    int32_t *v1, int32_t *v2, int32_t *v3, int32_t *v4, int32_t *v5) {
  if (Td[PA[*v2]] > Td[PA[*v3]]) {
    swap(v2, v3);
  }
  if (Td[PA[*v4]] > Td[PA[*v5]]) {
    swap(v4, v5);
  }
  if (Td[PA[*v2]] > Td[PA[*v4]]) {
    swap(v2, v4);
    swap(v3, v5);
  }
  if (Td[PA[*v1]] > Td[PA[*v3]]) {
    swap(v1, v3);
  }
  if (Td[PA[*v1]] > Td[PA[*v4]]) {
    swap(v1, v4);
    swap(v3, v5);
  }
  if (Td[PA[*v3]] > Td[PA[*v4]]) {
    return v4;
  }
  return v3;
}

/* Returns the pivot element. */
static inline
int32_t *
ss_pivot(const uint8_t *Td, const int32_t *PA, int32_t *first, int32_t *last) {
  int32_t *middle;
  int32_t t;

  t = last - first;
  middle = first + t / 2;

  if (t <= 512) {
    if (t <= 32) {
      return ss_median3(Td, PA, first, middle, last - 1);
    } else {
      t >>= 2;
      return ss_median5(Td, PA, first, first + t, middle, last - 1 - t, last - 1);
    }
  }
  
  t >>= 3;
  first = ss_median3(Td, PA, first, first + t, first + (t << 1));
  middle = ss_median3(Td, PA, middle - t, middle, middle + t);
  last = ss_median3(Td, PA, last - 1 - (t << 1), last - 1 - t, last - 1);
  return ss_median3(Td, PA, first, middle, last);
}


/*---------------------------------------------------------------------------*/

/* Binary partition for substrings. */
static inline
int32_t *
ss_partition(const int32_t *PA,
    int32_t *first, int32_t *last, int32_t depth) {
  int32_t *a, *b;
  int32_t t;
  for (a = first - 1, b = last;;) {
    for (; (++a < b) && ((PA[*a] + depth) >= (PA[*a + 1] + 1));)
      *a = ~*a;

    for (; (a < --b) && ((PA[*b] + depth) < (PA[*b + 1] + 1));) {
    }

    if (b <= a)
      break;

    t = ~*b;
    *b = *a;
    *a = t;
  }
  if (first < a)
    *first = ~*first;

  return a;
}

/* Multikey introsort for medium size groups. */
void
ss_mintrosort(const uint8_t *T, const int32_t *PA,
    int32_t *first, int32_t *last,
    int32_t depth) {
  stack < StackDataT > stack;

  const uint8_t *Td;
  int32_t *a, *b, *c, *d, *e, *f;
  int32_t s, t;
  int32_t limit = ss_ilg(last - first);
  int32_t v, x = 0;

  for (;;) {

    if ((last - first) <= SS_INSERTIONSORT_THRESHOLD) {
      if (1 < (last - first)) {
        ss_insertionsort(T, PA, first, last, depth);
      }

      if (stackPop(&first, &last, &depth, &limit, &stack))
        return;

      continue;
    }

    Td = T + depth;
    if (limit-- == 0) {
      ss_heapsort(Td, PA, first, last - first);
    }
    if (limit < 0) {
      for (a = first + 1, v = Td[PA[*first]]; a < last; ++a) {
        if ((x = Td[PA[*a]]) != v) {
          if (a > first) {
            break;
          }
          v = x;
          first = a;
        }
      }
      if (Td[PA[*first] - 1] < v) {
        first = ss_partition(PA, first, a, depth);
      }
      if ((a - first) <= (last - a)) {
        if (1 < (a - first)) {
          stack.push(StackDataT(a, last, depth, -1));
          last = a, depth += 1, limit = ss_ilg(a - first);
        } else {
          first = a, limit = -1;
        }
      } else {
        if (last > a) {
          stack.push(StackDataT(first, a, depth + 1, ss_ilg(a - first)));
          first = a, limit = -1;
        } else {
          last = a, depth += 1, limit = ss_ilg(a - first);
        }
      }
      continue;
    }

    /* choose pivot */
    a = ss_pivot(Td, PA, first, last);
    v = Td[PA[*a]];
    swap(*first, *a);

    /* partition */
    for (b = first; (++b < last) && ((x = Td[PA[*b]]) == v);) {
    }
    
    if (((a = b) < last) && (x < v)) {
      while ((++b < last) && ((x = Td[PA[*b]]) <= v)) {
        if (x == v) {
          swap(*b, *a);
          ++a;
        }
      }
    }
    for (c = last; (b < --c) && ((x = Td[PA[*c]]) == v);) {
    }
    if ((b < (d = c)) && (x > v)) {
      for (; (b < --c) && ((x = Td[PA[*c]]) >= v);) {
        if (x == v) {
          swap(*c, *d);
          --d;
        }
      }
    }
    while (b < c) {
      swap(*b, *c);
      while ((++b < c) && ((x = Td[PA[*b]]) <= v)) {
        if (x == v) {
          swap(*b, *a);
          ++a;
        }
      }
      while ((b < --c) && ((x = Td[PA[*c]]) >= v)) {
        if (x == v) {
          swap(*c, *d);
          --d;
        }
      }
    }

    if (a <= d) {
      c = b - 1;

      if ((s = a - first) > (t = b - a)) {
        s = t;
      }
      for (e = first, f = b - s; 0 < s; --s, ++e, ++f) {
        swap(*e, *f);
      }
      if ((s = d - c) > (t = last - d - 1)) {
        s = t;
      }
      for (e = b, f = last - s; 0 < s; --s, ++e, ++f) {
        swap(*e, *f);
      }

      a = first + (b - a), c = last - (d - c);
      b = (v <= Td[PA[*a] - 1]) ? a : ss_partition(PA, a, c, depth);

      if ((a - first) <= (last - c)) {
        if ((last - c) <= (c - b)) {
          stack.push(StackDataT(b, c, depth + 1, ss_ilg(c - b)));
          stack.push(StackDataT(c, last, depth, limit));
          last = a;
        } else if ((a - first) <= (c - b)) {
          stack.push(StackDataT(c, last, depth, limit));
          stack.push(StackDataT(b, c, depth + 1, ss_ilg(c - b)));
          last = a;
        } else {
          stack.push(StackDataT(c, last, depth, limit));
          stack.push(StackDataT(first, a, depth, limit));
          first = b, last = c, depth += 1, limit = ss_ilg(c - b);
        }
      } else {
        if ((a - first) <= (c - b)) {
          stack.push(StackDataT(b, c, depth + 1, ss_ilg(c - b)));
          stack.push(StackDataT(first, a, depth, limit));
          first = c;
        } else if ((last - c) <= (c - b)) {
          stack.push(StackDataT(first, a, depth, limit));
          stack.push(StackDataT(b, c, depth + 1, ss_ilg(c - b)));
          first = c;
        } else {
          stack.push(StackDataT(first, a, depth, limit));
          stack.push(StackDataT(c, last, depth, limit));
          first = b, last = c, depth += 1, limit = ss_ilg(c - b);
        }
      }
    } else {
      limit += 1;
      if (Td[PA[*first] - 1] < v) {
        first = ss_partition(PA, first, last, depth);
        limit = ss_ilg(last - first);
      }
      depth += 1;
    }
  }
}

/*---------------------------------------------------------------------------*/

static inline
void
ss_blockswap(int32_t *a, int32_t *b, int32_t n) {
  int32_t t;
  for (; 0 < n; --n, ++a, ++b) {
    t = *a, *a = *b, *b = t;
  }
}

static inline
void
ss_rotate(int32_t *first, int32_t *middle, int32_t *last) {
  int32_t *a, *b, t;
  int32_t l, r;
  l = middle - first, r = last - middle;

  while ((l > 0) && (r > 0)) {
    if (l == r) {
      ss_blockswap(first, middle, l);
      break;
    }
    if (l < r) {
      a = last - 1, b = middle - 1;
      t = *a;
      do {
        *a-- = *b, *b-- = *a;
        if (b < first) {
          *a = t;
          last = a;
          if ((r -= l + 1) <= l) {
            break;
          }
          a -= 1, b = middle - 1;
          t = *a;
        }
      } while (1);
    } else {
      a = first, b = middle;
      t = *a;
      do {
        *a++ = *b, *b++ = *a;
        if (last <= b) {
          *a = t;
          first = a + 1;
          if ((l -= r + 1) <= r) {
            break;
          }
          a += 1, b = middle;
          t = *a;
        }
      } while (1);
    }
  }
}

/*---------------------------------------------------------------------------*/

void
ss_inplacemerge(const uint8_t *T, const int32_t *PA,
    int32_t *first, int32_t *middle, int32_t *last,
    int32_t depth) {
  const int32_t *p;
  int32_t *a, *b;
  int32_t len, half;
  int32_t q, r;
  int32_t x;

  for (;;) {
    if (*(last - 1) < 0) {
      x = 1;
      p = PA + ~*(last - 1);
    } else {
      x = 0;
      p = PA + *(last - 1);
    }
    for (a = first, len = middle - first, half = len >> 1, r = -1;
         0 < len;
         len = half, half >>= 1) {
      b = a + half;
      q = ss_compare(T, PA + ((0 <= *b) ? *b : ~*b), p, depth);
      if (q < 0) {
        a = b + 1;
        half -= (len & 1) ^ 1;
      } else {
        r = q;
      }
    }
    if (a < middle) {
      if (r == 0) {
        *a = ~*a;
      }
      ss_rotate(a, middle, last);
      last -= middle - a;
      middle = a;
      if (first == middle) {
        break;
      }
    }
    --last;
    if (x != 0) {
      while (*--last < 0) {
      }
    }
    if (middle == last) {
      break;
    }
  }
}


/*---------------------------------------------------------------------------*/

/* Merge-forward with internal buffer. */
void
ss_mergeforward(const uint8_t *T, const int32_t *PA,
    int32_t *first, int32_t *middle, int32_t *last,
    int32_t *buf, int32_t depth) {
  int32_t *a, *b, *c, *bufend;
  int32_t t;
  int32_t r;

  bufend = buf + (middle - first) - 1;
  ss_blockswap(buf, first, middle - first);

  for (t = *(a = first), b = buf, c = middle;;) {
    r = ss_compare(T, PA + *b, PA + *c, depth);
    if (r < 0) {
      do {
        *a++ = *b;
        if (bufend <= b) {
          *bufend = t;
          return;
        }
        *b++ = *a;
      } while (*b < 0);
    } else if (r > 0) {
      do {
        *a++ = *c, *c++ = *a;
        if (last <= c) {
          while (b < bufend) {
            *a++ = *b, *b++ = *a;
          }
          *a = *b, *b = t;
          return;
        }
      } while (*c < 0);
    } else {
      *c = ~*c;
      do {
        *a++ = *b;
        if (bufend <= b) {
          *bufend = t;
          return;
        }
        *b++ = *a;
      } while (*b < 0);

      do {
        *a++ = *c, *c++ = *a;
        if (last <= c) {
          while (b < bufend) {
            *a++ = *b, *b++ = *a;
          }
          *a = *b, *b = t;
          return;
        }
      } while (*c < 0);
    }
  }
}

/* Merge-backward with internal buffer. */
void
ss_mergebackward(const uint8_t *T, const int32_t *PA,
    int32_t *first, int32_t *middle, int32_t *last,
    int32_t *buf, int32_t depth) {
  const int32_t *p1, *p2;
  int32_t *a, *b, *c, *bufend;
  int32_t t;
  int32_t r;
  int32_t x;

  bufend = buf + (last - middle) - 1;
  ss_blockswap(buf, middle, last - middle);

  x = 0;
  if (*bufend < 0) {
    p1 = PA + ~*bufend;
    x |= 1;
  } else {
    p1 = PA + *bufend;
  }
  if (*(middle - 1) < 0) {
    p2 = PA + ~*(middle - 1);
    x |= 2;
  } else {
    p2 = PA + *(middle - 1);
  }
  for (t = *(a = last - 1), b = bufend, c = middle - 1;;) {
    r = ss_compare(T, p1, p2, depth);
    if (0 < r) {
      if (x & 1) {
        do {
          *a-- = *b, *b-- = *a;
        } while (*b < 0);
        x ^= 1;
      }
      *a-- = *b;
      if (b <= buf) {
        *buf = t;
        break;
      }
      *b-- = *a;
      if (*b < 0) {
        p1 = PA + ~*b;
        x |= 1;
      } else {
        p1 = PA + *b;
      }
    } else if (r < 0) {
      if (x & 2) {
        do {
          *a-- = *c, *c-- = *a;
        } while (*c < 0);
        x ^= 2;
      }
      *a-- = *c, *c-- = *a;
      if (c < first) {
        while (buf < b) {
          *a-- = *b, *b-- = *a;
        }
        *a = *b, *b = t;
        break;
      }
      if (*c < 0) {
        p2 = PA + ~*c;
        x |= 2;
      } else {
        p2 = PA + *c;
      }
    } else {
      if (x & 1) {
        do {
          *a-- = *b, *b-- = *a;
        } while (*b < 0);
        x ^= 1;
      }
      *a-- = ~*b;
      if (b <= buf) {
        *buf = t;
        break;
      }
      *b-- = *a;
      if (x & 2) {
        do {
          *a-- = *c, *c-- = *a;
        } while (*c < 0);
        x ^= 2;
      }
      *a-- = *c, *c-- = *a;
      if (c < first) {
        while (buf < b) {
          *a-- = *b, *b-- = *a;
        }
        *a = *b, *b = t;
        break;
      }
      if (*b < 0) {
        p1 = PA + ~*b;
        x |= 1;
      } else {
        p1 = PA + *b;
      }
      if (*c < 0) {
        p2 = PA + ~*c;
        x |= 2;
      } else {
        p2 = PA + *c;
      }
    }
  }
}

/* D&C based merge. */
void
ss_swapmerge(const uint8_t *T, const int32_t *PA,
    int32_t *first, int32_t *middle, int32_t *last,
    int32_t *buf, int32_t bufsize, int32_t depth) {
#define GETIDX(a) ((0 <= (a)) ? (a) : (~(a)))
#define MERGE_CHECK(a, b, c)\
  do {\
    if(((c) & 1) ||\
       (((c) & 2) && (ss_compare(T, PA + GETIDX(*((a) - 1)), PA + *(a), depth) == 0))) {\
      *(a) = ~*(a);\
    }\
    if(((c) & 4) && ((ss_compare(T, PA + GETIDX(*((b) - 1)), PA + *(b), depth) == 0))) {\
      *(b) = ~*(b);\
    }\
  } while(0)

  stack < StackDataT2 > stack;
  int32_t *l, *r, *lm, *rm;
  int32_t m, len, half;
  int32_t check, next;

  for (check = 0;;) {
    if ((last - middle) <= bufsize) {
      if ((first < middle) && (middle < last)) {
        ss_mergebackward(T, PA, first, middle, last, buf, depth);
      }
      MERGE_CHECK(first, last, check);

      if (stackPop(&first, &middle, &last, &check, &stack))
        return;

      continue;
    }

    if ((middle - first) <= bufsize) {
      if (first < middle) {
        ss_mergeforward(T, PA, first, middle, last, buf, depth);
      }
      MERGE_CHECK(first, last, check);

      if (stack.empty())
        return;

	  auto const& stackTop = stack.top();

      first = stackTop.a;
	  middle = stackTop.b;
	  last = stackTop.c;
	  check = stackTop.d;
      stack.pop();

      continue;
    }

    for (m = 0, len = min(middle - first, last - middle), half = len >> 1;
         0 < len;
         len = half, half >>= 1) {
      if (ss_compare(T, PA + GETIDX(*(middle + m + half)),
          PA + GETIDX(*(middle - m - half - 1)), depth) < 0) {
        m += half + 1;
        half -= (len & 1) ^ 1;
      }
    }

    if (0 < m) {
      lm = middle - m, rm = middle + m;
      ss_blockswap(lm, middle, m);
      l = r = middle, next = 0;
      if (rm < last) {
        if (*rm < 0) {
          *rm = ~*rm;
          if (first < lm) {
            while (*--l < 0) {
            }
            next |= 4;
          }
          next |= 1;
        } else if (first < lm) {
          for (; *r < 0; ++r) {
          }
          next |= 2;
        }
      }

      if ((l - first) <= (last - r)) {
        stack.push(StackDataT2(r, rm, last, (next & 3) | (check & 4)));
        middle = lm, last = l, check = (check & 3) | (next & 4);
      } else {
        if ((next & 2) && (r == middle)) {
          next ^= 6;
        }
        stack.push(StackDataT2(first, lm, l, (check & 3) | (next & 4)));
        first = r, middle = rm, check = (next & 3) | (check & 4);
      }
    } else {
      if (ss_compare(T, PA + GETIDX(*(middle - 1)), PA + *middle, depth) == 0) {
        *middle = ~*middle;
      }
      MERGE_CHECK(first, last, check);

      if (stackPop(&first, &middle, &last, &check, &stack))
        return;
    }
  }
}


/*---------------------------------------------------------------------------*/

/*- Function -*/

/* Substring sort */
void
sssort(const uint8_t *T, const int32_t *PA,
    int32_t *first, int32_t *last,
    int32_t *buf, int32_t bufsize,
    int32_t depth, int32_t n, int32_t lastsuffix) {
  int32_t *a;
  int32_t *b, *middle;
  int32_t j, k, curbufsize, limit;
  int32_t i;

  if (lastsuffix != 0)
    ++first;

  if ((bufsize < SS_BLOCKSIZE) &&
      (bufsize < (last - first)) &&
      (bufsize < (limit = ss_isqrt(last - first)))) {
    if (SS_BLOCKSIZE < limit)
      limit = SS_BLOCKSIZE;

    buf = middle = last - limit, bufsize = limit;
  } else {
    middle = last, limit = 0;
  }
  for (a = first, i = 0; SS_BLOCKSIZE < (middle - a); a += SS_BLOCKSIZE, ++i) {
    int32_t *curbuf;

    ss_mintrosort(T, PA, a, a + SS_BLOCKSIZE, depth);
    curbufsize = last - (a + SS_BLOCKSIZE);
    curbuf = a + SS_BLOCKSIZE;
    if (curbufsize <= bufsize) {
      curbufsize = bufsize, curbuf = buf;
    }
    for (b = a, k = SS_BLOCKSIZE, j = i; j & 1; b -= k, k <<= 1, j >>= 1) {
      ss_swapmerge(T, PA, b - k, b, b + k, curbuf, curbufsize, depth);
    }
  }

  ss_mintrosort(T, PA, a, middle, depth);

  for (k = SS_BLOCKSIZE; i != 0; k <<= 1, i >>= 1) {
    if (i & 1) {
      ss_swapmerge(T, PA, a - k, a, middle, buf, bufsize, depth);
      a -= k;
    }
  }
  if (limit != 0) {
    ss_mintrosort(T, PA, middle, last, depth);
    ss_inplacemerge(T, PA, first, middle, last, depth);
  }


  if (lastsuffix != 0) {
    /* Insert last type B* suffix. */
    int32_t PAi[2];
    PAi[0] = PA[*(first - 1)], PAi[1] = n - 2;
    for (a = first, i = *(first - 1);
         (a < last) && ((*a < 0) || (0 < ss_compare(T, &(PAi[0]), PA + *a, depth)));
         ++a) {
      *(a - 1) = *a;
    }
    *(a - 1) = i;
  }
}
