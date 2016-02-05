// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(CollatzFixture, read1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);
}

TEST(CollatzFixture, read2) {
    string s("100 200\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 100, p.first);
    ASSERT_EQ(200, p.second);
}

TEST(CollatzFixture, read3) {
    string s("201 210\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 201, p.first);
    ASSERT_EQ(210, p.second);
}

// ------
// get_c
// ------

TEST(CollatzFixture, get_c1) {
	const int c = get_c(1);
	ASSERT_EQ(1, c);
}

TEST(CollatzFixture, get_c2) {
	const int c = get_c(100);
	ASSERT_EQ(26, c);
}

TEST(CollatzFixture, get_c3) {
	const int c = get_c(20);
	ASSERT_EQ(8, c);
}
	
// ------------
// find_maxC
// ------------

TEST(CollatzFixture, find_maxC1) {
	const int max_c = find_maxC(1, 10, 1);
	ASSERT_EQ(20, max_c);
}

TEST(CollatzFixture, find_maxC2) {
	const int max_c = find_maxC(1, 10, 21);
	ASSERT_EQ(21, max_c);
}

TEST(CollatzFixture, find_maxC3) {
	const int max_c = find_maxC(100, 200, 125);
	ASSERT_EQ(125, max_c);
}


// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

// -----
// print
// -----

TEST(CollatzFixture, print1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());
}

TEST(CollatzFixture, print2) {
    ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_EQ("100 200 125\n", w.str());
}

TEST(CollatzFixture, print3) {
    ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_EQ("201 210 89\n", w.str());
}

// -----
// solve
// -----

TEST(CollatzFixture, solve1) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());
}

TEST(CollatzFixture, solve2) {
    istringstream r("1 1000\n1001 2000\n2001 3000\n3001 4000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1000 179\n1001 2000 182\n2001 3000 217\n3001 4000 238\n", w.str());
}

TEST(CollatzFixture, solve3) {
    istringstream r("2811 2608\n5242 401\n9476 8566\n6477 92\n3606 6997\n7463 7526\n4959 123 \n5553 6918\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("2811 2608 191\n5242 401 238\n9476 8566 260\n6477 92 262\n3606 6997 262\n7463 7526 208\n4959 123 238\n5553 6918 262\n", w.str());
}
/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
*/
