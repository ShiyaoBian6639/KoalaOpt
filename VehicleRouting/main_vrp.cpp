// Solomon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"IO/read.hpp"
#include"solve.hpp"
#include"performance.hpp"



using namespace std;

int main()
{
    cout << "Welcome to Koala Vehicle Routing Problem Solver!\n";

    auto begin = chrono::steady_clock::now();
    Solve sol("./data/homberger_1000/C1_10_6.TXT");
    sol.read(); //sol.printCustomer();
    vector<vector<float>> distance_mat = sol.preprocess();

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - begin;

    cout << endl << "The whole program takes " << elapsed.count() << " seconds" << endl;


    return 0;
    /* performance benchmark */
    //perf_bench();
}
