/*
 * divsufsort.c for libdivsufsort
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

#include <cstring>
#include <stdlib.h>
#include "divsufsort_private.h"

/*- Private Functions -*/

/* Sorts suffixes of type B*. */
int32_t
sort_typeBstar( const uint8_t *T, int32_t *SA,
				int32_t *bucket_A, int32_t *bucket_B,
				int32_t n )
{
	int32_t *PAb, *ISAb, *buf;

	int32_t i, j, k, t, m, bufsize;
	int32_t c0, c1;

	memset( bucket_A, 0, BUCKET_A_SIZE * sizeof (int32_t ) );
	memset( bucket_B, 0, BUCKET_B_SIZE * sizeof (int32_t ) );

	/* Count the number of occurrences of the first one or two characters of each
	   type A, B and B* suffix. Moreover, store the beginning position of all
	   type B* suffixes into the array SA. */
	for ( i = n - 1, m = n, c0 = T[n - 1]; 0 <= i; )
	{
		/* type A suffix. */
		do
		{
			++BUCKET_A( c1 = c0 );
		}
		while ( ( 0 <= --i ) && ( ( c0 = T[i] ) >= c1 ) );
		if ( 0 <= i )
		{
			/* type B* suffix. */
			++BUCKET_BSTAR( c0, c1 );
			SA[--m] = i;
			/* type B suffix. */
			for ( --i, c1 = c0; ( 0 <= i ) && ( ( c0 = T[i] ) <= c1 ); --i, c1 = c0 )
			{
				++BUCKET_B( c0, c1 );
			}
		}
	}
	m = n - m;
	/*
	note:
	  A type B* suffix is lexicographically smaller than a type B suffix that
	  begins with the same first two characters.
	 */

	/* Calculate the index of start/end point of each bucket. */
	for ( c0 = 0, i = 0, j = 0; c0 < ALPHABET_SIZE; ++c0 )
	{
		t = i + BUCKET_A( c0 );
		BUCKET_A( c0 ) = i + j; /* start point */
		i = t + BUCKET_B( c0, c0 );
		for ( c1 = c0 + 1; c1 < ALPHABET_SIZE; ++c1 )
		{
			j += BUCKET_BSTAR( c0, c1 );
			BUCKET_BSTAR( c0, c1 ) = j; /* end point */
			i += BUCKET_B( c0, c1 );
		}
	}

	if ( 0 < m )
	{
		/* Sort the type B* suffixes by their first two characters. */
		PAb = SA + n - m;
		ISAb = SA + m;
		for ( i = m - 2; 0 <= i; --i )
		{
			t = PAb[i], c0 = T[t], c1 = T[t + 1];
			SA[--BUCKET_BSTAR( c0, c1 )] = i;
		}
		t = PAb[m - 1], c0 = T[t], c1 = T[t + 1];
		SA[--BUCKET_BSTAR( c0, c1 )] = m - 1;

		/* Sort the type B* substrings using sssort. */

		buf = SA + m, bufsize = n - ( 2 * m );
		for ( c0 = ALPHABET_SIZE - 2, j = m; 0 < j; --c0 )
		{
			for ( c1 = ALPHABET_SIZE - 1; c0 < c1; j = i, --c1 )
			{
				i = BUCKET_BSTAR( c0, c1 );
				if ( 1 < ( j - i ) )
				{
					sssort( T, PAb, SA + i, SA + j,
						 buf, bufsize, 2, n, *( SA + i ) == ( m - 1 ) );
				}
			}
		}

		/* Compute ranks of type B* substrings. */
		for ( i = m - 1; 0 <= i; --i )
		{
			if ( 0 <= SA[i] )
			{
				j = i;
				do
				{
					ISAb[SA[i]] = i;
				}
				while ( ( 0 <= --i ) && ( 0 <= SA[i] ) );
				SA[i + 1] = i - j;
				if ( i <= 0 )
				{
					break;
				}
			}
			j = i;
			do
			{
				ISAb[SA[i] = ~SA[i]] = j;
			}
			while ( SA[--i] < 0 );
			ISAb[SA[i]] = j;
		}

		/* Construct the inverse suffix array of type B* suffixes using trsort. */
		trsort( ISAb, SA, m, 1 );

		/* Set the sorted order of tyoe B* suffixes. */
		for ( i = n - 1, j = m, c0 = T[n - 1]; 0 <= i; )
		{
			for ( --i, c1 = c0; ( 0 <= i ) && ( ( c0 = T[i] ) >= c1 ); --i, c1 = c0 )
			{
			}
			if ( 0 <= i )
			{
				t = i;
				for ( --i, c1 = c0; ( 0 <= i ) && ( ( c0 = T[i] ) <= c1 ); --i, c1 = c0 )
				{
				}
				SA[ISAb[--j]] = ( ( t == 0 ) || ( 1 < ( t - i ) ) ) ? t : ~t;
			}
		}

		/* Calculate the index of start/end point of each bucket. */
		BUCKET_B( ALPHABET_SIZE - 1, ALPHABET_SIZE - 1 ) = n; /* end point */
		for ( c0 = ALPHABET_SIZE - 2, k = m - 1; 0 <= c0; --c0 )
		{
			i = BUCKET_A( c0 + 1 ) - 1;
			for ( c1 = ALPHABET_SIZE - 1; c0 < c1; --c1 )
			{
				t = i - BUCKET_B( c0, c1 );
				BUCKET_B( c0, c1 ) = i; /* end point */

				/* Move all type B* suffixes to the correct position. */
				for ( i = t, j = BUCKET_BSTAR( c0, c1 );
					 j <= k;
					 --i, --k )
				{
					SA[i] = SA[k];
				}
			}
			BUCKET_BSTAR( c0, c0 + 1 ) = i - BUCKET_B( c0, c0 ) + 1; /* start point */
			BUCKET_B( c0, c0 ) = i; /* end point */
		}
	}

	return m;
}

