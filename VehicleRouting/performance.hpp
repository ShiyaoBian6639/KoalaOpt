#pragma once
#ifndef _PERFORMANCE
#define _PERFORMANCE

#define NUM 100

#include"IO/read.hpp"


int nested_vector_access(Read instance);
int** dynamic_array(unsigned n, unsigned m);
void dictionary_vs_arr();
void perf_bench();
#endif // !_PERFORMANCE
