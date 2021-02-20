#pragma once
#ifndef SPARSE_MATRICES
#define SPARSE_MATRICES


#include<iostream>
#include<vector>
#include<chrono>

#include<Eigen/Dense>
#include<Eigen/Sparse>
#include<Eigen/SparseQR>
#include<Eigen/Cholesky>

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

using namespace std;
using namespace Eigen;

void test();
SpMat gen_sparse_constraint();
#endif // !SPARSE_MATRICES
