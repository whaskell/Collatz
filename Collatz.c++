// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Walter Haskell
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <list>

#include "Collatz.h"

using namespace std;

//#define HARD_CACHE_SIZE 60000
#define HARD_CACHE_SIZE 60
// 60,000 seems to be the fastest w/o out anyother caching


int hard_cache[HARD_CACHE_SIZE + 1];


// ------------
// collatz_read
// ------------

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

// ------------
// init cache
// ------------

// cache[0] = throw away value

void init_hard_cache(int i)
{
	int cycle_cnt, n;

	for (int x = i; x <= HARD_CACHE_SIZE; ++x)
	{
		n = x;
		cycle_cnt = 1;
		while(n != 1)
		{
#if 0
			if (n < x)
			{
				cycle_cnt += cache[n] - 1;
				break;
			}
#endif
			++cycle_cnt;
			if(n & 1)	// Test if odd number
			{
				n = n + n + n + 1; // n = 3*n + 1
			}
			else
			{
				n >>= 1 ; // n = n/2
			}
		}
		hard_cache[x] = cycle_cnt;
	}
}

// ------------
// collatz_eval
// ------------


int collatz_eval (int i, int j) {

	int cycle_cnt, n;
	int cycle_cnt_max = 0;

	if (i>j)
	{
		// swap values
		i = i + j;
		j = i - j;
		i = i - j;
	}

	for (int x = i; x <= j; ++x)
	{
		n = x;
		cycle_cnt = 1;
		while(n != 1)
		{
			if (n <= HARD_CACHE_SIZE)
			{
				cycle_cnt += hard_cache[n] - 1;
				break;
			}
			else
			{
				++cycle_cnt;
				if (n & 1)	// Test if odd number
				{
					n = n + n + n + 1; // n = 3*n + 1
				}
				else
				{
					n >>= 1; // n = n/2
				}
			}
		}

		if (cycle_cnt > cycle_cnt_max)
			cycle_cnt_max = cycle_cnt;
	}

    return cycle_cnt_max;}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    int i;
    int j;

    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}
}
