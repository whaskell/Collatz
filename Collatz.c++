// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {

	int cycle_cnt, n;
	int cycle_cnt_max = 0;
	if (i>j)
	{
		i = i + j;
		j = i - j;
		i = i - j;
	}

	for (int x=i; x<=j; ++x)
	{
		n = x;
		cycle_cnt = 1;
		while(n != 1)
		{
			++cycle_cnt;
			if(n%2)
			{
				n = 3*n + 1;
			}
			else
			{
				n >>= 1 ; // n = n + 2
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
        collatz_print(w, i, j, v);}}