/* Constructs the suffix array by using the sorted order of type B* suffixes. */
void
construct_SA( const uint8_t *T, int32_t *SA,
			  int32_t *bucket_A, int32_t *bucket_B,
			  int32_t n, int32_t m )
{
	int32_t *i, *j, *k;
	int32_t s;
	int32_t c0, c1, c2;

	if ( 0 < m )
	{
		/* Construct the sorted order of type B suffixes by using
		   the sorted order of type B* suffixes. */
		for ( c1 = ALPHABET_SIZE - 2; 0 <= c1; --c1 )
		{
			/* Scan the suffix array from right to left. */
			for ( i = SA + BUCKET_BSTAR( c1, c1 + 1 ),
				 j = SA + BUCKET_A( c1 + 1 ) - 1, k = NULL, c2 = -1;
				 i <= j;
				 --j )
			{
				if ( 0 < ( s = *j ) )
				{
					*j = ~s;
					c0 = T[--s];
					if ( ( 0 < s ) && ( T[s - 1] > c0 ) )
					{
						s = ~s;
					}
					if ( c0 != c2 )
					{
						if ( 0 <= c2 )
						{
							BUCKET_B( c2, c1 ) = k - SA;
						}
						k = SA + BUCKET_B( c2 = c0, c1 );
					}
					*k-- = s;
				}
				else
				{
					*j = ~s;
				}
			}
		}
	}

	/* Construct the suffix array by using
	   the sorted order of type B suffixes. */
	k = SA + BUCKET_A( c2 = T[n - 1] );
	*k++ = ( T[n - 2] < c2 ) ? ~( n - 1 ) : ( n - 1 );
	/* Scan the suffix array from left to right. */
	for ( i = SA, j = SA + n; i < j; ++i )
	{
		if ( 0 < ( s = *i ) )
		{
			c0 = T[--s];
			if ( ( s == 0 ) || ( T[s - 1] < c0 ) )
			{
				s = ~s;
			}
			if ( c0 != c2 )
			{
				BUCKET_A( c2 ) = k - SA;
				k = SA + BUCKET_A( c2 = c0 );
			}
			*k++ = s;
		}
		else
		{
			*i = ~s;
		}
	}
}

/* Constructs the burrows-wheeler transformed string directly
   by using the sorted order of type B* suffixes. */
int32_t
construct_BWT( const uint8_t *T, int32_t *SA,
			   int32_t *bucket_A, int32_t *bucket_B,
			   int32_t n, int32_t m )
{
	int32_t *i, *j, *k, *orig;
	int32_t s;
	int32_t c0, c1, c2;

	if ( 0 < m )
	{
		/* Construct the sorted order of type B suffixes by using
		   the sorted order of type B* suffixes. */
		for ( c1 = ALPHABET_SIZE - 2; 0 <= c1; --c1 )
		{
			/* Scan the suffix array from right to left. */
			for ( i = SA + BUCKET_BSTAR( c1, c1 + 1 ),
				 j = SA + BUCKET_A( c1 + 1 ) - 1, k = NULL, c2 = -1;
				 i <= j;
				 --j )
			{
				if ( 0 < ( s = *j ) )
				{
					c0 = T[--s];
					*j = ~( ( int32_t ) c0 );
					if ( ( 0 < s ) && ( T[s - 1] > c0 ) )
					{
						s = ~s;
					}
					if ( c0 != c2 )
					{
						if ( 0 <= c2 )
						{
							BUCKET_B( c2, c1 ) = k - SA;
						}
						k = SA + BUCKET_B( c2 = c0, c1 );
					}
					*k-- = s;
				}
				else if ( s != 0 )
				{
					*j = ~s;
				}
			}
		}
	}

	/* Construct the BWTed string by using
	   the sorted order of type B suffixes. */
	k = SA + BUCKET_A( c2 = T[n - 1] );
	*k++ = ( T[n - 2] < c2 ) ? ~( ( int32_t ) T[n - 2] ) : ( n - 1 );
	/* Scan the suffix array from left to right. */
	for ( i = SA, j = SA + n, orig = SA; i < j; ++i )
	{
		if ( 0 < ( s = *i ) )
		{
			c0 = T[--s];
			*i = c0;
			if ( ( 0 < s ) && ( T[s - 1] < c0 ) )
			{
				s = ~( ( int32_t ) T[s - 1] );
			}
			if ( c0 != c2 )
			{
				BUCKET_A( c2 ) = k - SA;
				k = SA + BUCKET_A( c2 = c0 );
			}
			*k++ = s;
		}
		else if ( s != 0 )
		{
			*i = ~s;
		}
		else
		{
			orig = i;
		}
	}

	return orig - SA;
}


