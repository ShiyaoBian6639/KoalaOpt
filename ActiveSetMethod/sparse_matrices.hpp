#pragma once
#ifndef SPARSE_MATRICES
#define SPARSE_MATRICES


#include<iostream>
#include<vector>
#include<chrono>

#define EIGEN_USE_MKL_ALL
#include<Eigen/Dense>
#include<Eigen/Sparse>
#include<Eigen/SparseQR>
#include<Eigen/Cholesky>

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

using namespace std;
using namespace Eigen;

void test();
SpMat genSparseConstraint();
#endif // !SPARSE_MATRICES
