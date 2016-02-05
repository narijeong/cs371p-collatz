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
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    //assert i > 0; 
    //assert j > 0;
    //assert i <= j;
    
    int max = j;
    int min = i;
    
    if(i > i) {
		min = j;
		max = i;
	}
    
    if((max/2)+1 > min) {
	  min = (max/2)+1;
	}
	
    int max_length = 1; 
    int c_length = 1;
    for(int i = min; i <= max; ++i) {
	  	c_length = get_c(i);
	  	if(c_length > max_length)
		  max_length = c_length; 
	}
    return max_length;
}

int get_c(int i) {
	//assert (i > 0);
	int cycle_length = 1;
	while(i > 1) {
	   if(i%2 == 0)
	     i = i/2;
	   else 
		 i = i*3 + 1;
	   cycle_length++;
	}
	return cycle_length;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}
}