/*---------------------------------------------------------------------------*/

/*- Function -*/

int32_t
divsufsort( const uint8_t *T, int32_t *SA, int32_t n )
{
	int32_t *bucket_A, *bucket_B;
	int32_t m;
	int32_t err = 0;

	/* Check arguments. */
	if ( ( T == NULL ) || ( SA == NULL ) || ( n < 0 ) )
	{
		return -1;
	}
	else if ( n == 0 )
	{
		return 0;
	}
	else if ( n == 1 )
	{
		SA[0] = 0;
		return 0;
	}
	else if ( n == 2 )
	{
		m = ( T[0] < T[1] );
		SA[m ^ 1] = 0, SA[m] = 1;
		return 0;
	}

	bucket_A = new int32_t [BUCKET_A_SIZE];
	bucket_B = new int32_t [BUCKET_B_SIZE];

	/* Suffixsort. */
	if ( ( bucket_A != NULL ) && ( bucket_B != NULL ) )
	{
		m = sort_typeBstar( T, SA, bucket_A, bucket_B, n );
		construct_SA( T, SA, bucket_A, bucket_B, n, m );
	}
	else
	{
		err = -2;
	}

	delete[] bucket_B;
	delete[] bucket_A;

	return err;
}

int32_t
divbwt( const uint8_t *T, uint8_t *U, int32_t *A, int32_t n )
{
	int32_t *B;
	int32_t *bucket_A, *bucket_B;
	int32_t m, pidx, i;

	/* Check arguments. */
	if ( ( T == NULL ) || ( U == NULL ) || ( n < 0 ) )
	{
		return -1;
	}
	else if ( n <= 1 )
	{
		if ( n == 1 )
		{
			U[0] = T[0];
		}
		return n;
	}

	if ( ( B = A ) == NULL )
	{
		B = new int32_t [ ( n + 1 )];
	}
	bucket_A = new int32_t [BUCKET_A_SIZE];
	bucket_B = new int32_t [BUCKET_B_SIZE];

	/* Burrows-Wheeler Transform. */
	if ( ( B != NULL ) && ( bucket_A != NULL ) && ( bucket_B != NULL ) )
	{
		m = sort_typeBstar( T, B, bucket_A, bucket_B, n );
		pidx = construct_BWT( T, B, bucket_A, bucket_B, n, m );

		/* Copy to output string. */
		U[0] = T[n - 1];
		for ( i = 0; i < pidx; ++i )
		{
			U[i + 1] = ( uint8_t ) B[i];
		}
		for ( i += 1; i < n; ++i )
		{
			U[i] = ( uint8_t ) B[i];
		}
		pidx += 1;
	}
	else
	{
		pidx = -2;
	}

	delete[] bucket_B;
	delete[] bucket_A;
	if ( A == NULL )
		delete[] B;

	return pidx;
}

/* Inverse Burrows-Wheeler transform. */
int32_t
inverse_bw_transform( const uint8_t *T, uint8_t *U, int32_t *A,
					  int32_t n, int32_t idx )
{
	int32_t C[ALPHABET_SIZE];
	uint8_t D[ALPHABET_SIZE];
	int32_t *B;
	int32_t i, p;
	int32_t c, d;

	/* Check arguments. */
	if ( ( T == NULL ) || ( U == NULL ) || ( n < 0 ) || ( idx < 0 ) ||
		 ( n < idx ) || ( ( 0 < n ) && ( idx == 0 ) ) )
	{
		return -1;
	}
	if ( n <= 1 )
	{
		return 0;
	}

	if ( ( B = A ) == NULL )
	{
		/* Allocate n*sizeof(saidx_t) bytes of memory. */
		B = new int32_t [n];
	}

	/* Inverse BW transform. */
	memset( C, 0, sizeof ( int32_t ) * ALPHABET_SIZE );
	for ( i = 0; i < n; ++i )
	{
		++C[T[i]];
	}
	for ( c = 0, d = 0, i = 0; c < ALPHABET_SIZE; ++c )
	{
		p = C[c];
		if ( 0 < p )
		{
			C[c] = i;
			D[d++] = ( uint8_t ) c;
			i += p;
		}
	}
	for ( i = 0; i < idx; ++i )
	{
		B[C[T[i]]++] = i;
	}
	for (; i < n; ++i )
	{
		B[C[T[i]]++] = i + 1;
	}
	for ( c = 0; c < d; ++c )
	{
		C[c] = C[D[c]];
	}
	for ( i = 0, p = idx; i < n; ++i )
	{
		U[i] = D[ std::lower_bound( C, C + d, p ) - C ];
		p = B[p - 1];
	}
	if ( A == NULL )
		delete[] B;
	return 0;
}